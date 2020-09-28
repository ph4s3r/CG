// catmull_clark_2d.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// hany pontig menjunk el
#define M 100

// kontrollpontok x,y koordinataja
double rx[M]; 
double ry[M];

// finomitassal kapott uj pontok
double rx1[M];
double ry1[M];

// most epp hany kontrollpontunk van
int N;

bool szin = 0;

// kezdo kontrollpontok
void ControlPointInit(){
	rx[0] = 10.0; ry[0] = 18.0;
	rx[1] = 24.0; ry[1] = 25.0;
	rx[2] = 34.0; ry[2] = 57.0;
	rx[3] = 56.0; ry[3] = 78.0;
	rx[4] = 63.0; ry[4] = 90.0;
	rx[5] = 70.0; ry[5] = 67.0;
	rx[6] = 81.0; ry[6] = 45.0;
	rx[7] = 88.0; ry[7] = 33.0;

	N = 8;
}

// finomitas, alulosztas
// regi kontrollpontokbol ujakat csinalunk
//
//  Negy kontrollpontbol otot csinal:
//	p0			[4 4 0 0] [p0]
//	p1			|1 6 1 0| |p1|
//	p2 = 1/8 *  |0 4 4 0| |p2|
//	p3			|0 1 6 1| [p3]
//	p4			[0 0 4 4]
//
//	(ha minden igaz, ez a Catmull-Clark alulosztas:)
//	
//	az elso negy pontbol ot lesz, utana meg minde pont miatt ket uj kerul be,
//	ez az utolso ponttal osszekoto szakasz felezopontja (ez a 4 4 0 0 sorok),
//  egy pedig az utolso ketto es az uj kombinacioja
//
//  bena megoldas, ket kulon tombot hasznalok a regi es uj ertekeknek, de igy egyszeru:)
//	N pontbol 5 + (N - 4) * 2 uj pontot csinal

void Refinement(){
	int i,j;
	// elso negy pont finomitasa
	rx1[0] = (rx[0] + rx[1]) / 2;  ry1[0] = (ry[0] + ry[1]) / 2;  
	rx1[1] = (rx[0] + 6 * rx[1] + rx[2]) / 8.0; ry1[1] = (ry[0] + 6 * ry[1] + ry[2]) / 8.0;
	rx1[2] = (rx[1] + rx[2]) / 2;  ry1[2] = (ry[1] + ry[2]) / 2;  
	rx1[3] = (rx[1] + 6 * rx[2] + rx[3]) / 8.0; ry1[3] = (ry[1] + 6 * ry[2] + ry[3]) / 8.0;
	rx1[4] = (rx[2] + rx[3]) / 2;  ry1[4] = (ry[2] + ry[3]) / 2;  

	// innentol mehet ciklussal
	for (i = 4; i < N; i++){
		// minden egyes pont 2 ujabbat hoz be
		j = (4 + (i-3)*2) - 1;	// ez a 5 + (N - 4 ) * 2 - bol jon, csak 0-sak a tomb kezdesek, ezert kell eltolni
		rx1[j] = (rx[i-2] + 6 * rx[i-1] + rx[i]) / 8.0;
		ry1[j] = (ry[i-2] + 6 * ry[i-1] + ry[i]) / 8.0;

		rx1[j+1] = (rx[i-1] + rx[i]) / 2.0;
		ry1[j+1] = (ry[i-1] + ry[i]) / 2.0;  
	}

	// at kell masolni az uj pontokat a regi tombbe
	for (i=0; i< 5 + (N-4)*2; i++){
		printf("%d. %.2f,%.2f\t\t%.2f,%.2f\n", i, rx[i],ry[i],rx1[i],ry1[i]);
	
		rx[i] = rx1[i];
		ry[i] = ry1[i];
	}

	N = 5 + (N-4)*2;

	szin = !szin; // hogy az uj kontrollpontokat mas szinnel irjuk ki
}

void DrawControlPoints(){
    glPointSize(3.0);		// pontmeret, glBegin elott kell kiadni
	glBegin(GL_POINTS);    
	
	if (szin)
		glColor3d(1.0, 1.0 , 0.0);
	else 
		glColor3d(1.0, 0.0 , 1.0);

    for(int i=0; i<N;i++){
        glVertex2d(rx[i],ry[i]);
	}

    glEnd();

}

void DrawLines(){
	glBegin(GL_LINE_STRIP);    
	glColor3d(1.0 ,1.0 ,1.0);

    for(int i=0; i<N;i++){
        glVertex2d(rx[i],ry[i]);
	}

    glEnd();
}

void ReDraw(){
	if (5 + (N - 4) * 2 < M){ // ha meg egy finomitassak nem erjuk el a max pontszamot, akkor meg finomithatunk
		while (5 + (N - 4) * 2 < M){
			glClear(GL_COLOR_BUFFER_BIT);		// egesz kepernyo torlese	
			DrawControlPoints();				// kontrollpontok felrajzolasa
			DrawLines();						// kontrollpontok kozott vonal
			glFlush();							// rajzoljon most

			//Sleep(1000);						// varunk
			Refinement();						// finomitas
			DrawControlPoints();				// kontrollpontok felrajzolasa
			DrawLines();						// kontrollpontok kozott vonal
			glFlush();		

			//Sleep(3000);
		}
	}
	else{										// egyebkent csak kirajzoljuk a vonalat
		glClear(GL_COLOR_BUFFER_BIT);
		DrawLines();
		glFlush();
	}
}

int main(int argc, char* argv[])
{
	ControlPointInit();

	 glutInitWindowSize(200, 200);           // 200*200-as ablak
    glutInitWindowPosition(100, 100);   // 100,100 helyen legyen
    glutInit(&argc, argv);                              // atadjuk a main parametereit
    glutInitDisplayMode( GLUT_RGB );    // RGB-ben dolgozunk

    glutCreateWindow("Catmull-Clark");                 // csinalja meg az ablakot

        //init, ezt copy&pasteletem ez egyik tutorialbol
        glClearColor(0.0,0.0,0.0,0.0);      // a törloszín a fekete 
    glMatrixMode(GL_PROJECTION);        // az aktuális mátrix mód a vetítési mátrix 
    glLoadIdentity();                   // legyen az egységmátrix 
    gluOrtho2D(0,100,0,100);            // párhuzamos vetítést specifikálunk; 

        glutDisplayFunc( ReDraw );                      // ujrarajzolo fuggveny a ReDraw
        glutMainLoop();                                         // kezdheti a vegtelen ciklusban figyelest

        return 0;
}
