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
// Nev: Kun Attila          
// Neptun: cre6kz
//--------------------------------------------------------

class Object {
	float g_Points[7][2];
	float g_Knots[11];
	unsigned int g_num_cvs;
	unsigned int g_degree;
	unsigned int g_order;
	unsigned int g_num_knots;
	unsigned int LOD;
public:
	Object(int deg) {
		LOD=80;
		g_degree=deg;
		g_order=g_degree+1;
		g_num_cvs=7;
		g_num_knots=g_num_cvs+g_order;

		Init();
	}

	void Init() {		


		//  Initializing knot points
		//
		this->g_Knots[0] = 0.0;
		this->g_Knots[1] = 0.0;
		this->g_Knots[2] = 0.0;
		this->g_Knots[3] = 0.0;
		this->g_Knots[4] = 1.0;
		this->g_Knots[5] = 2.0;
		this->g_Knots[6] = 3.0;
		this->g_Knots[7] = 4.0;
		this->g_Knots[8] = 4.0;
		this->g_Knots[9] = 4.0;
		this->g_Knots[10] = 4.0;

		//  Initializing Controlpoints
		//
		this->g_Points[0][0] = -0.2;
		this->g_Points[0][1] = 0.0;

		this->g_Points[1][0] = 0.0;
		this->g_Points[1][1] = 0.5;

		this->g_Points[2][0] = 0.1;
		this->g_Points[2][1] = 0.0;

		this->g_Points[3][0] = 0.3;
		this->g_Points[3][1] = -0.4;

		this->g_Points[4][0] = 0.3;
		this->g_Points[4][1] = 0.4;

		this->g_Points[5][0] = 0.0;
		this->g_Points[5][1] = -0.5;

		this->g_Points[6][0] = -0.2;
		this->g_Points[6][1] = 0.0;
	}
	//------------------------------------------------------------	CoxDeBoor()
	//
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

	//------------------------------------------------------------	GetOutpoint()
	//
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

	void Drawing() {
		glColor4f( 0.8f, 0.9f, 0.5f, 0.0f );
		glBegin(GL_LINE_LOOP);
		for(int i=0;i!=LOD;++i) {
			float t  = g_Knots[g_num_knots-1] * i / (float)(LOD-1);
			if(i==LOD-1) 
				t-=0.001f;
			float Outpoint[3]={0,0,0};
			GetOutpoint(t,Outpoint);
			glVertex3fv(Outpoint);
		}
		glEnd();
	}

	void translater(const float x, const float y) {
		for(int i = 0; i < 7; i++) {
			g_Points[i][0] += x;
			g_Points[i][1] += y;
		}
	}

	void rotater(const float alpha) {
		for(int i = 0; i < 7; i++) {
			float temp_x = g_Points[i][0];
			g_Points[i][0] = g_Points[i][0]*cos(alpha) - g_Points[i][1]*sin(alpha);
			g_Points[i][1] = temp_x*sin(alpha) + g_Points[i][1]*cos(alpha);
		}
	}	

	void scaler(const float size) {
		for(int i = 0; i < 7; i++) {
			g_Points[i][0] *= size;
			g_Points[i][1] *= size;
		}
	}

};


bool isGLTransformed = false;			//State-machine
bool isPTTransformed = false;			

Object fish(3);			

void finishDrawing() {
	fish.Drawing();
	glFinish();
	glutSwapBuffers();
}

void ClearSCR() {
	glClearColor(0.2f, 0.1f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void onInitialization( ) {
}

void onDisplay( ) {
	glClearColor(0.2f, 0.1f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	fish.Drawing();

	glFinish();
	glutSwapBuffers();
}

void onMouse(int button, int state, int x, int y) {
	// A GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON
	// ill. a GLUT_DOWN / GLUT_UP makrokat hasznald.
}

void onIdle( ) {
}

void onKeyboard(unsigned char key, int x, int y) {
	if(key == 's') {

		ClearSCR();

		if(isPTTransformed || isGLTransformed) {
			fish.Init();
			glPopMatrix();
			glPushMatrix();
		}

		fish.scaler(1.2);
		fish.rotater(1);
		fish.translater(0.2, 0.2);

		finishDrawing();

		isPTTransformed = true;
	}

	else if (key == 'S') {

		if(isPTTransformed || isGLTransformed) {
			fish.Init();
			glPopMatrix();
			glPushMatrix();
		}

		ClearSCR();

		if(!isGLTransformed) {
			glPushMatrix();
		}

		glTranslated(0.2, 0.2, 0);
		glRotated(60, 0, 0, 1);
		glScaled(1.2, 1.2, 0);

		finishDrawing();

		isGLTransformed = true;
	}
}

// ...Idaig modosithatod
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char **argv) {
	glutInit(&argc, argv); 
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

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
