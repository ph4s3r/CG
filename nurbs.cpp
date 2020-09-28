//========================================================
// Hazi feladat keret.          
// A //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sorokon beluli reszben celszeru garazdalkodni, mert
// a tobbit ugyis toroljuk. 
// A Hazi feladat csak ebben a fajlban lehet
// Tilos:
// - mast "beincludolni", illetve mas konyvtarat hasznalni
// - faljmuveleteket vegezni
//========================================================

#include <math.h>
#include <stdlib.h>
#ifdef WIN32
#include <windows.h>     // MsWindows-on ez is kell
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>     // Ezt le kell tolteni: http://www.opengl.org/resources/libraries/glut/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Nev:          
// Neptun:
//--------------------------------------------------------

#pragma region NURBS IMPLEMENTATION

float g_Points[7][3] = { 
	{ -30,0,0 },
	{  -45,30,2 },
	{ -45,30,0 },
	{-30,15,-2},
	{-15,30,0},
	{-15,30,2},
	{-15,0,0}
};
float g_Knots[] = {0.0f,0.0f,0.0f,0.0f,1.0f,2.0f,3.0f,4.0f,4.0f,4.0f,4.0f};
unsigned int g_num_cvs=7;
unsigned int g_degree=3;
unsigned int g_order=g_degree+1;
unsigned int g_num_knots=g_num_cvs+g_order;

unsigned int LOD=20;
int w = 1024;
int h = 600;


float CoxDeBoor(float u,int i,int k,const float* Knots) {
	if(k==1)
	{
		if( Knots[i] <= u && u <= Knots[i+1] ) {
			return 1.0f;
		}
		return 0.0f;
	}
	float Den1 = Knots[i+k-1] - Knots[i];
	float Den2 = Knots[i+k] - Knots[i+1];
	float Eq1=0,Eq2=0;
	if(Den1>0) {
		Eq1 = ((u-Knots[i]) / Den1) * CoxDeBoor(u,i,k-1,Knots);
	}
	if(Den2>0) {
		Eq2 = (Knots[i+k]-u) / Den2 * CoxDeBoor(u,i+1,k-1,Knots);
	}
	return Eq1+Eq2;
}

void GetOutpoint(float t,float OutPoint[]) {

	// sum the effect of all CV's on the curve at this point to 
	// get the evaluated curve point
	// 
	for(unsigned int i=0;i!=g_num_cvs;++i) {

		// calculate the effect of this point on the curve
		float Val = CoxDeBoor(t,i,g_order,g_Knots);

		if(Val>0.001f) {

			// sum effect of CV on this part of the curve
			OutPoint[0] += Val * g_Points[i][0];
			OutPoint[1] += Val * g_Points[i][1];
			OutPoint[2] += Val * g_Points[i][2];
		}
	}
}

#pragma endregion 

#pragma region Catmull Clark Implementation
// hany pontig menjunk el
#define M 100

// kontrollpontok x,y koordinataja
double rx[M]; 
double ry[M];

// finomitassal kapott uj pontok
double rx1[M];
double ry1[M];

// most epp hany kontrollpontunk van
int N ;

bool szin = 0;

// kezdo kontrollpontok
void ControlPointInit(){
	rx[0] = 0.0; ry[0] = 0.0;
	rx[1] = 0.0; ry[1] = 15.0;
	rx[2] = 0.0; ry[2] = 30.0;
	rx[3] = 15.0; ry[3] = 15.0;
	rx[4] = 30.0; ry[4] = 30.0;
	rx[5] = 30.0; ry[5] = 15.0;
	rx[6] = 30.0; ry[6] = 0.0;
	//rx[7] = 30.0; ry[7] = 0.0;

	N = 7;
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
//		printf("%d. %.2f,%.2f\t\t%.2f,%.2f\n", i, rx[i],ry[i],rx1[i],ry1[i]);
	
		rx[i] = rx1[i];
		ry[i] = ry1[i];
	}

	N = 5 + (N-4)*2;

	szin = !szin; // hogy az uj kontrollpontokat mas szinnel irjuk ki
}
void DrawControlPoints()
{
    glPointSize(5.0);		// pontmeret, glBegin elott kell kiadni
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


#pragma endregion 

#pragma region OpenGL Events

void Init( ) 
{ // enable depth testing
	glEnable(GL_DEPTH_TEST);
}
void onDisplay( ) {
   // clear the screen & depth buffer
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	// clear the previous transform
	glLoadIdentity();

// set the drawable region of the window
	glViewport(0,0,w,h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// just use a perspective projection
	gluPerspective(45,(float)w/h,0.1,100);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// set the camera position
	gluLookAt(	1,100,26,	//	eye pos
				0,5,0,	//	aim point
				0,1,0);	//	up direction

	glColor3f(1,1,0);
	glBegin(GL_LINE_STRIP);
	for(int i=0;i!=LOD;++i) {

		float t  = g_Knots[g_num_knots-1] * i / (float)(LOD-1);

		if(i==LOD-1) 
			t-=0.001f;

		float Outpoint[3]={0,0,0};

		GetOutpoint(t,Outpoint);

		glVertex3fv(Outpoint);
	}
	glEnd();

	glColor3f(1,0,0);
	glPointSize(3);
	glBegin(GL_POINTS);
	for(int i=0;i!=g_num_cvs;++i) {
		glVertex3fv(g_Points[i]);
	}
	glEnd();

ControlPointInit();

	if (5 + (N - 4) * 2 < M){ // ha meg egy finomitassak nem erjuk el a max pontszamot, akkor meg finomithatunk
		while (5 + (N - 4) * 2 < M){
			//glClear(GL_COLOR_BUFFER_BIT);		// egesz kepernyo torlese	
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
		//glClear(GL_COLOR_BUFFER_BIT);
		DrawLines();
		glFlush();
	}
	// currently we've been drawing to the back buffer, we need
	// to swap the back buffer with the front one to make the image visible
	glutSwapBuffers();
}

void onMousePress(int button, int state, int x, int y) 
{
	if (button == 0)
	{
		LOD+=2;
		
	}
	if (button == 2)
	{
	LOD-=2;

		// have a minimum LOD value
		if (LOD<4) 
			LOD=4;
		
	}
	// ask glut to redraw the screen for us... 
	glutPostRedisplay();
}

void onIdle( ) {
}

void onKeyboard(unsigned char key, int x, int y) {
}

#pragma endregion

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void main(int argc, char * argv[]) {
	glutInit(&argc, argv); 
	glutInitWindowSize(1024, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Grafika hazi feladat");
  	Init();
	glutDisplayFunc(onDisplay);
	glutMouseFunc(onMousePress); 
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboard);
	glutMainLoop();
}
