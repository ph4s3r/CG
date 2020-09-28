					//Cg
					#include "Cg\cg.h"
					#include "Cg\cgGL.h"

#include "codebehind.cpp"

using namespace std;

int w_height = 600;
int w_width = 600;

//******************************
//Cg Environment Vars Init Begin

CGcontext cgContext;
CGprogram myVertexProgram, myFragmentProgram;
CGprofile cgVertexProfile, cgFragmentProfile;
CGparameter	 modelViewMatrix, 	globalAmbient,	eyePosition, lightPosition, lightColor;

//Cg Environment Vars Init End
//****************************

static void checkForCgError(const char *situation)
{
  CGerror error;
  const char *string = cgGetLastErrorString(&error);

  if (error != CG_NO_ERROR) {
    printf("%s: %s: %s\n",
      myProgramName, situation, string);
    if (error == CG_COMPILER_ERROR) {
      printf("%s\n", cgGetLastListing(myCgContext));
    }
    exit(1);
  }
}

GLuint MakeTexture() {
	GLuint texture_id;
               glGenTextures(1, &texture_id);
               glBindTexture(GL_TEXTURE_2D, texture_id);
			   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);				//bilinear texture filtering
			   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
			   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
               glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, terep.pixel_data);
	return texture_id;
}

void DrawPyramid() {

	glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.8f, 0.2f);
	//piramis alap

	glVertex3f(-10.0, 0.0, -10.0);
	glVertex3f(10.0, 0.0, -10.0);
	glVertex3f(-10.0, 0.0, 10.0);
	glVertex3f(-10.0, 0.0, 10.0);
	glVertex3f(10.0, 0.0, 10.0);
	glVertex3f(10.0, 0.0, -10.0);

	//piramis oldallapok
	
		//Normalvektor:
		Vector v1;
		Vector v2;
		Vector v3;

	v1 = Vector(-20.0, 0.0, 0.0);	//p1-p2
	v2 = Vector(10.0, 13.0, -10.0);	//p2-p3
	v3 = v1%v2;
	glNormal3f(v3.x, v3.y, v3.z);
	glVertex3f(-10.0, 0.0, -10.0);
	glVertex3f(10.0, 0.0, -10.0);
	glVertex3f(0.0, -13.0, 0.0);

	v1 = Vector(10.0, -13.0, 10.0);
	v2 = Vector(0.0, 0.0, -20.0);
	v3 = -v1%v2;
	glNormal3f(v3.x, v3.y, v3.z);
	glVertex3f(0.0, -13.0, 0.0);
	glVertex3f(-10.0, 0.0, -10.0);
	glVertex3f(-10.0, 0.0, 10.0);

	v1 = Vector(-20.0, 0.0, 0.0);
	v2 = Vector(10.0, 13.0, 10.0);
	v3 = v1%v2;
	glNormal3f(v3.x, v3.y, v3.z);
	glVertex3f(-10.0, 0.0, 10.0);
	glVertex3f(10.0, 0.0, 10.0);
	glVertex3f(0.0, -13.0, 0.0);

	v1 = Vector(0.0, 0.0, -20.0);
	v2 = Vector(10.0, 13.0, 10.0);
	v3 = -v1%v2;
	glNormal3f(v3.x, v3.y, v3.z);
	glVertex3f(10.0, 0.0, -10.0);
	glVertex3f(10.0, 0.0, 10.0);
	glVertex3f(0.0, -13.0, 0.0);

	glEnd();

	//cgGLDisableProfile(cgVertexProfile);

	//cgGLDisableProfile(cgFragmentProfile);

	//cgDestroyProgram(myVertexProgram);										//Free resources allocated for a single program
	
	//cgDestroyContext(cgContext);										//Free all the resources allocated for a context

}

void DrawTheGun(float radius, float height, float div) {

	glBegin(GL_QUADS);
	for(int i = 0; i <= div; i++) {
		float v = float(i);
				Vector vertex1, vertex2, vertex3, vertex4, v_normal;

				vertex1 = Vector(radius*cos(v),radius*sin(v),0.0);
				vertex2 = Vector(radius*cos(v+div),radius*sin(div+v),0.0);
				vertex3 = Vector(radius*cos(v+div),radius*sin(div+v),height);
				v_normal = (vertex1-vertex2)%(vertex2-vertex3);

				glNormal3f(-v_normal.x, -v_normal.y, -v_normal.z);

				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(vertex1.x,vertex1.y,vertex1.z);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(vertex2.x,vertex2.y,vertex2.z);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(vertex3.x,vertex3.y,vertex3.z);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(radius*cos(v),radius*sin(v),height);
	}
	glEnd();
}

void DrawBullet(float radius, float height, float div) {

	glBegin(GL_QUADS);
	for(float i = 0; i <= div; i++) {
		float v = float(i);
			for(int j = 0; j <= height; j++) {
					Vector vertex1, vertex2, vertex3, vertex4, v_normal;
					vertex1 = Vector(radius*cos(v),radius*sin(v),0.0);
					vertex2 = Vector(radius*cos(v+div),radius*sin(div+v),0.0);
					vertex3 = Vector(radius*cos(v+div),radius*sin(div+v),0.0);
					v_normal = -(vertex1-vertex2)%(vertex2-vertex3);

					glNormal3f(v_normal.x, v_normal.y, v_normal.z);

					glVertex3f(vertex1.x,vertex1.y,vertex1.z);
					glVertex3f(vertex2.x,vertex2.y,vertex3.z);
					glVertex3f(vertex3.x,vertex3.y,vertex3.z);
					glVertex3f(radius*cos(v),radius*sin(v),0.0+height);

					vertex1 = Vector(radius*cos(v),radius*sin(v),0.0);
					vertex2 = Vector(radius*cos(v+div),radius*sin(div+v),0.0);
					vertex3 = Vector(0.0,0.0,0.0);
					v_normal = -(vertex1-vertex2)%(vertex2-vertex3);

					glNormal3f(v_normal.x, v_normal.y, v_normal.z);
	
					glVertex3f(vertex1.x,vertex1.y,vertex1.z);
					glVertex3f(vertex2.x,vertex2.y,vertex3.z);
					glVertex3f(vertex3.x,vertex3.y,vertex3.z);
					glVertex3f(0.0,0.0,0.0);

					vertex1 = Vector(0.0,0.0,height+2.8);
					vertex2 = Vector(0.0,0.0,height+2.8);
					vertex3 = Vector(radius*cos(v+div),radius*sin(v+div),0.0);
					v_normal = -(vertex1-vertex2)%(vertex2-vertex3);

					glNormal3f(v_normal.x, v_normal.y, v_normal.z);

					glVertex3f(vertex1.x,vertex1.y,vertex1.z);
					glVertex3f(vertex2.x,vertex2.y,vertex3.z);
					glVertex3f(vertex3.x,vertex3.y,vertex3.z);
					glVertex3f(radius*cos(v),radius*sin(v),0.0+height);
		}
	}
	glEnd();
}

void DrawSideFoot() {
	//oldallap, kulso
	glBegin(GL_POLYGON);
		glNormal3f(-1.0, 0.0, 0.0);

		glTexCoord2f(0.0f,0.0f);
		glVertex3f(0.0, 3.0, -10.0);
		glVertex3f(0.0, 3.3, -9.0);
		
		glVertex3f(0.0, 3.3, 9.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0, 3.0, 10.0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.0, 0.0, 8.0);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0, 0.0, -8.0);
	glEnd();
	//oldallap, belso
	glBegin(GL_POLYGON);
		glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(4.0, 3.0, -10.0);
		glVertex3f(4.0, 3.3, -9.0);
		
		glVertex3f(4.0, 3.3, 9.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(4.0, 3.0, 10.0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4.0, 0.0, 8.0);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(4.0, 0.0, -8.0);
	glEnd();
	//ket oldallap kozott a negyszog lapok
	glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0, 3.0, -10.0);glTexCoord2f(0.0f, 1.0f);
		glVertex3f(4.0, 3.0, -10.0);glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.0, 3.3, -9.0);glTexCoord2f(1.0f, 0.0f);
		glVertex3f(4.0, 3.3, -9.0);glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0, 3.3, 9.0);glTexCoord2f(0.0f, 0.0f);
		glVertex3f(4.0, 3.3, 9.0);glTexCoord2f(1.0f,0.0f);
		glVertex3f(0.0, 3.0, 10.0);glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4.0, 3.0, 10.0);glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0, 0.0, 8.0);glTexCoord2f(0.0f, 0.0f);
		glVertex3f(4.0, 0.0, 8.0);glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0, 0.0, -8.0);glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4.0, 0.0, -8.0);glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0, 3.0, -10.0);glTexCoord2f(0.0f, 0.0f);
		glVertex3f(4.0, 3.0, -10.0);
	glEnd();

}

void DrawTankBody() {
	
			//kozepso test
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-1.0, 0.0, -1.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(1.0, 0.0, -1.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.0, 0.0, 1.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-1.0, 0.0, 1.0);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(1.0, 0.0, 1.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-1.0, 0.0, 1.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-1.0, 0.65, 1.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.0, 0.65, 1.0);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-1.0, 0.65, 1.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(1.0, 0.65, 1.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.0, 0.65, -1.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-1.0, 0.65, -1.0);
	glEnd();

	glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-1.0, 0.0, 1.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-1.0, 0.65, 1.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-1.0, 0.65, -1.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-1.0, 0.0, -1.0);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-1.0, 0.65, -1.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-1.0, 0.0, -1.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.0, 0.0, -1.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.0, 0.65, -1.0);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(1.0, 0.0, -1.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(1.0, 0.65, -1.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.0, 0.65, 1.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.0, 0.0, 1.0);

	glEnd();
}

void DrawLTHat(void) {

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.0, 0.0, -2.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(2.0, 0.0, -2.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(2.5, 0.0, 3.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-2.5, 0.0, 3.0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.0, 0.0, -2.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(2.0, 0.0, -2.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.5, 2.0, -0.9);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-0.5, 2.0, -0.9);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.5, 0.0, 3.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(2.5, 0.0, 3.0);
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(0.5, 2.0, -0.9);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-0.5, 2.0, -0.9);
		glEnd();
		glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.0, 0.0, -2.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-2.5, 0.0, 3.0);
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(-0.5, 2.0, -0.9);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(2.0, 0.0, -2.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(2.5, 0.0, 3.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.5, 2.0, -0.9);
		glEnd();

}

void DrawLT(float radius, float height, float div) {

glBegin(GL_QUADS);
	for(float i = 0; i <= div; i++) {
		float v = float(i);
					Vector vertex1, vertex2, vertex3, vertex4, v_normal;
					vertex1 = Vector(radius*cos(v),radius*sin(v),0.0);
					vertex2 = Vector(radius*cos(v+div),radius*sin(div+v),0.0);
					vertex3 = Vector(radius*cos(v+div),radius*sin(div+v),0.0);
					v_normal = -(vertex1-vertex2)%(vertex2-vertex3);

					glNormal3f(v_normal.x, v_normal.y, v_normal.z);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(vertex1.x,vertex1.y,vertex1.z);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(vertex2.x,vertex2.y,vertex3.z);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(vertex3.x,vertex3.y,vertex3.z);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(radius*cos(v),radius*sin(v),0.0+height);

					vertex1 = Vector(radius*cos(v),radius*sin(v),0.0);
					vertex2 = Vector(radius*cos(v+div),radius*sin(div+v),0.0);
					vertex3 = Vector(0.0,0.0,0.0);
					v_normal = -(vertex1-vertex2)%(vertex2-vertex3);

					glNormal3f(v_normal.x, v_normal.y, v_normal.z);
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(vertex1.x,vertex1.y,vertex1.z);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(vertex2.x,vertex2.y,vertex3.z);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(vertex3.x,vertex3.y,vertex3.z);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(0.0,0.0,0.0);

					vertex1 = Vector(0.0,0.0,0.0);
					vertex2 = Vector(0.0,0.0,0.0);
					vertex3 = Vector(radius*cos(v+div),radius*sin(div+v),0.0);
					v_normal = -(vertex1-vertex2)%(vertex2-vertex3);

					glNormal3f(v_normal.x, v_normal.y, v_normal.z);
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(vertex1.x,vertex1.y,vertex1.z);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(vertex2.x,vertex2.y,vertex3.z);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(vertex3.x,vertex3.y,vertex3.z);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(radius*cos(v),radius*sin(v),0.0+height);
	}
	glEnd();
}

void DrawVehicle(float shot_angle, float turret_lookat, GLuint tex) {

	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SHININESS, Tank_ShineSurface);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);
	glTranslatef(0.0, -6.0, -9.5);
	DrawTankBody();
	glTranslatef(0.8, -0.1, 0.0);
	glScalef(0.28, 0.28, 0.28);
	DrawSideFoot();
	glTranslatef(-10.0, 0.0, 0.0);
	DrawSideFoot();
	glTranslatef(7.0, 2.5, 0.0);
	glScalef(0.68, 0.68, 0.68);
	glRotatef(turret_lookat, 0.0, 1.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	DrawLT(5.0, 2.0, 80.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 1.0, 0.0);

	DrawLTHat();
	glTranslatef(0.0, 0.0, 0.0);
	
	glRotatef(-shot_angle, 1.0, 0.0, 0.0);
	DrawTheGun(1.0, 32.0, 32.0);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glDeleteTextures(1,&tex);
	
}

void dISPLAY(float ang, float cannon_pitch, float turret_rotate) {

	GLuint g_textureId2 = MakeTexture();

	float lx = sin(ang);		//forgatashoz kell
	float lz = -cos(ang);
	float ly;
	ly = 0.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0 , -20.0, 40.0, 			//eye
		      0.0+ lx,-20.0 + ly,40.0 + lz,	//lookat
			  0.0f,-1.0f,0.0f);				//updir

	float j = 0.0f;
	float startx = 500.0f;
	float startz = 80.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Field_DIFFUSE);

	glBegin(GL_QUADS);
	for(;j<1000;j+=4) {
		float i = 0.0f;
		for(;i<1000;i+=4) {
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(startx-j, 1.0f, startz-i);
			glVertex3f(startx-j, 1.0f, startz-i-4.0f);
			glVertex3f(startx-j-4.0f, 1.0f, startz-i-4.0f);
			glVertex3f(startx-j-4.0f, 1.0f, startz-i);
		}
	}
	glEnd();
	
	glTranslatef(135.0,0.0,20.0);
	glRotatef(50, 0.0, 1.0, 0.0);
	glScalef(2.0, 2.0, 2.0);
	
	int n = 7;
	int m = 9;
	
	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_SPECULAR, PyramidSpecularSurface);
	glMaterialfv(GL_FRONT, GL_SHININESS, PyramidShineSurface);

	for(int i = 0; i < n; i++) {
		glTranslatef(0.0,0.0,-40.0);
		for(int j = 0; j < m; j++) {
			glTranslatef(50.0,0.0,0.0);
			if(j == m-1) glTranslatef(-j*60.0, 0.0, 0.0); 			//carriage return:)
				DrawPyramid();
		}
	}
	glLoadIdentity();
	
	DrawVehicle(20.0+cannon_pitch, 20.0+turret_rotate, g_textureId2);

	glMaterialfv(GL_FRONT, GL_AMBIENT, BulletAmbient);
	glMaterialf(GL_FRONT, GL_SHININESS, BulletShineSurface);

	glMaterialfv(GL_FRONT, GL_EMISSION, Emission);

	glTranslatef(0.0+cannon_pitch*10, 0.0+turret_rotate*10, 40.0+ang*10);
	DrawBullet(0.95, 2.4, 26.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Zero);
	glMaterialf(GL_FRONT, GL_SHININESS, ZeroShineSurface);
	glMaterialfv(GL_FRONT, GL_EMISSION, Zero);
	
	}

void onInitialization( ) { 

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_FOG);

	float FogCol[3]={0.73f,0.73f,0.85f}; 
  	glFogfv(GL_FOG_COLOR,FogCol);  

	glFogi(GL_FOG_MODE, GL_LINEAR); 
  	glFogf(GL_FOG_START, 28.f);
  	glFogf(GL_FOG_END, 450.f);		

	glFogf(GL_FOG_DENSITY, 1.f);

	float LightDiffuse[] = {0.0, 1.0, 0.0, 1.0};
	float LightSpecular[] = {0.0, 1.0, 0.0, 1.0};									
	float LightPosition[] = {100*cos(20.0), 100*sin(20.0), -100.0, 0.0};			//4. koord 0 -> iranyfenyforras
	float Shininess[] = { 30.0 };							//lightpos 1.param-e pozitiv, keletrol sut a nap..

	GLfloat SkyAmbient[] = { 0.05f, 0.58f, 0.74f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, SkyAmbient);			//Egbolt ambiens fenye, uolyan szinu mint a 'hatter'

	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, LightDiffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	//glLightfv(GL_LIGHT0, GL_SHININESS, Shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	//glEnable(GL_LIGHT0);	

	glViewport(0, 0, w_width, w_height);						//kepernyo transzformacio
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (w_height == 0) ? 1.0 : w_width / w_height;
	gluPerspective(113, aspect, 1, 800);							//perspektiv transzf, szeles latokor:)

// ********************* Cg Init Begin********************* \\
	
	cgContext = cgCreateContext();
	
	if (cgContext == NULL)
	{
		cout << "Failed to create Cg context" << endl;				
	}

	cgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);	
	cgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);


	if (cgVertexProfile == CG_PROFILE_UNKNOWN)
	{
		cout << "Graphics card does not support Vertex Profile!" << endl;			
	}

	if (cgFragmentProfile == CG_PROFILE_UNKNOWN)
	{
		cout << "Graphics Card Does Not Support Fragment Profile!" << endl;			
	}

	cgGLSetOptimalOptions(cgVertexProfile);	
	cgGLSetOptimalOptions(cgFragmentProfile);	
	
	//Compile
	myVertexProgram = cgCreateProgramFromFile(cgContext, CG_SOURCE, "Vertex2.cg", cgVertexProfile, "my_vertex_shader", 0);

	myFragmentProgram = cgCreateProgramFromFile(cgContext, CG_SOURCE, "Fragment.cg", cgFragmentProfile, "my_fragment_shader", 0);
	
	if (myVertexProgram == NULL)
	{
		CGerror Error = cgGetError();

		cout <<  cgGetErrorString(Error) << endl;
	}

	if (myFragmentProgram == NULL)
	{
		CGerror Error = cgGetError();

		cout <<  cgGetErrorString(Error) << endl;
	}

	//FragmentColor = cgGetNamedParameter(myFragmentProgram, "IN.color");
	//cgGLSetParameter4f(FragmentColor, 1.0, 0.0, 0.0, 1.0);

	//Upload programs to the GPU
	cgGLLoadProgram(myVertexProgram);
	//cgGLLoadProgram(myFragmentProgram);

#define GET_PARAM(name) \
		name = \
    cgGetNamedParameter(name); \
  checkForCgError("could not get " #name " parameter");

  GET_PARAM(modelViewProj);
  GET_PARAM(globalAmbient);
  GET_PARAM(lightColor);
  GET_PARAM(lightPosition);
  GET_PARAM(eyePosition);
  GET_PARAM(Ke);
  GET_PARAM(Ka);
  GET_PARAM(Kd);
  GET_PARAM(Ks);
  GET_PARAM(shininess);

  /* Set light source color parameters once. */
  cgSetParameter3fv(myCgVertexParam_globalAmbient, myGlobalAmbient);
  cgSetParameter3fv(myCgVertexParam_lightColor, myLightColor);

					// Before executing a program in OpenGL, enable its corresponding profile.
					cgGLEnableProfile(cgVertexProfile);
					//cgGLEnableProfile(cgFragmentProfile);

					//Select program on GPU to run
					cgGLBindProgram(myVertexProgram);
					//cgGLBindProgram(myFragmentProgram);

					// Set The Modelview Matrix Of Our Shader To Our OpenGL Modelview Matrix
					cgGLSetStateMatrixParameter(modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
					cgGLSetParameter3f(globalAmbient, 0.05f, 0.58f, 0.74f);
					cgGLSetParameter3f(lightColor, 1.0, 0.0, 0.0);
					cgGLSetParameter3f(lightPosition, 100*cos(20.0), 100*sin(20.0), -100.0);
					cgGLSetParameter3f(eyePosition, 0.0 , -20.0, 40.0);

					

	
	// ********************* Cg Init End ********************* \\

}
float angle, ang;
float turret_rotate, cannon_pitch;

void onDisplay( ) {
	glClearColor(0.15f, 0.58f, 0.74f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	dISPLAY(angle, cannon_pitch, turret_rotate);

	glutSwapBuffers();
}

void onKeyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'w' : 
			cannon_pitch += 0.1f;
			glClearColor(0.15f, 0.58f, 0.74f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			dISPLAY(angle, cannon_pitch, turret_rotate);
			
			glutSwapBuffers();
			break;
		case 's' : 
			cannon_pitch -= 0.1f;
			glClearColor(0.15f, 0.58f, 0.74f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			dISPLAY(angle, cannon_pitch, turret_rotate);
			
			glutSwapBuffers();
			break;
			case 'a' :
			glClearColor(0.15f, 0.58f, 0.74f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			turret_rotate -= 0.1;
			dISPLAY(angle, cannon_pitch, turret_rotate);
			
			glutSwapBuffers();
			break;
			case 'd' :
			glClearColor(0.15f, 0.58f, 0.74f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			turret_rotate += 0.1;
			dISPLAY(angle, cannon_pitch, turret_rotate);
			
			glutSwapBuffers();
			break;
		case 'x' :
			glClearColor(0.15f, 0.58f, 0.74f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			angle += 0.1;
			dISPLAY(angle, cannon_pitch, turret_rotate);
			
			glutSwapBuffers();
			break;
		case 'c' :
			glClearColor(0.15f, 0.58f, 0.74f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			angle -= 0.1;
			dISPLAY(angle, cannon_pitch, turret_rotate);
			
			glutSwapBuffers();
			break;
	}
}


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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

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

	  /* Initialize OpenGL entry points. */
  if (glewInit()!=GLEW_OK || !GLEW_VERSION_1_1) {
    fprintf(stderr, "%s: failed to initialize GLEW, OpenGL 1.1 required.\n", myProgramName);    
    exit(1);
  }

	glutMainLoop();

	cgDestroyProgram(myVertexProgram);										//Free resources allocated for a single program
	
	cgDestroyContext(cgContext);										//Free all the resources allocated for a context

	return 0;
}

