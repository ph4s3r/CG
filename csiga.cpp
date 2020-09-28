//=============================================================================================
// Szamitogepes grafika hazi feladat keret. Ervenyes 2011-tol.          
// A //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sorokon beluli reszben celszeru garazdalkodni, mert a tobbit ugyis toroljuk. 
// A beadott program csak ebben a fajlban lehet, a fajl 1 byte-os ASCII karaktereket tartalmazhat. 
// Tilos:
// - mast "beincludolni", illetve mas konyvtarat hasznalni
// - faljmuveleteket vegezni (printf is fajlmuvelet!)
// - new operatort hivni
// - felesleges programsorokat a beadott programban hagyni
// - tovabbi kommenteket a beadott programba irni a forrasmegjelolest kommentjeit kiveve
// ---------------------------------------------------------------------------------------------
// A feladatot ANSI C++ nyelvu forditoprogrammal ellenorizzuk, a Visual Studio-hoz kepesti elteresekrol
// es a leggyakoribb hibakrol (pl. ideiglenes objektumot nem lehet referencia tipusnak ertekul adni)
// a hazibeado portal ad egy osszefoglalot.
// ---------------------------------------------------------------------------------------------
// A feladatmegoldasokban csak olyan gl/glu/glut fuggvenyek hasznalhatok, amelyek
// 1. Az oran a feladatkiadasig elhangzottak ES (logikai AND muvelet)
// 2. Az alabbi listaban szerepelnek:  
// Rendering pass: glBegin, glVertex[2|3]f, glColor3f, glNormal3f, glTexCoord2f, glEnd, glDrawPixels
// Transzformaciok: glViewport, glMatrixMode, glLoadIdentity, glMultMatrixf, gluOrtho2D, 
// glTranslatef, glRotatef, glScalef, gluLookAt, gluPerspective, glPushMatrix, glPopMatrix,
// Illuminacio: glMaterialfv, glMaterialfv, glMaterialf, glLightfv
// Texturazas: glGenTextures, glBindTexture, glTexParameteri, glTexImage2D, glTexEnvi, 
// Pipeline vezerles: glShadeModel, glEnable/Disable a kovetkezokre:
// GL_LIGHTING, GL_NORMALIZE, GL_DEPTH_TEST, GL_CULL_FACE, GL_TEXTURE_2D, GL_BLEND, GL_LIGHT[0..7]
//
// NYILATKOZAT
// ---------------------------------------------------------------------------------------------
// Nev    : Karacsonyi Peter
// Neptun : T84F5D
// ---------------------------------------------------------------------------------------------
// ezennel kijelentem, hogy a feladatot magam keszitettem, es ha barmilyen segitseget igenybe vettem vagy 
// mas szellemi termeket felhasznaltam, akkor a forrast es az atvett reszt kommentekben egyertelmuen jeloltem. 
// A forrasmegjeloles kotelme vonatkozik az eloadas foliakat es a targy oktatoi, illetve a 
// grafhazi doktor tanacsait kiveve barmilyen csatornan (szoban, irasban, Interneten, stb.) erkezo minden egyeb 
// informaciora (keplet, program, algoritmus, stb.). Kijelentem, hogy a forrasmegjelolessel atvett reszeket is ertem, 
// azok helyessegere matematikai bizonyitast tudok adni. Tisztaban vagyok azzal, hogy az atvett reszek nem szamitanak
// a sajat kontribucioba, igy a feladat elfogadasarol a tobbi resz mennyisege es minosege alapjan szuletik dontes.  
// Tudomasul veszem, hogy a forrasmegjeloles kotelmenek megsertese eseten a hazifeladatra adhato pontokat 
// negativ elojellel szamoljak el es ezzel parhuzamosan eljaras is indul velem szemben.
//=============================================================================================

#include <math.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
// MsWindows-on ez is kell
#include <windows.h>     
#endif // Win32 platform

#include <GL/gl.h>
#include <GL/glu.h>
// A GLUT-ot le kell tolteni: http://www.opengl.org/resources/libraries/glut/
#include <GL/glut.h>     

#define new new_nelkul_is_meg_lehet_csinalni

#define CRS_POINTS 10
#define BEZ_POINTS 6

const float PI=3.1415926535897932384626433832795;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Innentol modosithatod...


class Point {
public:
	float x, y;

	Point(float x1, float y1)  
	{
		x = x1;
		y = y1;
	}
	Point() {
		x = 0; y = 0;
	}

	Point operator+(const Point &p) {
		return Point(p.x+x, p.y+y);
	}

};

class Bezier_Spline {
public:

	Point ctrlpoints[BEZ_POINTS];		//vezerlopont tomb
	int npoints;			//vezerlopontok szama
	Bezier_Spline(int n) {
		npoints = n;
		for(int i = 0; i < n; i++) {
			ctrlpoints[i] = Point();
		}
	}

	Point Interpolate ( double tt ) {

		Point rr(0, 0);
		int j = 1;
		for(int i = 0; i< npoints; i++) {
			double Bi = 1.0;
			for(j = 1;j <= i; j++) Bi *= tt * (npoints-j)/j;
			for(;j < npoints; j++) Bi *= (1-tt);
		rr.y += ctrlpoints[i].y * Bi;
		rr.x += ctrlpoints[i].x * Bi;
		}
		return rr;
	}

	void rajzol() {
		glColor3d( 1.0, 0.0, 0.0) ;
		/*
		glBegin( GL_LINE_STRIP );
		for ( int i = 0; i < 100 ; i++ ) {
			double t = (double)i / 100;
			Point p = Interpolate(t);
			glVertex2f( p.x, p.y );
		}
		glEnd();
		*/
		//Original vezerlopontok
		///*
		glColor3d( 0.2, 0.4, 0.6 ) ;
		glBegin( GL_LINE_STRIP ) ;
		for ( int k = 0; k < npoints; k++) 
						glVertex2f( ctrlpoints[k].x, ctrlpoints[k].y );
		glEnd();
		//*/
	}

};


class Catmull_Clark_Spline {
public:

	Point ctrlpoints[CRS_POINTS];		//vezerlopont tomb
	int npoints;			//vezerlopontok szama
	Catmull_Clark_Spline(int n) {
		npoints = n;
		for(int i = 0; i < n; i++) {
			ctrlpoints[i] = Point();
		}
	}

	void Catrajzol() {
		Point catmull[CRS_POINTS];
		catmull[0] = ctrlpoints[0];

		for(int i = 1; i < npoints*2; i++) {
			if(i%2 == 1) {
				int j = (i+1)/2;
				catmull[i].x = (ctrlpoints[j].x + ctrlpoints[j+1].x)/2;
				catmull[i].y = (ctrlpoints[j].y + ctrlpoints[j+1].y)/2;
			}
			else
				catmull[i].x = ctrlpoints[i/2+1].x;
				catmull[i].y = ctrlpoints[i/2+1].y;
		}														//felezes vege
		glColor3d( 1.0, 0.0, 0.0);
		glBegin( GL_LINE_STRIP );
		for ( int i = 0; i < npoints*2 -2 ; i++ ) {
			glVertex2f( catmull[i].x, catmull[i].y );
		}
		glEnd();
	}
		void rajzol() {
		glColor3d( 1.0, 0.0, 0.0) ;
		glBegin( GL_LINE_STRIP );
		for ( int i = 0; i < npoints ; i++ ) {
			glVertex2f( ctrlpoints[i].x, ctrlpoints[i].y );
		}
		glEnd();
	}

};

// Inicializacio, a program futasanak kezdeten, az OpenGL kontextus letrehozasa utan hivodik meg (ld. main() fv.)
void onInitialization( ) { 
		gluOrtho2D(0., 500., 0., 500.);
		//gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
}

// Rajzolas, ha az alkalmazas ablak ervenytelenne valik, akkor ez a fuggveny hivodik meg
void onDisplay( ) {
    glClearColor(0.1f, 0.6f, 0.1f, 0.0f);		// torlesi szin beallitasa
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // kepernyo torles

	Bezier_Spline Szem1(BEZ_POINTS);
	Catmull_Clark_Spline CsigaHaz1(CRS_POINTS);

	float rad = 100.0;
	//Szem1.ctrlpoints[0] = Point(rad*cos(360.0),rad*sin(360.0));
	Szem1.ctrlpoints[0] = Point(rad*cos(30.0),rad*sin(30.0));
	Szem1.ctrlpoints[1] = Point(rad*cos(60.0),rad*sin(60.0));
	Szem1.ctrlpoints[2] = Point(rad*cos(90.0),rad*sin(90.0));
	Szem1.ctrlpoints[3] = Point(rad*cos(120.0),rad*sin(120.0));
	Szem1.ctrlpoints[4] = Point(rad*cos(150.0),rad*sin(150.0));
	Szem1.ctrlpoints[5] = Point(rad*cos(180.0),rad*sin(180.0));
	//Szem1.ctrlpoints[7] = Point(rad*cos(210.0),rad*sin(210.0));
	//Szem1.ctrlpoints[8] = Point(rad*cos(240.0),rad*sin(240.0));
	//Szem1.ctrlpoints[9] = Point(rad*cos(270.0),rad*sin(270.0));
	//Szem1.ctrlpoints[10] = Point(rad*cos(300.0),rad*sin(300.0));
	//Szem1.ctrlpoints[11] = Point(rad*cos(330.0),rad*sin(330.0));
	//Szem1.ctrlpoints[12] = Point(rad*cos(360.0),rad*sin(360.0));

	CsigaHaz1.ctrlpoints[0] = Point(111,171);
	CsigaHaz1.ctrlpoints[1] = Point(-182,230);
	CsigaHaz1.ctrlpoints[2] = Point(163,-400);
	CsigaHaz1.ctrlpoints[3] = Point(182,230);
	CsigaHaz1.ctrlpoints[4] = Point(220,189);
	CsigaHaz1.ctrlpoints[5] = Point(-274,198);
	CsigaHaz1.ctrlpoints[6] = Point(307,-220);
	CsigaHaz1.ctrlpoints[7] = Point(-278,-400);
	CsigaHaz1.ctrlpoints[8] = Point(-307,-220);
	CsigaHaz1.ctrlpoints[9] = Point(386,206);
	
	glTranslatef(250.0, 250.0, 0.0);
	Szem1.rajzol();
	//CsigaHaz1.rajzol();



	// Buffercsere: rajzolas vege
	glFinish();
	glutSwapBuffers();
}

// Billentyuzet esemenyeket lekezelo fuggveny
void onKeyboard(unsigned char key, int x, int y) {
    if (key == 'd') glutPostRedisplay( ); 		// d beture rajzold ujra a kepet

}

// Eger esemenyeket lekezelo fuggveny
void onMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT && state == GLUT_DOWN);  // A GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON illetve GLUT_DOWN / GLUT_UP
}

// `Idle' esemenykezelo, jelzi, hogy az ido telik, az Idle esemenyek frekvenciajara csak a 0 a garantalt minimalis ertek
void onIdle( ) {
     long time = glutGet(GLUT_ELAPSED_TIME);		// program inditasa ota eltelt ido

}

// ...Idaig modosithatod
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// A C++ program belepesi pontja, a main fuggvenyt mar nem szabad bantani
int main(int argc, char **argv) {
    glutInit(&argc, argv); 				// GLUT inicializalasa
    glutInitWindowSize(600, 600);			// Alkalmazas ablak kezdeti merete 600x600 pixel 
    glutInitWindowPosition(100, 100);			// Az elozo alkalmazas ablakhoz kepest hol tunik fel
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	// 8 bites R,G,B,A + dupla buffer + melyseg buffer

    glutCreateWindow("Grafika hazi feladat");		// Alkalmazas ablak megszuletik es megjelenik a kepernyon

    glMatrixMode(GL_MODELVIEW);				// A MODELVIEW transzformaciot egysegmatrixra inicializaljuk
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);			// A PROJECTION transzformaciot egysegmatrixra inicializaljuk
    glLoadIdentity();

    onInitialization();					// Az altalad irt inicializalast lefuttatjuk

    glutDisplayFunc(onDisplay);				// Esemenykezelok regisztralasa
    glutMouseFunc(onMouse); 
    glutIdleFunc(onIdle);
    glutKeyboardFunc(onKeyboard);

    glutMainLoop();					// Esemenykezelo hurok
    
    return 0;
}

