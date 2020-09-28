//===========================================================
// Hazi feladat keret.          
// A //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sorokon beluli reszben celszeru garazdalkodni, mert
// a tobbit ugyis toroljuk. 
// A Hazi feladat csak ebben a fajlban lehet
// Tilos:
// - mast "beincludolni", illetve mas konyvtarat hasznalni
// - faljmuveleteket vegezni
// - tovabbi glut fuggvenyeket hivni
// - a feladat kiirasban nem szereplo glut fuggvenyeket hivni
//===========================================================

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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Innentol modosithatod...

//--------------------------------------------------------
// Nev    : Kun Attila
// Neptun : CRE6KZ
//--------------------------------------------------------

struct Point {

	float x, y;
	Point(float x1, float y1)  
	{
		x = x1;
		y = y1;
	}
	Point() {
		x = 0; y = 0;
	}
	Point operator*( float f ) {         // vektor és szám szorzata
		return Point( x * f, y * f );
	}
	Point operator+( const Point& v ) { // két vektor összege
		float X = x + v.x, Y = y + v.y;
		return Point(X, Y);
	}
	void operator+=( const Point& v ) {  // vektor összeadás
		x += v.x; y += v.y; 
	}
	Point operator-( const Point& v ) { 
		float X = x - v.x, Y = y - v.y;
		return Point(X, Y);
	}
	Point operator/( float f ) {		  // vektor osztva egy számmal
		return Point( x/f, y/f ); 
	}
	void operator<( const Point& v) {				//egy felsikkal jobbra forgatas
		float tempx = x;
		x = y; y = -tempx;
	}
	void operator>( const Point& v) {				//egy felsikkal balra forgatas
		float tempx = x;
		x = -y; y = tempx;
	}
	float Hossz( ) {                     // vektor abszolút értéke
		return (float)sqrt( x * x + y * y );
	}
	void Normal( ) {					  // vektor normalizálása
		float l = Hossz( );
		if ( l < 0.000001f) { x = 1; y = 0; }
		else { x /= l; y /= l; }
	}
};

Point ctrlpoints[10] = { 	
	Point(10,30),
	Point(9,43),
	Point(27,50),
	Point(29,25),
	Point(41,20),
	Point(57,40),
	Point(69,10),
	Point(69,40),
	Point(55,60),
	Point(70,70),
};

class myB_Spline {

private:

	float  t[14];								// csomóvektor
	int    m;									// vezérlopontok száma 
	int    K;									// fokszám

public:

	myB_Spline( ) {								// konstruktor
		K = 4;									// harmadfokú = 4 szint
		m = 10;
		int i = 0;
		for(i = 0; i < m+4; i++) t[i] = i - 3;  //csomovektor tomb
	}

	float B(int i, int k, float tt) {			// k-rendû i. bázisfüggvény
		if (k == 1)  {							// triviális eset vizsgálata
			if (i < m - 1) {
				if (t[i] <= tt && tt < t[i+1])  return 1;
				else						    return 0; 
			} else {
				if (t[i] <= tt)  return 1;
				else			 return 0; 
		 }
		}

		float b1, b2;
		if (t[i+k-1] - t[i] > 0.00001) b1 = (tt-t[i]) / (t[i+k-1] - t[i]);
		else                           b1 = 1.0;       // Itt: 0/0 = 1
		if (t[i+k] - t[i+1] > 0.00001) b2 = (t[i+k]-tt) / (t[i+k] - t[i+1]);
		else                           b2 = 1.0;       // Itt: 0/0 = 1

		return (b1 * B(i, k-1, tt) + b2 * B(i+1, k-1, tt) ); // rekurzió
	}

	Point Curve(float t) {						// a görbe egy adott pontja
		Point rt(0,0);
		for(int i = 0; i < m; i++) rt += ctrlpoints[i] * B(i, 4, t);
		return rt;
	}

	Point Velo(float o){
		int it = (int)o;

		float t = o-(int)o;
		
		float b0 = -(t*t - 2*t +1)/2;
		float b1 = (3*t*t-4*t)/2;
		float b2 = (2*t-3*t*t+1)/2;
		float b3 = (t*t)/2;
		Point rt = ctrlpoints[it]*b0 + ctrlpoints[it+1]*b1 + ctrlpoints[it+2]*b2 + ctrlpoints[it+3]*b3;
		return (rt);
	}

	Point Acc(float t){
		int it = (int)t;
		t = t-(int)t;

		float b0 = -t+1;
		float b1 = 3*t-2;
		float b2 = 1-3*t;
		float b3 = t;

		return (ctrlpoints[it]*b0+
			ctrlpoints[it+1]*b1+
			ctrlpoints[it+2]*b2+
			ctrlpoints[it+3]*b3);
	}

	void DrawVec(Point p, float t, float c1, float c2, float c3){//szint is bekerunk miutan ketfele vektorrol lesz szo

		Point arrowHeadleft = p;					//jo lesz nyilvegnek
		Point arrowHeadright = p;
		arrowHeadleft>arrowHeadleft;				//elforgatas balra
		arrowHeadright<arrowHeadright;				//jobbra.. ..egy felsikkal
		Point aHR = p*(-1)+arrowHeadright;			//vektorunk ellentetjevel osszeadjuk!
		Point aHL = p*(-1)+arrowHeadleft;
		aHR.Normal();
		aHL.Normal();

		glColor3f(c1, c2, c3);	
		glBegin( GL_LINE_STRIP );
		glVertex2f(Curve(t).x, Curve(t).y);
		glVertex2f(Curve(t).x + p.x, Curve(t).y + p.y);
		glVertex2f(Curve(t).x + p.x + aHL.x*2, Curve(t).y + p.y + aHL.y*2);		//nyilhegy no1
		glVertex2f(Curve(t).x + p.x, Curve(t).y + p.y);
		glVertex2f(Curve(t).x + p.x + aHR.x*2, Curve(t).y + p.y + aHR.y*2);		//nyilhegy no2
		glEnd();
	}

	void DrawtheSplineandCtrls( ) {
		glColor3f(1, 1, 0);
		glBegin( GL_TRIANGLES );			// vezérlo: pontok
		for(int i = 0; i < m; i++) {
			glVertex2f( ctrlpoints[i].x-0.3, ctrlpoints[i].y-0.3 );
			glVertex2f( ctrlpoints[i].x+0.3, ctrlpoints[i].y-0.3 );
			glVertex2f( ctrlpoints[i].x,   ctrlpoints[i].y+0.3 );
		}
		glEnd();

		glColor3d( 1.0, 1.0, 1.0) ;
		glBegin( GL_LINE_STRIP );
//gorbe pontjai
		for(int i = 0; i < 7; i++)
		{
			for(int j = 0; j < 100; j++ )
			{
				float tt = t[i+3] + (t[i+4] - t[i+3])/100 * j;
				Point point = Curve( tt );
				glVertex2f( point.x, point.y );
			}
		}
		glEnd();
	}
};

void onInitialization( ) { 

	float parallelprojection[16] = {
		2.0/100.0,    0.0,       0.0,       0.0,
		0.0,           2.0/100.0,    0.0,       0.0,
		0.0,              0.0,      -1.0,       0.0,
		-1.0,			  -1.0,		  0.0,       1.0};

	glMultMatrixf(parallelprojection);
}
myB_Spline spline;			//defeinaljuk a gorbe't
float parameter = 0.0;

void onDisplay( ) {
	glClearColor(0.1f, 0.1f, 0.1f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT);

	spline.DrawtheSplineandCtrls();

	spline.DrawVec(spline.Velo(parameter), parameter, 0.8, 0.1, 0.5);
	spline.DrawVec(spline.Acc(parameter), parameter, 0.1, 0.1, 0.8);

	glFinish();
	glutSwapBuffers();
}

void onKeyboard(unsigned char key, int x, int y) {
	if(key == ' ') {
		
		if( parameter >= 7 ) parameter-=7;			//parameter ertekunk  m-K+1 ig fut, ahogy kell
		else	parameter+=0.3;

		onDisplay( );

	}
}

// Eger esemenyeket lekezelo fuggveny
void onMouse(int button, int state, int x, int y) {
}
void onIdle( ) {
}

// ...Idaig modosithatod
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// A C++ program belepesi pontja
int main(int argc, char **argv) {
	glutInit(&argc, argv); 
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Grafika hazi feladat");

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	onInitialization();

	glutDisplayFunc(onDisplay);
	glutMouseFunc(onMouse); 
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboard);

	glutMainLoop();

	return 0;
}

