//=============================================================================================
// Szamitogepes grafika hazi feladat keret. Ervenyes 2010-tol.          
// A //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sorokon beluli reszben celszeru garazdalkodni, mert a tobbit ugyis toroljuk. 
// A Hazi feladat csak ebben a fajlban lehet. 
// Tilos:
// - mast "beincludolni", illetve mas konyvtarat hasznalni
// - faljmuveleteket vegezni (printf is fajlmuvelet!)
// ---------------------------------------------------------
// A keretben szereplokon kivul csak az anyagban szereplo gl/glu/glut fuggvenyek hasznalhatok: 
// Rendering pass: glBegin, glVertex[2|3]f, glColor3f, glNormal3f, glTexCoord2f, glEnd, glDrawPixels
// Transzformaciok: glViewport, glMatrixMode, glLoadIdentity, glMultMatrixf, gluOrtho2D, 
// glTranslatef, glRotatef, glScalef, gluLookAt, gluPerspective, glPushMatrix, glPopMatrix,
// Illuminacio: glMaterialfv, glMaterialfv, glMaterialf, glLightfv
// Texturazas: glGenTextures, glBindTexture, glTexParameteri, glTexImage2D, glTexEnvi, 
// Pipeline vezerles: glShadeModel, glEnable/Disable a kovetkezokre:
// GL_LIGHTING, GL_NORMALIZE, GL_DEPTH_TEST, GL_CULL_FACE, GL_TEXTURE_2D, GL_BLEND, GL_LIGHT[0..7]
//
// A beadott program nem tartalmazhat felesleges programsorokat!
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Innentol modosithatod...

//--------------------------------------------------------
// Nev    : Karacsonyi Peter
// Neptun : T84F5D	
//--------------------------------------------------------

const float PI=3.1415926535897932384626433832795;
const float rad_90deg = 90*PI/180;

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

Point spwn(0.61, -0.66);

class BoundingBox {
public:
	float xmin, xmax;
	float ymin, ymax;

	BoundingBox() {
		xmin = 0;
		ymin = 0;
		xmax = 0;
		ymax = 0;
	}

	BoundingBox(float x1, float x2, float y1, float y2) {
		xmin = x1;
		ymin = y1;
		xmax = x2;
		ymax = y2;
	}

	bool Collide(const BoundingBox other) {

		if(xmin<=other.xmax	&&
			xmax>=other.xmin &&
			ymin<=other.ymax &&
			ymax>=other.ymin) return true;
		else
			return false;

	}
};

class Object {
public:
	Point position;		//virualis vilagbeli koordináta
	float orientation; //radianban az elfordulas szoge
	float r;			//objektum sugara (hasznos lehet)

	BoundingBox AABB;
	virtual void Draw() {;} ;
	virtual void Animate() {;} ;

	Object() {
		position = Point(0.0,0.0);
		orientation = 0.0;
		r = 0.0;

		AABB = BoundingBox();
	}
} 	ObjectContainer[7];

class fal : public Object {
	float xmin;
	float xmax;
	float ymin;
	float ymax;

public:
	fal(float x_min, float x_max, float y_min, float y_max) {
		xmax =  x_max;
		ymax =  y_max;
		ymin =  y_min;
		xmin =  x_min;

		AABB.xmax =  x_max;
		AABB.ymax =  y_max;
		AABB.ymin =  y_min;
		AABB.xmin =  x_min;
	};

	void Draw() {
		glColor3f( 0.0f, 0.0f, 0.05f );
		glBegin( GL_QUADS );
		glVertex2f( xmin, ymin );
		glVertex2f( xmax, ymin );
		glVertex2f( xmax, ymax );
		glVertex2f( xmin, ymax );
		glEnd();
	}
};

class Ora : public Object {
	Point BPointerPos;
	Point LPointerPos;
public:

	Ora(Point pos) {
		position = pos;
	}

	void Draw() {
		glColor3f( 0.6f, 0.2f, 0.3f);
		glBegin( GL_QUADS );
		glVertex2f( position.x + 0.16f, position.y + 0.16f );
		glVertex2f( position.x + 0.16f, position.y - 0.16f );
		glVertex2f( position.x - 0.16f, position.y - 0.16f );
		glVertex2f( position.x - 0.16f, position.y + 0.16f );
		glEnd();

		//Oramutato (nagy)

		glColor3f( 0.0f, 0.0f, 0.0f);
		glBegin( GL_LINE_STRIP );
		glVertex2f( position.x, position.y);
		glVertex2f( BPointerPos.x, BPointerPos.y);
		glEnd();

		//Oramutato (kicsi)

		glColor3f( 1.0f, 1.0f, 1.0f);
		glBegin( GL_LINE_STRIP );
		glVertex2f( position.x, position.y);
		glVertex2f( LPointerPos.x, LPointerPos.y);
		glEnd();
	}
	void Animate(long dt, bool On) {
		if(On) {
			//A dt valtozo atalakitasa, hogy 0-60ig menjen (implementacios indokbol -30tol 30ig megy)
			dt = dt/500;
			dt = dt%60;
			dt = dt - 30;
			float B_angle = -dt*PI/60;
			float L_angle = -dt*PI/3600;
			BPointerPos = Point( position.x + 0.145*cos(B_angle), position.y + 0.145*sin(B_angle));
			LPointerPos = Point( position.x + 0.11*cos(L_angle), position.y + 0.11*sin(L_angle));
		}
	}
};

class Mouse : public Object {

public:

	bool isMoving;

	Mouse(Point pos, float orient) {
		r = 0.10;
		isMoving = false;
		position = pos;
		orientation = orient;
		AABB.xmax = position.x+0.05;
		AABB.ymax = position.y+0.05;
		AABB.ymin = position.y-0.05;
		AABB.xmin = position.x-0.05;
	}

	void Draw() {
		//Eger-test
		glColor3f( 0.2f, 0.2f, 0.24f) ;
		glBegin( GL_TRIANGLES );
		glVertex2f( r*cos(orientation) + position.x, r*sin(orientation) + position.y );
		glVertex2f( r*cos(orientation + 2.0) + position.x, r*sin(orientation + 2.0) + position.y );
		glVertex2f( r*cos(orientation + 4.0) + position.x, r*sin(orientation + 4.0) + position.y );
		glEnd();
		//Farok
		glBegin( GL_LINE_STRIP );
		glVertex2f( position.x, position.y);
		glVertex2f( position.x - (r+0.1)*cos(orientation), position.y - (r+0.1)*sin(orientation) );
		glEnd();
		//Bajusz
		glBegin( GL_LINE_STRIP );
		glVertex2f( (r)*cos(orientation + 0.6) + position.x, (r)*sin(orientation + 0.6) + position.y );
		glVertex2f( (r)*cos(orientation - 0.6) + position.x, (r)*sin(orientation - 0.6) + position.y );
		glEnd();
		//Szemek
		glColor3f( 0.0f, 0.0f, 0.0f) ;
		glBegin( GL_POINTS );
		glVertex2f( (r-0.06)*cos(orientation + 0.3) + position.x, (r-0.06)*sin(orientation + 0.3) + position.y );
		glVertex2f( (r-0.06)*cos(orientation - 0.3) + position.x, (r-0.06)*sin(orientation - 0.3) + position.y );
		glEnd();
	}

	void TurnLeft() {
		orientation = orientation + rad_90deg;
	}
	void TurnRight() {
		orientation = orientation - rad_90deg;
	}
	void Animate(long dt){
		Point velocity;
		if(!isMoving) velocity =  Point(0.0,0.0);
		else {
			velocity =  Point(r*cos(orientation), r*sin(orientation));
			position.x += velocity.x/400;
			position.y += velocity.y/400;
		}
		AABB.xmax = position.x+0.05;
		AABB.ymax = position.y+0.05;
		AABB.ymin = position.y-0.05;
		AABB.xmin = position.x-0.05;
	}

	int CollisionDetect(void) {							//Utkozes detektalas
		if(ObjectContainer[0].AABB.Collide(AABB))return 1;		//Ha sajttal utkozunk
		for(int i = 1; i <= 10; i++) {
			if(ObjectContainer[i].AABB.Collide(AABB))return i+1;	//Ha pedig fallal
		}
		return 0;
	}

	void Respawn(Point pt, float ori) {
		position = pt;
		orientation = ori;
	}
};

class Sajt : public Object {
public:
	Sajt(Point pos) {
		position = pos;
		orientation = 0.0;
		r = 0.09;
		AABB.xmax = position.x+0.05;
		AABB.ymax = position.y+0.05;
		AABB.ymin = position.y-0.05;
		AABB.xmin = position.x-0.05;
	}

	void Draw() {
		AABB.xmax = position.x+0.05;
		AABB.ymax = position.y+0.05;
		AABB.ymin = position.y-0.05;
		AABB.xmin = position.x-0.05;
		glColor3f( 0.6f, 0.6f, 0.1f);
		glBegin( GL_POLYGON );
		glVertex2f( r*cos(orientation) + position.x, r*sin(orientation) + position.y );
		glVertex2f( r*cos(orientation + 1.0) + position.x, r*sin(orientation + 1.0) + position.y );
		glVertex2f( r*cos(orientation + 2.0) + position.x, r*sin(orientation + 3.0) + position.y );
		glVertex2f( r*cos(orientation + 2.7) + position.x, r*sin(orientation + 5.0) + position.y );
		glVertex2f( r*cos(orientation + 4.0) + position.x, r*sin(orientation + 1.7) + position.y );
		glEnd();
	}
};

Mouse eger(spwn, PI);
Sajt Ementali(Point(-0.3, 0.57));
Ora TagHeuer(Point(-0.8, 0.8));
long time, start, respwn_timer;
bool m2sec = false;
bool Finish = false;
//   fal(x_min,x_max,y_min,y_max)
fal fal1(-1.0, 1.0, -1.0, -0.8);
fal fal2(-1.0, -0.75, -1.0, 1.0);
fal fal3(0.85, 1.0, -1.0, 1.0);
fal fal4(-0.4, 1.0, -0.55, -0.2);
fal fal5(-1.0, 0.5, 0.05, 0.4); 
fal fal6(-1.0, 1.0, 0.75, 1.0); 


// Inicializacio, a program futasanak kezdeten, az OpenGL kontextus letrehozasa utan hivodik meg (ld. main() fv.)
void onInitialization( ) { 

	ObjectContainer[0] = Ementali;
	ObjectContainer[1] = fal1;
	ObjectContainer[2] = fal2;
	ObjectContainer[3] = fal3;
	ObjectContainer[4] = fal4;
	ObjectContainer[5] = fal5;
	ObjectContainer[6] = fal6;
}

// Rajzolas, minden frame megjelenitesehez ez a fuggveny hivodik meg
void onDisplay( ) {
	glClearColor(0.478f, 0.192f, 0.192f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,600,600);

	fal1.Draw();
	fal2.Draw();
	fal3.Draw();
	fal4.Draw();
	fal5.Draw();
	fal6.Draw();
		eger.Draw();
	Ementali.Draw();
	TagHeuer.Draw();
	glutSwapBuffers();

}

// Billentyuzet esemenyeket lekezelo fuggveny
void onKeyboard(unsigned char key, int x, int y) {
	if (key == 'e') 
	{
		start = glutGet(GLUT_ELAPSED_TIME);
		glutPostRedisplay();
	}
	if (key == 'b')
	{
		eger.TurnLeft();
		glutPostRedisplay();
	}
	if (key == 'j')
	{
		eger.TurnRight();
		glutPostRedisplay();
	}
}

// Eger esemenyeket lekezelo fuggveny
void onMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT && state == GLUT_DOWN);  // A GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON illetve GLUT_DOWN / GLUT_UP
}

// `Idle' esemenykezelo, jelzi, hogy az ido telik
void onIdle( ) {
	long time = glutGet(GLUT_ELAPSED_TIME);		// program inditasa ota eltelt ido
	if(time > 1000.0 && time - start < 1000.0) eger.isMoving = true;
	else eger.isMoving = false;
	eger.Animate(time);
	if(!Finish) {
		TagHeuer.Animate(time, true);
	}
	else {
		TagHeuer.Animate(time, false);
	}
	if(eger.CollisionDetect() == 1) {
		Finish = true;
	}
	else if (eger.CollisionDetect() > 1 && eger.CollisionDetect() < 11) {		//ha fallal utkozunk
		if(!m2sec) {
			respwn_timer = glutGet(GLUT_ELAPSED_TIME);
			m2sec = true;
		}
		while (time - respwn_timer < 2000.0) {
			time = glutGet(GLUT_ELAPSED_TIME);	
			glClearColor(0.9f, 0.192f, 0.192f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glutSwapBuffers();
			eger.Respawn(spwn, PI);
			m2sec = false;
		}			
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

// ...Idaig modosithatod
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// A C++ program belepesi pontja, a main fuggvenyt mar nem szabad bantani
int main(int argc, char **argv) {
	glutInit(&argc, argv); 				// GLUT inicializalasa
	glutInitWindowSize(600, 600);			// Windows ablak kezdeti meret 600x600 pixel 
	glutInitWindowPosition(100, 100);			// Az elozo Windows ablakhoz kepest hol tunik fel
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	// 8 bites R,G,B,A + dupla buffer + melyseg buffer

	glutCreateWindow("Grafika hazi feladat");		// Windows ablak megszuletik es megjelenik a kepernyon

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

