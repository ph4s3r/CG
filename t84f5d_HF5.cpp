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
// Nev    : KARACSONYI PETER
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

#define new minek_new

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Innentol modosithatod...

#define PI 3.14159265

//Ablakmeret
#define w_width 600
#define w_height 600

//Targyak tesszellaciojanak reszletessege (csak paros szam lehet)
#define tess_div 100

//Nezopont valtozo
float cam_angle, temp1, temp2;

//Nap
float SunPosition[4];

//textura kellekek
#define TexSize 32
#define TexSize_Road 32
GLfloat TexImg[TexSize][TexSize][3];	//textura tomb
GLuint g_textureId[2];						//textura azonosito: 0 a terep, 1 a tobbi

//Mindenhol hasznalt anyagtulajdonsagok
const GLfloat Shininess[] = { 20.0 };
const GLfloat No_Mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat No_Shine[] = {0.0f};

//Csirke anyagtulajdonsagai
const GLfloat RedSurface[] = {1.0f, 0.1f, 0.1f, 1.0};
const GLfloat YellowSurface[] = {1.0f, 1.0f, 0.1f, 1.0};

//Arnyek matrix
float shadow[4][4];

class Vector {
	//===============================================================
public:
	float x, y, z;

	Vector() {}
	Vector(float xx, float yy, float zz) {
		x = xx; y = yy; z = zz;
	}

	// binary operators
	Vector operator+(const Vector& c) const {
		return Vector(x + c.x, y + c.y, z + c.z);
	}

	Vector operator-(const Vector& c) const {
		return Vector(x - c.x, y - c.y, z - c.z);
	}

	Vector operator*(float f) const {				//Skalar
		return Vector(x * f, y * f, z * f);
	}

	Vector operator-(void) const { 
		return Vector(-x, -y, -z);
	}

	Vector operator%(const Vector& v) const {		//Kereszt
		return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	void operator+=( const Vector& v ) {  // vektor összeadás
		x += v.x; y += v.y; z += v.z; 
	}
	void operator-=( const Vector& v ) {  // vektor különbség
		x -= v.x; y -= v.y; z -= v.z; 
	}
	void operator*=( float f ) {		  // vektor és szám szorzata
		x *= f; y *= f; z *= f; 
	}
	float Len(void) const {
		return sqrt(x*x + y*y + z*z);
	}

};

class Matrix {
//===============================================================
public:
	float m[4][4];

	Matrix( ) { Clear(); m[3][3] = 1; }
	Matrix( float d1, float d2, float d3 ) {
		Clear();
		m[0][0] = d1; m[1][1] = d2; m[2][2] = d3; m[3][3] = 1;
	}
	void Clear( ) {  // a mátrixelemek törlése
		memset( &m[0][0], 0, sizeof( m ) );
	}
	void LoadIdentity( ) { // a mátrix legyen egységmátrix
		Clear();
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
	}
	Matrix operator+( const Matrix& mat ) { // mátrix összeadás
		Matrix result;
		for( int i = 0; i < 4; i++ )
			for( int j = 0; j < 4; j++ ) result.m[i][j] = m[i][j]+mat.m[i][j];
		return result;
	}
	Matrix operator*( const Matrix& mat ) { // mátrixok szorzása
		Matrix result;
		for( int i = 0; i < 4; i++ )
			for( int j = 0; j < 4; j++ ) {
				result.m[i][j] = 0;
				for( int k = 0; k < 4; k++ ) result.m[i][j] += m[i][k] * mat.m[k][j];
			}
			return result;
	}
	Vector operator*( const Vector& v ) {  // Vektor transzformációja
		float Xh = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
		float Yh = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
		float Zh = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
		float  h = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];
		return Vector(Xh/h, Yh/h, Zh/h);
	}
	Matrix Transpose( ) {
		Matrix result;
		for( int i = 0; i < 4; i++ )
			for( int j = 0; j < 4; j++ ) result.m[j][i] = m[i][j];
		return result;
	}
	Vector Transform( Vector& v ) {
		return Vector( v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
			           v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
				       v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2]);
	}
	float * GetArray() { return &m[0][0]; }
};

//Textura tomb proceduralis generalasa
void GenTexture(int TSize) {
	for(int y=0;y<TSize; y++){
        for(int x=0;x<TSize; x++){
		
	  float random = (rand()%100)/100.0;

      TexImg[x][y][0] = random-0.15;
      TexImg[x][y][1] = random-0.16;
      TexImg[x][y][2] = random-0.2;

		}
	}
}

GLuint MakeTexture(int TSize) {
	GenTexture(TSize);
			GLuint texture_id;
               glGenTextures(1, &texture_id);
               glBindTexture(GL_TEXTURE_2D, texture_id);
			   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);				//bilinearis szures	
			   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TSize, TSize, 0, GL_RGB, GL_FLOAT, TexImg);
	return texture_id;
}

//Fuves,lapos, zold diffuz terep, kozepen texturazott aszfalt ut

void DrawAsphaltAndField() {

	const GLfloat Fieldsurface_da[] = {0.1f, 0.7f, 0.1f, 1.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Fieldsurface_da);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Fieldsurface_da);
	glMaterialfv(GL_FRONT, GL_EMISSION, No_Mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, No_Mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, No_Shine);

	glDisable(GL_TEXTURE_2D);

	//QUADOK merete:
	//XZ-ben: 500-250, 250-0, 0--250, -250-500
	float j = 0.0f;
	float startx = 500.0f;
	float startz = 500.0f;

	glBegin(GL_QUADS);
	for(;j<=(float)750.0;j+=(float)250.0) {
		float i = 0.0f;
		for(;i<=(float)750.0;i+=(float)250.0) {

			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(startx-(float)j, 0.0f, startz-(float)i);
			
			glVertex3f(startx-(float)j, 0.0f, startz-(float)i-250.0f);

			glVertex3f(startx-(float)j-250.0f, 0.0f, startz-(float)i-250.0f);
		
			glVertex3f(startx-(float)j-250.0f, 0.0f, startz-(float)i);

		}
	}
	glEnd();

	//Az aszfalt ut az xz sikon fekszik 
	
	const GLfloat Roadsurface_da[] = {1.0f, 0.9f, 0.9f, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Roadsurface_da);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,g_textureId[0]);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_QUADS);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-500.0f, -0.1f, -10.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-500.0f, -0.1f, 10.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(500.0f, -0.1f, 10.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(500.0f, -0.1f, -10.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);

}

//Alap parametrikus felulet fuggvenyek

//Henger (texturazhato)
void Cylinder(  float height,				//henger magassága
				float radius) {				//henger sugara

		float angle;		// hengerlap felosztas fokban

		float heightInc = (float)height/tess_div;		// hengerpalast felosztott darabok merete

		//Henger felso lap rajzolasa triangle fan-nal
		glBegin( GL_TRIANGLE_FAN );

		glNormal3f(0.0f,1.0f,0.0f);	//felfele mutato normalvektorok
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(0.0f,0.5f*height,0.0f);

		for(int i=0;i<=tess_div;++i)	{	//tess_div: itt hengerlap felosztas (db resz)

			angle = (float)i*(-2*PI)/tess_div;
			glTexCoord2f(radius*cos(angle),radius*sin(angle));
			glVertex3f(radius*cos(angle),0.5f*height,radius*sin(angle));

		}

		glEnd();

		//Henger also lap triangle fan-nal
		glBegin( GL_TRIANGLE_FAN );
		glNormal3f(0.0f,-1.0f,0.0f); //lefele mutato normalvektorok
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(0.0f,-0.5f*height,0.0f);

		for(int i=0;i<=tess_div;++i)	{	//tess_div: itt hengerlap felosztas (db resz)

			angle = (float)i*(2*PI)/tess_div;
			glTexCoord2f(radius*cos(angle),radius*sin(angle));
			glVertex3f(radius*cos(angle),-0.5f*height,radius*sin(angle));

		}

		glEnd();

		//Henger palast quad-strip-el (szabalyos kocka lapok)
		for(int i=0;i<tess_div;++i) {	//tess_div: itt hengerpalast felosztas (db resz)

			float fCurrMin = -0.5f*height + heightInc*i,	//egy negyzetlap i. also koordinataja
				fCurrMax = fCurrMin + heightInc;			//felso
			glBegin( GL_QUAD_STRIP );
			for(int j=0;j<=tess_div;++j)	{

				//egy kocka-lap elso ket koordinataja + normalvektor + textura
				float cos_alpha, sin_alpha;
				angle = (float)j*(2*PI)/tess_div;
				cos_alpha = radius*cos(angle);
				sin_alpha = radius*sin(angle);
				glNormal3f(cos_alpha,0.0f,sin_alpha);
				glTexCoord2f(0.0f,0.0f);
				glVertex3f(cos_alpha,fCurrMin,sin_alpha);
				glTexCoord2f(1.0f,0.0f);
				glVertex3f(cos_alpha,fCurrMax,sin_alpha);

				//egy kocka-lap masik ket koordinataja
				angle = (float)(j+1)*(2*PI)/tess_div;
				cos_alpha = radius*cos(angle);
				sin_alpha = radius*sin(angle);
				glNormal3f(cos_alpha,0.0f,sin_alpha);
				glTexCoord2f(0.0f,1.0f);
				glVertex3f(cos_alpha,fCurrMin,sin_alpha);
				glTexCoord2f(1.0f,1.0f);
				glVertex3f(cos_alpha,fCurrMax,sin_alpha);

			}			
			glEnd();
		}
}

void Ellipsoid(float a, float b, float c) {

	glBegin(GL_QUADS);

	for(int i=1;i<tess_div;i++){

		float angle_v = (float)i*(2*PI)/tess_div;
		float angle_v_next = (float)(i+1)*(2*PI)/tess_div;

		for(int j=1;j<tess_div;j++){
				
			float angle_u = (float)j*(2*PI)/tess_div;
			float angle_u_next = (float)(j+1)*(2*PI)/tess_div;

			Vector v1,v2,v3,v4,v_normal;

			v1 = Vector(a*cos(angle_u)*sin(angle_v),c*cos(angle_v), b*sin(angle_u)*sin(angle_v));
			v2 = Vector(a*cos(angle_u_next)*sin(angle_v),c*cos(angle_v), b*sin(angle_u_next)*sin(angle_v));
			v3 = Vector(a*cos(angle_u_next)*sin(angle_v_next),c*cos(angle_v_next), b*sin(angle_u_next)*sin(angle_v_next));
			v4 = Vector(a*cos(angle_u)*sin(angle_v_next),c*cos(angle_v_next), b*sin(angle_u)*sin(angle_v_next));
			v_normal = -(v1-v2)%(v2-v3);

			glNormal3f(v_normal.x, v_normal.y, v_normal.z);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(v1.x, v1.y,v1.z);	
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(v2.x, v2.y, v2.z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(v3.x ,v3.y, v3.z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(v4.x ,v4.y, v4.z);	

		}
	}

	glEnd();
};

//Kup
void Cone(float height,			//kup magassága
		  float radius ){		//kup lapjanak sugara

	//Kup palast haromszogekbol
	glBegin( GL_TRIANGLES );
	for(int j=0;j<=tess_div;++j){

		float angle1 = (float)(j)*(2*PI)/tess_div;
		float angle_next = (float)(j+1)*(2*PI)/tess_div;

		Vector v1, v2, v3, v_normal;
		v1 = Vector(radius*cos(angle1), 0.0f, radius*sin(angle1));
		v2 = Vector(radius*cos(angle_next), 0.0f, radius*sin(angle_next));
		v3 = Vector(0.0f,height,0.0f);
		v_normal = -(v1-v2)%(v2-v3);

		glNormal3f(v_normal.x, v_normal.y, v_normal.z); //normalvektor a haromszog-lapbol kifele mutat
		glVertex3f(v1.x, v1.y,v1.z);	//v1 also 1
		glVertex3f(v2.x, v2.y, v2.z);	//v2 also 2
		glVertex3f(v3.x ,v3.y, v3.z);	//v3 kup teto

	}			
	glEnd();

	//Kup also lap triangle fan-nal
	glBegin( GL_TRIANGLE_FAN );
	glNormal3f(0.0f,-1.0f,0.0f); //lefele mutato normalvektorok
	glVertex3f(0.0f,0.0f,0.0f);	 //triangle-fan 0. vertexe a lap kozepe

	for(int i=0;i<=tess_div;++i)	{
		float angle = (float)i*(2*PI)/tess_div;
		glVertex3f(radius*cos(angle),0.0f,radius*sin(angle));
	}

	glEnd();
}

//Kamera transzformacio
void SetCameraTransform() {
		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (w_height == 0) ? 1.0 : w_width / w_height;
	gluPerspective(80, aspect, 1, 800);							//perspektiv transzf

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(23.0f*sinf(cam_angle), -15.0, 23.0f*cosf(cam_angle),			//szempozicio (eye)
		-10.0, 0.0, 0.0,					//nezeti referencia pont (lookat)
		0.0, -1.0, 0.0);				//felfele irany (updir)
	}
/*
class ShadowZbuffer 
	//===============================================================
{
	float Tc_inv[4][4];						//Adott XY pixelben a kepernyon melyik vilagkoordinatarendszerbeli vertexet latjuk
	float Tc[4][4];							//Egy adott vertexet a fenyforras 'kepernyojere' vetito trafo
	float Tcl[4][4];						//Fenti ket trafo szorzata
	float lightDepth[w_width*w_height];		//fenyforras z-buffer (egy XY pixelben lathato legkozelebbi vertex tavolsagerteke

public:
	ShadowZbuffer();
	void CalcCamTransForm(Vector &eye, Vector &lookAt, Vector &up){

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			float aspect = (w_height == 0) ? 1.0 : w_width / w_height;
			gluPerspective(80, aspect, 1, 800);							//perspektiv transzf

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			gluLookAt(23.0f*sinf(cam_angle), -15.0, 23.0f*cosf(cam_angle),			//szempozicio (eye)
				-10.0, 0.0, 0.0,					//nezeti referencia pont (lookat)
				0.0, -1.0, 0.0);				//felfele irany (updir)

			//A projekcios es modell-nezeti trafo mentese

			float Tproj[4][4], Tmview[4][4];
			glGetFloatv(GL_PROJECTION_MATRIX, &Tproj[0][0]);
			glGetFloatv(GL_MODELVIEW_MATRIX, &Tmview[0][0]);
			//MatrixConcat(Tmview, Tproj, Tc_inv);		//Tc_inv lesz a ket matrix szorzata
			//MatrixInvert(Tc_inv, Tc_inv);				//Kesz is

	}

	void CalcLightTransForm(Vector &light, Vector &lookAt, Vector &up){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			float aspect = (w_height == 0) ? 1.0 : w_width / w_height;
			gluPerspective(80, aspect, 1, 800);							//perspektiv transzf

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			gluLookAt(23.0f*sinf(cam_angle), -15.0, 23.0f*cosf(cam_angle),			//szempozicio (eye)
				-10.0, 0.0, 0.0,					//nezeti referencia pont (lookat)
				0.0, -1.0, 0.0);				//felfele irany (updir)

			//A projekcios es modell-nezeti trafo mentese

			float Tproj[4][4], Tmview[4][4];
			glGetFloatv(GL_PROJECTION_MATRIX, &Tproj[0][0]);
			glGetFloatv(GL_MODELVIEW_MATRIX, &Tmview[0][0]);
			//MatrixConcat(Tmview, Tproj, Tc_inv);		//Tc_inv lesz a ket matrix szorzata
			//MatrixInvert(Tc_inv, Tc_inv);				//Kesz is
	}
	bool ShadowZCheck(float x, float y, float z);
};
*/

class RoadRoller 
	//===============================================================
{
	Vector position;
	//Uthenger ket oldallapjanak pontjai (X-Y sikban), amiket majd osszekotunk
	Vector side_polygon_a[20];
	Vector side_polygon_b[20];

public:

	RoadRoller(){
		for(int i = 0; i < 20; i++) {
			side_polygon_a[i] = Vector(0.0, 0.0, 0.0);
			//Z-beli eltolas
			side_polygon_b[i] = Vector(0.0, 0.0, 4.5);
			position = Vector(0.0f, -8.1f, 0.0f);
		}

		side_polygon_a[0].x = 3.0;
		side_polygon_a[0].y = 5.3;

		side_polygon_a[1].x = 0.0;
		side_polygon_a[1].y = 5.3;

		side_polygon_a[2].x = 0.0;
		side_polygon_a[2].y = 4.8;

		side_polygon_a[3].x = 2.9;
		side_polygon_a[3].y = 4.8;

		side_polygon_a[4].x = 2.9;
		side_polygon_a[4].y = 2.0;

		side_polygon_a[5].x = 2.3;
		side_polygon_a[5].y = 2.0;

		side_polygon_a[6].x = 2.3;
		side_polygon_a[6].y = 1.6;

		side_polygon_a[7].x = 5.5;
		side_polygon_a[7].y = 1.6;

		side_polygon_a[8].x = 5.5;
		side_polygon_a[8].y = 2.0;

		side_polygon_a[9].x = 5.2;
		side_polygon_a[9].y = 2.0;

		side_polygon_a[10].x = 5.2;
		side_polygon_a[10].y = 4.8;

		side_polygon_a[11].x = 6.4;
		side_polygon_a[11].y = 4.8;

		side_polygon_a[12].x = 6.4;
		side_polygon_a[12].y = 0.0;

		side_polygon_a[13].x = 6.7;
		side_polygon_a[13].y = 0.0;

		side_polygon_a[14].x = 6.7;
		side_polygon_a[14].y = 4.8;

		side_polygon_a[15].x = 9.0;
		side_polygon_a[15].y = 4.8;

		side_polygon_a[16].x = 9.0;
		side_polygon_a[16].y = 5.3;

		side_polygon_a[17].x = 6.9;
		side_polygon_a[17].y = 5.3;

		side_polygon_a[18].x = 5.3;
		side_polygon_a[18].y = 7.0;

		side_polygon_a[19].x = 3.6;
		side_polygon_a[19].y = 7.0;


					//Rosszul sorszamoztam be a koordinatakat, ezert az egesz tomb shiftelese vissza 1-el
					for(int i = 0; i < 20; i++) {
						//Atteszem a 'b'-be az egesz feltoltott 'a' tombot 
						side_polygon_b[i].x = side_polygon_a[i].x;
						side_polygon_b[i].y = side_polygon_a[i].y;

					}
						//20. pont a 0. pont kell legyen
						side_polygon_a[19].x = side_polygon_b[0].x;
						side_polygon_a[19].y = side_polygon_b[0].y;

						for(int i = 0; i < 19; i++) {
							//Osszes tobbi mehet iteratorral
							side_polygon_a[i].x = side_polygon_b[i+1].x;
							side_polygon_a[i].y = side_polygon_b[i+1].y;
						}

		//Visszatoltjuk b-be a, mar jo tombot
		for(int i = 0; i < 20; i++) {
			side_polygon_b[i].x = side_polygon_a[i].x;
			side_polygon_b[i].y = side_polygon_a[i].y;
		}
		
	}

	void Dock() {

		const GLfloat Rollersurface_d[] = {0.7f, 0.7f, 0.7f, 1.0};
		const GLfloat Rollersurface_s[] = {0.3f, 0.7f, 1.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Rollersurface_d);
		glMaterialfv(GL_FRONT, GL_EMISSION, No_Mat);
		glMaterialfv(GL_FRONT, GL_SPECULAR, Rollersurface_s);
		glMaterialfv(GL_FRONT, GL_SHININESS, No_Shine);

		glPushMatrix();
			glScalef(2.0f, 2.0f, 2.0f);
			glTranslatef(position.x, position.y, position.z);

			//Eloszor a ket oldallap segitsegevel felrajzoljuk az uthenger palastot
			glBegin(GL_QUADS);

			for(int i = 0; i < 20; i++){
				glVertex3f(side_polygon_b[i].x, side_polygon_b[i].y, side_polygon_b[i].z);
				glVertex3f(side_polygon_a[i].x, side_polygon_a[i].y, side_polygon_a[i].z);
				glVertex3f(side_polygon_a[i+1].x, side_polygon_a[i+1].y, side_polygon_a[i+1].z);
				glVertex3f(side_polygon_b[i+1].x, side_polygon_b[i+1].y, side_polygon_b[i+1].z);
			
			}

			glEnd();

			//Majd a ket oldallap felrajzolasa
		
			glBegin(GL_QUADS);
			//1
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(side_polygon_b[0].x, side_polygon_b[0].y, side_polygon_b[0].z);
			glVertex3f(side_polygon_b[1].x, side_polygon_b[1].y, side_polygon_b[1].z);
			glVertex3f(side_polygon_b[14].x, side_polygon_b[14].y, side_polygon_b[14].z);
			glVertex3f(side_polygon_b[15].x, side_polygon_b[15].y, side_polygon_b[15].z);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(side_polygon_a[0].x, side_polygon_a[0].y, side_polygon_a[0].z);
			glVertex3f(side_polygon_a[1].x, side_polygon_a[1].y, side_polygon_a[1].z);
			glVertex3f(side_polygon_a[14].x, side_polygon_a[14].y, side_polygon_a[14].z);
			glVertex3f(side_polygon_a[15].x, side_polygon_a[15].y, side_polygon_a[15].z);
			//2
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(side_polygon_b[16].x, side_polygon_b[16].y, side_polygon_b[16].z);
			glVertex3f(side_polygon_b[17].x, side_polygon_b[17].y, side_polygon_b[17].z);
			glVertex3f(side_polygon_b[18].x, side_polygon_b[18].y, side_polygon_b[18].z);
			glVertex3f(side_polygon_b[19].x, side_polygon_b[19].y, side_polygon_b[19].z);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(side_polygon_a[16].x, side_polygon_a[16].y, side_polygon_a[16].z);
			glVertex3f(side_polygon_a[17].x, side_polygon_a[17].y, side_polygon_a[17].z);
			glVertex3f(side_polygon_a[18].x, side_polygon_a[18].y, side_polygon_a[18].z);
			glVertex3f(side_polygon_a[19].x, side_polygon_a[19].y, side_polygon_a[19].z);

			//3
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(side_polygon_b[2].x, side_polygon_b[2].y, side_polygon_b[2].z);
			glVertex3f(side_polygon_b[3].x, side_polygon_b[3].y, side_polygon_b[3].z);
			glVertex3f(side_polygon_b[8].x, side_polygon_b[8].y, side_polygon_b[8].z);
			glVertex3f(side_polygon_b[9].x, side_polygon_b[9].y, side_polygon_b[9].z);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(side_polygon_a[2].x, side_polygon_a[2].y, side_polygon_a[2].z);
			glVertex3f(side_polygon_a[3].x, side_polygon_a[3].y, side_polygon_a[3].z);
			glVertex3f(side_polygon_a[8].x, side_polygon_a[8].y, side_polygon_a[8].z);
			glVertex3f(side_polygon_a[9].x, side_polygon_a[9].y, side_polygon_a[9].z);

			//4
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(side_polygon_b[4].x, side_polygon_b[4].y, side_polygon_b[4].z);
			glVertex3f(side_polygon_b[5].x, side_polygon_b[5].y, side_polygon_b[5].z);
			glVertex3f(side_polygon_b[6].x, side_polygon_b[6].y, side_polygon_b[6].z);
			glVertex3f(side_polygon_b[7].x, side_polygon_b[7].y, side_polygon_b[7].z);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(side_polygon_a[4].x, side_polygon_a[4].y, side_polygon_a[4].z);
			glVertex3f(side_polygon_a[5].x, side_polygon_a[5].y, side_polygon_a[5].z);
			glVertex3f(side_polygon_a[6].x, side_polygon_a[6].y, side_polygon_a[6].z);
			glVertex3f(side_polygon_a[7].x, side_polygon_a[7].y, side_polygon_a[7].z);
		
			//5
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(side_polygon_b[10].x, side_polygon_b[10].y, side_polygon_b[10].z);
			glVertex3f(side_polygon_b[11].x, side_polygon_b[11].y, side_polygon_b[11].z);
			glVertex3f(side_polygon_b[12].x, side_polygon_b[12].y, side_polygon_b[12].z);
			glVertex3f(side_polygon_b[13].x, side_polygon_b[13].y, side_polygon_b[13].z);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(side_polygon_a[10].x, side_polygon_a[10].y, side_polygon_a[10].z);
			glVertex3f(side_polygon_a[11].x, side_polygon_a[11].y, side_polygon_a[11].z);
			glVertex3f(side_polygon_a[12].x, side_polygon_a[12].y, side_polygon_a[12].z);
			glVertex3f(side_polygon_a[13].x, side_polygon_a[13].y, side_polygon_a[13].z);

			glEnd();
		
			//Utolsokent pedig a hengerek
		
			glPushMatrix();
			//A henger az y tengely korul 'rajzolodik', elforgatjuk
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, g_textureId[1]);

			glTranslatef(0.0, 6.0, 0.0);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0, 2.25, 0.0);
				Cylinder(4.5, 2.0);
			//Inkr. eltolas (hatra)
			glTranslatef(9.5, 0.0, 0.0);
				Cylinder(4.5, 2.0);

			glPopMatrix();
		
		glPopMatrix();

	}
};

class Chicken {
	//===============================================================
	Vector position;
	//Labak elore s hatra mozgathatok, a fej forgathato a nyak tengelyen 
	float LeftFoot_angle, RightFoot_angle, Head_angle;

public:

	Chicken() {
		position = Vector(-20.0f, -8.0f, 2.5f);
		LeftFoot_angle = -20.0f;
		RightFoot_angle = 20.0f;
		Head_angle = 0.0f;
	}
	void ShowUp() {

		glPushMatrix();			

			Body(Vector(position.x, position.y, position.z));

			//Csirke fej: pos, lookat angle 
			Head(Vector(-1.8f, -3.8f, 0.0f), 0.0f);

			//Labak
			Foot(Vector(0.0f, 0.0f, -0.5f), RightFoot_angle);
			Foot(Vector(0.0f, 0.0f, -2.5f), LeftFoot_angle);

	
		glPopMatrix();
	}

	void Head(Vector pos, float lookat) {
		glPushMatrix();
		//Hianyzik a forgatas
			glTranslatef(pos.x, pos.y, pos.z);
			glRotatef(Head_angle, 0.0f, 1.0f, 0.0f);
			//Textures off
			glDisable(GL_TEXTURE_2D);
				//A fej egy ellipszoid
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YellowSurface);
					glMaterialfv(GL_FRONT, GL_SPECULAR, YellowSurface);
				Ellipsoid(1.0, 1.0, 1.0);

				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RedSurface);
					glMaterialfv(GL_FRONT, GL_SPECULAR, RedSurface);
				
				//Csor 
				glPushMatrix();
				glTranslatef(-0.5f,0.0f,0.0f);
				glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
				Cone(1.9, 0.3);

				//Taraj
				glTranslatef(0.0f, -1.0f, 0.0f);
				glRotatef(160.0f, 0.0f, 0.0f, 1.0f);
				Cone(1.6, 0.1);
				glTranslatef(-0.3f, -0.3f, 0.0f);
				glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
				Cone(1.6, 0.1);
				glTranslatef(0.0f, -0.3f, 0.0f);
				glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
				Cone(1.6, 0.1);
				glPopMatrix();

			glPopMatrix();

	}

	void Body(Vector pos) {
		glTranslatef(pos.x, pos.y, pos.z);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, g_textureId[1]);
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YellowSurface);
					glMaterialfv(GL_FRONT, GL_SPECULAR, YellowSurface);
			//Csirke test
			Ellipsoid(1.5, 2.1, 3.3);
		glDisable(GL_TEXTURE_2D);
			//Farok
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RedSurface);
					glMaterialfv(GL_FRONT, GL_SPECULAR, RedSurface);
			glPushMatrix();
			glTranslatef(1.0f,0.0f,0.0f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			Cone(1.9, 0.3);
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glTranslatef(2.0f, 0.0f, 0.0f);
			Ellipsoid(0.4, 1.2, 1.2);
			glPopMatrix();

			glDisable(GL_TEXTURE_2D);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YellowSurface);
					glMaterialfv(GL_FRONT, GL_SPECULAR, YellowSurface);
			//Csirke nyak
			glPushMatrix();
			glTranslatef(-1.4f, -3.2f, 0.0f);
			glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
				Cylinder(2.32, 0.4);
			glPopMatrix();

	}

	void Foot(Vector pos, float angle) {
				glPushMatrix();
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YellowSurface);
					glMaterialfv(GL_FRONT, GL_SPECULAR, YellowSurface);
				glTranslatef(pos.x,pos.y,pos.z);
				glRotatef(angle, 0.0f, 0.0f, 1.0f);
					//Comb
					glPushMatrix();
						glTranslatef(0.0f, 3.0f, 2.0f);
						Cylinder(2.6, 0.2);

						//Also labszar
						glTranslatef(0.75f, 2.1f, 0.0f);
						glRotatef(-35.0f, 0.0f, 0.0f, 1.0f);
						Cylinder(2.6, 0.2);

						//Labfej
						glRotatef(80.0f, 0.0f, 0.0f, 1.0f);
						glTranslatef(1.0f, 1.5f, 0.0f);
						Cylinder(2.6, 0.2);
					glPopMatrix();

				glPopMatrix();
	}

	void Animate(float dt) {
		Head_angle = temp1;
		Head_angle = -temp2;

	}

};

// Inicializacio, a program futasanak kezdeten, az OpenGL kontextus letrehozasa utan hivodik meg (ld. main() fv.)
void onInitialization( ) {

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	//Nagyobb textura az utnak
	g_textureId[0] = MakeTexture(TexSize_Road);
	//Kisebb minden masnak
	g_textureId[1] = MakeTexture(TexSize);

	float SkyAmbient[] = {0.8, 0.8, 0.8, 1.0};

	float SunSpecular[] = {0.8, 0.8, 0.8, 1.0};
	float SunDiffuse[] = {0.8, 1.0, 1.0, 1.0};
	float Emission[] = {0.8, 0.8, 0.8, 1.0};
	
	//Nap
	glLightfv(GL_LIGHT0, GL_DIFFUSE, SunDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SunSpecular);
	glLightfv(GL_LIGHT0, GL_SHININESS, Shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, SunPosition);
	glLightfv(GL_LIGHT0, GL_EMISSION, Emission);
	glEnable(GL_LIGHT0);

	//'Egbolt ambiens fenye'
	glLightfv(GL_LIGHT1, GL_AMBIENT, SkyAmbient);
	glEnable(GL_LIGHT1);
	
	glViewport(0, 0, w_width, w_height);						//kepernyo transzf

		shadow[0][0] = 1.0f; shadow[0][1] = 0.0f; shadow[0][2] = 0.0f; shadow[0][3] = 0.0f;
		shadow[1][0] = -(SunPosition[0])/(SunPosition[1]); shadow[1][1] = 0.0f; shadow[1][2] = -(SunPosition[2])/(SunPosition[1]); shadow[1][3] = 0.0f;
		shadow[2][0] = 0.0f; shadow[2][1] = 0.0f; shadow[2][2] = 1.0f; shadow[2][3] = 0.0f;
		shadow[3][0] = 0.0f; shadow[3][1] = 0.001f; /*EPS*/shadow[3][2] = 0.0f; shadow[3][3] = 1.0f;
}
//Az uthenger

	RoadRoller marci_autoja = RoadRoller();
	Chicken istvan = Chicken();


// Rajzolas, ha az alkalmazas ablak ervenytelenne valik, akkor ez a fuggveny hivodik meg
void onDisplay( ) {
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);		// torlesi szin beallitasa
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // kepernyo torles

	
	//Arnyekok
	glPushMatrix();
	glMultMatrixf(&shadow[0][0]);
	glDisable(GL_LIGHTING);
	glColor3f(0.0,0.0,0.0);
		DrawAsphaltAndField();
		marci_autoja.Dock();
		istvan.ShowUp();
	glEnable(GL_LIGHTING);
	glPopMatrix();

  SetCameraTransform();
	DrawAsphaltAndField();
	marci_autoja.Dock();
	istvan.ShowUp();
	// ...

	glutSwapBuffers();     				// Buffercsere: rajzolas vege

}

// Billentyuzet esemenyeket lekezelo fuggveny
void onKeyboard(unsigned char key, int x, int y) {
	if (key == 'd') {
		cam_angle = cam_angle + 6.0f;
		glutPostRedisplay( ); 		// d beture rajzold ujra a kepet
	}

	if (key == 'k') {
		temp1+= 6.0f;
		glutPostRedisplay( ); 		// d beture rajzold ujra a kepet
	}

	if (key == 'l') {
		temp2-= 6.0f;
		glutPostRedisplay( ); 		// d beture rajzold ujra a kepet
	}
}

// Eger esemenyeket lekezelo fuggveny
void onMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT && state == GLUT_DOWN);  // A GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON illetve GLUT_DOWN / GLUT_UP
}

void AnimateSun(float time) {
	
	time = (int)time % 10000;
	float angle = time*0.00018;
	
	//A nap az YZ sikon megtesz egy felkort
	SunPosition[0] = 10*sinf(angle);
	SunPosition[1] = 10*cosf(angle);
	SunPosition[2] = 0.0f;
	SunPosition[3] = 0.0f; //NAP: 4. koord 0.0 -> pozicioja vegtelen tavol, ettol iranyfenyforras
	glLightfv(GL_LIGHT0, GL_POSITION,SunPosition);



}


// `Idle' esemenykezelo, jelzi, hogy az ido telik, az Idle esemenyek frekvenciajara csak a 0 a garantalt minimalis ertek
void onIdle( ) {
	long time = glutGet(GLUT_ELAPSED_TIME);		// program inditasa ota eltelt ido
	long old_time = 0;
	float dt = 0.01 * (time - old_time);
	istvan.Animate(time);
	AnimateSun(time);
	old_time = time;
	glutPostRedisplay();

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
