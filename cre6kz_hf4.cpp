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
// Nev    : Kun Attila
// Neptun : CRE6KZ
//--------------------------------------------------------

int w_height = 600;
int w_width = 600;
int time;	//GLUT_ELAPSED_TIME
float PI = 3.141592654;
float RAD = 180/PI;
float PI_of_180 = 0.017453292;

const float PyramidSurface[] = {0.91, 0.72, 0.0, 1.0};
const float PyramidBackSurface[] = {0.847, 0.71, 0.55, 0.7};
const float TerrainSurface[] = {0.0, 0.25, 0.0, 1.0};
const float Zero[] = {0.0, 0.0, 0.0, 1.0};
const float BulletSurface[] = {0.2, 0.2, 0.2, 1.0};
const float SkyAmbient[] = { 0.05f, 0.58f, 0.74f, 1.0f };
const float LightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
const float LightSpecular[] = {1.0, 1.0, 1.0, 1.0};
const float LightPosition[] = {100*cos(20.0), 100*sin(20.0), 100.0, 0.0};			//4. koord 0 -> iranyfenyforras
const float Shininess[] = { 30.0 };							//lightpos 1.param-e pozitiv, keletrol sut a nap..

static const struct {
	unsigned int 	 width;
	unsigned int 	 height;
	unsigned int 	 bytes_per_pixel; /* 3:RGB, 4:RGBA */ 
	unsigned char	 pixel_data[32 * 32 * 3 + 1];
} terep = {
	32, 32, 3,
	"nnL~\204V|\211Ty\212Sv\211Qw\217Cn\2055p\2032t\2025~\205A{|C\206\201W~uT"
	"e`C;6\31\35\31\0\33\27\0\33\31\4!\37\22#\40\33\26\25\23\32\20\31\32\20\31"
	"\30\15\25\30\16\17\36\24\12B8\35sl@\207\200L\210yR~rLtnJZY;}\204Z\177\220"
	"Zw\217Sv\220Qr\224>m\2167r\2169n\2034q~9{\177L\204\201^b[AD=-!\33\13\23\15"
	"\0\30\25\4\30\31\13\25\26\16\16\20\15\7\10\12\26\20\32\27\21\33\24\14\27"
	"\26\15\22\31\20\11""4,\27f^9\201yK\206vT\204wUztRGF*qzO{\220Wv\223Qs\225"
	"Kl\227=s\233B{\235Fm\2109m}>y\200Tvt[>8('\35\34\34\24\21\37\32\24\37\37\27"
	"\34\35\27\30\35\31\17\24\27\6\16\21\14\13\20\14\13\21\14\6\20\24\15\24\30"
	"\16\15\34\23\4:0\25TJ'xgI\216\201a\207\201a65\31Va6m\205Iw\231Ot\233Jb\223"
	"7l\231>s\233Eo\216Bu\211NoyTZ[I&!\33\35\23\33\32\21\26\40\34\35\32\32\30"
	"\23\25\22\22\30\30\12\24\26\11\22\31\25\31\30\30\31\33\20\17\25\27\22\31"
	"\35\24\27\24\11\3\31\16\0%\31\1VE)\210{[\215\207e)(\12?K\35_y:y\236Pv\240"
	"Jl\237Bl\235Bo\231Cw\227N}\222ZZdB24'\14\10\7\35\22\40\23\13\26\32\25\33"
	"\27\27\31\21\25\26\17\27\31\10\23\27\13\26\34\22\31\22\31\35\34\15\14\21"
	"\21\14\23!\30\35\40\25\23\34\20\4\36\21\0H7\33\200rU\206\200\\4+\12HJ\33"
	"bt8s\224Ou\237Wr\243Tk\237Mi\236Ll\240Uo\230^\40;\32\3\17\5\22\23\30\24\23"
	"\33\23\23\25\26\27\17\24\26\10\24\24\10\26\25\20\22\20\25\16\12\30\23\21"
	"\26\23\21\24\21\21\17\25\26\20\24\22\6\26\21\0#\30\2!\22\0""1&\10cX8\210"
	"\200YSJ)gi:n\200Dq\220Lo\227Nk\240Pe\234Ie\236Mi\237Sc\220U\26""4\16\2\20"
	"\1\30\36\36\40\36!\23\22\16\23\23\7\35\34\12\34\32\13\23\20\7\21\13\15\23"
	"\14\24\26\17\26\27\22\30\22\20\23\16\16\14\12\12\2\27\23\7""1*\27""7/\32"
	"-\"\4?4\24e]6qhG\205\207Xy\210Mo\214Ik\223Jg\240Oa\234J]\233Ha\236Pc\225"
	"V\40E\31\1\30\0\4\20\4\33\30\17$\"\25""76\"IG0B=)#\33\16\22\11\4\25\13\14"
	"\27\12\23\32\16\30\21\14\23\14\12\17\17\17\17))!WUHnkZL>#5*\12UM({rS\214"
	"\216_y\207Lo\215Gq\225K`\236K^\236JW\233F]\235Ok\244`Fq<&B\34\20\"\10""5"
	"5\35QQ7dcEyuXysYJB/\40\24\10\32\13\4\30\7\17\26\11\22\15\5\20\16\13\26\21"
	"\21\31#%$KLDdfYI:#)\33\0B7\27wnQ\207\206Xt\202Go\212Et\226L[\233G]\236JV"
	"\233HY\234Mk\247_e\222W^~MSj@ptOy}XqsN\207\204c\225\216q]R<%\30\7\37\17\0"
	"\30\12\12\23\10\16\16\6\23\25\23!\26\26\"\20\21\26\37!\36/1&6&\26%\26\3>"
	"0\26piM\203\202Vt\177Cn\210As\223Ha\241M_\240NW\232JZ\235Nh\242Xi\227Vr\224"
	"Xt\215T}\211Y|\205VuzQ\207\211dzuW<5\33\40\24\0%\26\3!\30\17\30\23\20\16"
	"\13\24\26\25#\27\26&\11\11\21\15\14\12\30\25\16*\27\21(\26\14""6$\26jcG\203"
	"\202Vw\202Fo\206@r\221Ee\243Pc\242Q[\234L]\233Nd\234Sh\226Nr\222Oo\210Go"
	"\200Iq\177L|\210Zx|WA@!*$\12F;%?3\35#$\22\37!\26\21\22\26\16\20\35\20\17"
	"\37\11\6\21\14\6\6\22\13\3/\33\35""1\35\34""5\"\34c\\@\203\202Vy\204Hp\207"
	"At\223G_\232He\242Ra\240Q]\233Nb\230Mo\232R~\235Wy\220J|\221Vt\207Pz\207"
	"YX`9\30\31\0B>%\212\202kbWA\30\36\4\35$\24\25\31\32\22\24!\26\25%\26\20\34"
	"\30\17\20\31\16\10'\22\31/\32\37""5\40\37\\TA\201\201[v\205Ln\220Fn\231G"
	"[\233E[\233E^\236Hd\237On\235Wq\222[izPbhFWgM]kRV_J%*\26\27\30\6;8'tm]PG"
	"8\35!\20FM=\40(\35\4\12\6\13\17\20\13\11\14\26\20\22\27\14\20(\20\35""3\31"
	"$0\22\34\\SB\200\200\\w\206Op\221Jm\230H_\237If\246Pd\244Pj\244Xi\227WJj"
	";/>\35+/\30\27$\22\34)\27&/\36\30\34\15\35\36\20\37\35\20""93'3-!`dSptf6"
	";4\22\26\25\27\30\32\23\16\22\30\15\21\24\5\12)\22\34""7\35&8\32\"\\SD\177"
	"~_w\205Rp\220Mj\224HZ\232De\245Q`\237Pg\240[Y\205P#A\35\10\25\3\17\20\10"
	"\4\20\6\2\14\3\12\21\11\12\20\6\35\40\27\14\15\5\27\27\17""74-moaik`/2+\21"
	"\21\21\25\23\26\24\13\20\30\11\16\27\4\10&\17\25""1\30\34""5\30\34\\SD~}"
	"^w\205Tp\220Og\221G_\237Hd\244N]\233N^\226U<g9\6#\7\4\17\7\22\21\26\27\40"
	"\35\27\40\35\25\33\27\14\22\16\22\31\22\0\3\0\11\16\7&+$)+\35&(\35\15\16"
	"\10\11\10\6\24\16\20\25\11\13\34\11\13!\10\13%\20\15,\24\22.\22\21^UD}}["
	"u\203Pn\216Md\216D`\241G\\\234E]\234MZ\222Q%P\"\0\26\0\15\30\22\30\27\35"
	"\4\12\12\16\24\22\16\27\24\14\26\16\10\22\11\0\10\0\21\35\17\30$\26\23\27"
	"\6\15\21\2\12\15\2\24\25\17\32\25\21\30\12\7\31\6\0\35\4\0*\26\15""1\32\22"
	"""4\30\24aYD\177\177[s\201Lm\215Jd\216B\\\235?W\230>`\240L`\231R+W\"\1\36"
	"\0\14\30\14\16\16\16\15\22\16\13\22\13\5\17\6\16\32\16\16\34\13\21\"\17""5"
	"I0:Q7\",\24\11\22\0\6\17\0\21\25\7\25\23\6\34\22\6(\26\10""1\33\15-\32\13"
	"""5\37\22:\37\26f_C\202\203Yt\203Jn\217Hg\222C_\241@]\236@e\245Nj\244WHv"
	"8\30""7\15\6\24\0\7\11\0\30\36\24\16\24\10\12\25\5&5\40>R7IaAc~[v\222lO^"
	"?(7\32!/\25%/\27\"%\20""1+\25C4\35N<$2\40\14""4\37\16""6\34\17jdD\205\206"
	"Zt\203Hn\220Fi\224BZ\234:[\235<`\241Em\250Vg\225T6V%\22!\0\33\36\11\20\24"
	"\6\15\24\4\35)\23O_Dy\216mu\217hg\206\\s\224g\201\225p\\pMaqTerV\\bFgcHs"
	"hJ~mO<*\24""5\40\15""0\26\7\177x[\210|T\200}Hq\204Bm\222Ej\236<b\242AR\234"
	"=R\226Cg\231Ti\212UJe8+G\36\37""1\27#2\25MX6p{Sy\212]q\217[`\213U_\222Ym"
	"\232cp\225ar\212Z~\207\\\204\202[\200{U\202zU|wQE9\21""8)\10""3\37\7\201"
	"z]\214\200Z\203\200Ms\203Bg\214?g\235?\\\236=R\237AW\237Ig\237Vt\234^r\225"
	"]g\214Xe~WbwPm|Qp~Ml\200Kk\212Qg\223Vl\240bd\222Tj\220Ur\213Tx\204RprCqn"
	"A\200|O~zMf\\8G:\32""8$\14\205{`\214~Y\207\201Ou\205Fg\211?c\233BV\233@U"
	"\246IY\250O[\232Ic\225Lm\234Vm\237Zp\223]v\223[z\217Vp\202Fk\201Aj\212Ic"
	"\222Nd\233Wx\246fl\224Vj\207M_r;LT!]_.~|L~zK|xUbY:J8\"\210|d\211yW\204|M"
	"z\210Ki\212Cb\231H[\237JX\253Q[\253RX\236HZ\225C_\230Ga\234Jd\221Lp\225O"
	"t\215Ip\204=r\210@o\216Hd\222Ib\232Qg\227]:e-.Q\33\37""7\5\"/\1[a5\205\203"
	"Z\203\200WzzX\177z\\eV?\214}f\211vV\201vI}\210Nk\212Dh\227Oc\242SW\245QS"
	"\241K[\241Kb\235Ia\235G`\240If\235Jn\231In\212=t\204;x\210Al\207@_\211AZ"
	"\217G6d3\0,\0\1'\0\0\25\0\17!\0_gB}}[\177zZtvO\210\205bymS\213zf\215x[\200"
	"sI{\204Kl\211Fk\220Mf\232RW\234LS\233Ia\240Og\240Qb\233J^\234Ib\234Gg\224"
	"Aj\2058y\205=|\205Bl\177?_\202BX\206F*Z*\24B\23""2\\.&J\36*C\33`nJquT\177"
	"|]v|N|}S~xV}lZ\217w]\201sLz\201Kq\213Jn\210Kg\220N`\231Rc\241Vj\242Yl\236"
	"Ug\233Qd\234Qd\240Ji\226Eq\207>\200\205C\177\177Cs~Fq\214Ul\224_Ew<I{@m\235"
	"c`\213SVwBn\202Qu|P\210\206]\177\206PsuD~{Rp]L\214tZ\202sLx\177Iw\221P|\216"
	"Tl\217Oh\233Vl\244]f\227U_\214K`\216Ma\224Qd\237Kn\231Jy\215F\207\207K\177"
	"zCryFv\214]m\221a`\224La\226No\243[h\227Qi\216Kx\216Pu~E||F\201\207Kqt=\202"
	"\177TM<(oaD{wQ\201\204Y{\202Vm\210So\211Yu\222bYxL:^0-S\40""2Z%W\203Hk\246"
	"Tm\227Kp\200?\204\202I|w@t}Dk\213Lc\225Pi\243Oc\241LU\231Bb\244Mk\241Sh\210"
	"Et}H\200yK\215\215Q}|D\177}L5$\24I=#b^;uwR{\202Yl\201Vq\206]dzT0J%\15)\3"
	"\0\36\0\11-\0=a1l\242V|\241[s\203Dyx@zw@y\204Hk\213Hd\223Kc\243Me\251RZ\243"
	"Jb\246Qn\244Vl\214Is~F~zJ\177\177C~}E\177}J&\24\12-\40\15C=#Z[<otT\205\222"
	"vp}cHV?\30'\22\10\32\4\10\34\3\11\40\3$=\35Nz;w\226[{\210R\201\201K\205\206"
	"M\201\221Rn\217He\226GS\234C\\\246MV\240IY\236Kf\234Pi\211Fp{Awv@~}D\205"
	"\204L\200\177I",
};

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

	Vector operator*(float f) const {
		return Vector(x * f, y * f, z * f);
	}

	Vector operator/(float f) const {
		return Vector(x / f, y / f, z / f);
	}

	Vector operator-(void) const { 
		return Vector(-x, -y, -z);
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

	// other methods
	float operator*(const Vector& v) const {		// DotProduct
		return x * v.x + y * v.y + z * v.z; 
	}

	Vector operator%(const Vector& v) const {		// CrossProduct
		return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}    
	/*Vector operator=(const Vector& v) const {		// Equation
	return Vector(v.x,v.y,v.z);
	} */

	float Norm(void) const {
		return sqrt(x*x + y*y + z*z);
	}

	void Normalize() {
		float norm = Norm();
		x /= norm;
		y /= norm;
		z /= norm;
	}
	Vector UnitVector( ) {				  // egy vektorral párhuzamos egységvektor
		Vector r = * this;
		r.Normalize();
		return r;
	}
};

GLuint MakeTexture() {
	GLuint TexID;
	glGenTextures(1, &TexID);
	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, terep.pixel_data);
	return TexID;
}

class Bezier_3d {

	int nVectors;
	Vector ctrlVectors[5];
public:
	Bezier_3d(int n) {
		nVectors = n;
		Vector* ctrlVectors = new Vector[nVectors];
		SetControls();
	}

	Vector GetPoint ( float p ) {

		Vector rr(0, 0, 0);
		int j = 1;
		for(int i = 0; i< nVectors; i++) {
			float Bi = 1.0;
			for(j = 1;j <= i; j++) Bi *= p * (nVectors-j)/j;
			for(;j < nVectors; j++) Bi *= (1-p);
			rr.y += ctrlVectors[i].y * Bi;
			rr.x += ctrlVectors[i].x * Bi;
			rr.z += ctrlVectors[i].z * Bi;
		}
		return rr;
	}

	void DrawCurve() {
		glColor4d( 0.0, 0.0, 0.0, 1.0) ;
		glBegin( GL_LINE_STRIP );
		for ( int i = 0; i < 100 ; i++ ) {
			float t = (float)i / 100;
			Vector p = GetPoint(t);
			glVertex3f( p.x, p.y, p.z );
		}
		glEnd();

		glColor3d( 1.0, 1.0, 0.6 ) ;
		glBegin( GL_POINTS ) ;
		for ( int k = 0; k < nVectors; k++) glVertex3f( ctrlVectors[k].x, ctrlVectors[k].y, ctrlVectors[k].z );
		glEnd();
	}

	void SetControls() {
		ctrlVectors[0] = Vector(50,0,-30);
		ctrlVectors[1] = Vector(150,0,-290);
		ctrlVectors[2] = Vector(-75,0,-380);
		ctrlVectors[3] = Vector(-185,0,-280);
		ctrlVectors[4] = Vector(-185,0,-350);
	}

};

Bezier_3d Track(5);

class AABB {
	float xmin, xmax;
	float ymin, ymax;
	float zmin, zmax;

public:
	AABB() {
		xmin = 0;
		ymin = 0;
		zmin = 0;

		xmax = 0;
		ymax = 0;
		zmax = 0;
	}

	AABB(float x1, float x2, float y1, float y2, float z1, float z2 ) {
		xmin = x1;
		ymin = y1;
		zmin = z1;

		xmax = x2;
		ymax = y2;
		zmax = z2;
	}

	bool Collide(const AABB other) {

		if(xmin<=other.xmax	&&
			xmax>=other.xmin &&
			ymin<=other.ymax &&
			ymax>=other.ymin &&
			zmin<=other.zmax &&
			zmax>=other.zmin) return true;
		else
			return false;

	}
};

class Pyramid {
	Vector position;		//pozicio a vilag-koordinata rendszerben

public:
	AABB BoundingBox;

	Pyramid() {
		position = Vector(0.0, 0.0, 0.0);
	}
	Pyramid(Vector pos) {
		position = pos;
		BoundingBox = AABB(pos.x-3, pos.x+3, pos.y-3, pos.y+3, pos.z-3, pos.z+3);
	}

	void DrawIt() {
		glPushMatrix();
		glTranslatef(position.x+80.0, position.y, position.z+90.0);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.8f, 0.2f);
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
		glPopMatrix();
	}
};

Pyramid PyramidContainer[56];

class Bullet {
	Vector position, velocity;
	Vector pos0;
	float v0, ShotAngle, Shot_Dir, time0;

public:
	Bullet(Vector pos) {
		pos0 = pos;
		position = pos;
	}

	void Fire(float startvel, float angle, float dir, Vector Startpos, float startTime) {
		pos0 = Startpos;
		position = Startpos;
		v0 = startvel;
		ShotAngle = angle;
		Shot_Dir = dir;
		time0 = startTime;
	}

	Vector SetnTrace( float dt) {
		position.x = pos0.x+(v0*cos(ShotAngle*PI_of_180)*(dt-time0))*sin(Shot_Dir*PI_of_180);
		position.y = pos0.y-(v0*sin(ShotAngle*PI_of_180)*(dt-time0))+(9.81/2)*(dt-time0)*(dt-time0)/1000000.0;
		position.z = pos0.z+(v0*cos(ShotAngle*PI_of_180)*(dt-time0))*cos(Shot_Dir*PI_of_180);

		return position;
	}

	Vector Trace( float dt) {
		return Vector((pos0.x+(v0*cos(ShotAngle*PI_of_180)*(dt-time0))*sin(Shot_Dir*PI_of_180)),
		(pos0.y-(v0*sin(ShotAngle*PI_of_180)*(dt-time0))+(9.81/2)*(dt-time0)*(dt-time0)/1000000.0),
		(pos0.z+(v0*cos(ShotAngle*PI_of_180)*(dt-time0))*cos(Shot_Dir*PI_of_180)));
	}

	void DrawIt( float dt ) {
		SetnTrace( dt );

		float radius = 1.0;
		float height = 2.0;
		float div = 32.0;

		velocity =  position - Trace( dt+1 );
		Vector modell_head( 0, 0, 1 );                     // orientáció számítás
		Vector world_head = velocity.UnitVector(); 			// orr iránya
		Vector rotate_axis = world_head % modell_head;     // forgatási tengely
		float cos_rotate_angle = world_head * modell_head; // forgatási szög
		float rotate_angle = acos( cos_rotate_angle )*RAD;

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BulletSurface);
		glMaterialfv(GL_FRONT, GL_SPECULAR, BulletSurface);
		glMaterialfv(GL_FRONT, GL_SHININESS, Shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, BulletSurface);
		
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		
		glRotatef( -rotate_angle+180.0, rotate_axis.x, rotate_axis.y, rotate_axis.z );
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

		glPopMatrix();
	}
};

Bullet FirstShot(Vector(0.0, 0.0, 0.0));

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

	glPushMatrix();
	glScalef(4.0, 4.0, 4.0);
	glTranslatef(-1.0,0.0, 0.0);
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

	glPopMatrix();

	DrawSideFoot();
	glTranslatef(-10.0, 0.0, 0.0);
	DrawSideFoot();
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

	glRotatef(-90.0, 1.0, 0.0, 0.0);
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

void DrawVehicle(Vector pos, float rot_angle, Vector rot_axis, float shot_angle, float turret_lookat) {

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Zero);
	glMaterialfv(GL_FRONT, GL_SPECULAR, TerrainSurface);
	glMaterialfv(GL_FRONT, GL_EMISSION, TerrainSurface);

	glTranslatef(pos.x, pos.y, pos.z);	//Pozicio
	glPushMatrix();						//Tank test, es talpak
	glRotatef( 180.0, 1.0, 0.0, 1.0 );	
	glRotatef( 90.0, 0.0, 1.0, 0.0 );

	glRotatef( -rot_angle, rot_axis.x, rot_axis.y, rot_axis.z );		//Forgatas menetiranyba
	DrawTankBody();

	//Lovegtorony + tankcso
	glTranslatef(7.0, 3.0, 0.0);
	glScalef(0.68, 0.68, 0.68);
	glRotatef(turret_lookat, 0.0, 1.0, 0.0);	//turret_lookat

	DrawLT(5.0, 2.0, 80.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 1.0, 0.0);
	DrawLTHat();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(-shot_angle, 1.0, 0.0, 0.0);	//shot_angle
	DrawTheGun(1.0, 26.0, 32.0);

	glPopMatrix();
}

void DrawTerrain(){

	float j = 0.0;
	float startx = 500.0;
	float startz = 200.0;

	glBegin(GL_QUADS);
	for(;j<1200;j+=100) {
		float i = 0.0;
		for(;i<1000;i+=100) {
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(startx-j, 1.0, startz-i);
			glVertex3f(startx-j, 1.0, startz-i-100.0);
			glVertex3f(startx-j-100.0, 1.0, startz-i-100.0);
			glVertex3f(startx-j-100.0, 1.0, startz-i);
		}
	}
	glEnd();
}

class Avatar {
	Vector Head, Eye, Velocity;
	float H_Angle, speed;
	AABB BoundingBox;
	Vector LookDir;
	
public:
	Avatar(Vector E, Vector L) {
		Eye = E;
		speed = 0.0;
		Velocity = Vector(0.0, 0.0, 0.0);
		Head = Vector(0.0,0.0,0.0);
		Head.x = Eye.x + LookDir.x;
		Head.z = Eye.z + LookDir.z;
		Head.y = 0.0;
		H_Angle = 0.0;
		LookDir = L;
	}
	Vector  GetHead( ) { return Head; }
	Vector GetEye( ) { return Eye; }

	void SetCameraTransform() {
		


		Head.x = Eye.x + LookDir.x;
		Head.z = Eye.z + LookDir.z;
		Velocity = LookDir*speed;

		AnimateMe();

		BoundingBox = AABB(Eye.x-3, Eye.x+3, Eye.y-3, Eye.y+3, Eye.z-3, Eye.z+3);

		glViewport(0, 0, w_width, w_height);		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		float aspect = (w_height == 0) ? 1.0 : w_width / w_height;
		gluPerspective(90, aspect, 1, 800);						

		glMatrixMode(GL_MODELVIEW);          	

		glLoadIdentity();
		gluLookAt( Eye.x, -7.0, Eye.z,
			Head.x, -6.0, Head.z, 					//Mindig egy szintben latunk...
			0.0, -1.0, 0.0);
	}

	void Move(bool left, bool right) {
		if(left&&right){
			//Eye.x += LookDir.x;
			//Eye.z += LookDir.z;
			speed+=0.04;
		}
		else if(left&&!right){
			H_Angle -= 4.0;
			float H_Rad = H_Angle*(PI_of_180);
			LookDir.x = -sin(H_Rad)*4;
			LookDir.z = -cos(H_Rad)*4;

		}
		else if(!left&&right) {		
			H_Angle += 4.0;
			float H_Rad = H_Angle*(PI_of_180);	
			LookDir.x = -sin(H_Rad)*4;		
			LookDir.z = -cos(H_Rad)*4;		
		}
	}

	void AnimateMe() {
		if(speed<=0.0) speed = 0.0;
		else
			speed-=0.01;
		
		Eye+=Velocity;
	}

	bool CD(void) {							//Utkozes detektalas
		for(int i = 0; i <= 55; i++) {
			if(PyramidContainer[i].BoundingBox.Collide(BoundingBox))return true;
		}
		return false;
	}

};

Avatar Myself( Vector(100.0, 0.0, -17.0), Vector(0.28, 0.0, -4.0));

class EnemyTank {
	Vector position, velocity;
	float shoot_angle, turret_turn;

public:
	EnemyTank(Vector pos, Vector vel) {
		position = pos;
		velocity = vel;
		shoot_angle = 0.0;
		turret_turn = 0.0;
	}

	float SetShooterAngle(Vector target_position) {		//Lovegtorony vertikalis allasa

		Vector len = target_position - position;
		float distance = sqrt(len.x*len.x+len.z*len.z);
		shoot_angle = (asin((distance*9.81)/1600)/2)*(RAD);
		return shoot_angle;
	}

	Vector GetPos() {
		return position;
	}

	float SetTurretDir(Vector target_position) {			//Lovegtorony horizontalis allasa

	Vector turret_dir = position - target_position;
	float turret = sqrt(turret_dir.x*turret_dir.x+turret_dir.z*turret_dir.z);
	turret = turret_dir.z/turret;
	turret = acos(turret)*(RAD);
	Vector velocity = Track.GetPoint(time/50000.0+0.01)-Track.GetPoint(time/50000.0);
	float target = acos(velocity.z/sqrt(velocity.x*velocity.x+velocity.z*velocity.z))*(RAD);

	if(velocity.x < 0)
		target = -target;

	if(target_position.x < position.x) turret = -turret;
		turret += target;
		turret_turn = turret;
		return turret;
	}

	void DrawIt() {
		velocity = position - Track.GetPoint(time/50000.0+0.01);				//A konyvbol valo orientacios szamitas..
		Vector modell_head( 0, 0, 1 );                     
		Vector world_head = velocity.UnitVector(); 			
		Vector rotate_axis = world_head % modell_head;    
		float cos_rotate_angle = world_head * modell_head;
		float rotate_angle = acos( cos_rotate_angle ) * RAD;

		DrawVehicle(Vector( position.x, position.y, position.z ), -rotate_angle, Vector( rotate_axis.x, -1.0, rotate_axis.z ), shoot_angle, turret_turn);
	}

	void SetPosition(float dt) {
		Vector u = Track.GetPoint(dt/50000.0);	//Az egesz gorbe tul hosszu, es inkabb lassabban menjen hogy latszodjon
		position = Vector(u.x, u.y, u.z);		//Gorbe'n valtoztatott helyzet
	}
};

EnemyTank Ellenseg(Vector(50,0,-30), Vector(0.0, 0.0, 0.0));

void Pyramids() {

	Vector PyramidVectorContainer[56];			//Piramisok helyzetet tarolo vektorok (poziciok)
	int p = 0;
	Vector v1 = Vector(-232.0, 0.0, -14.0);

	//7x8 db piramis

	for(int i = 0; i < 7; i++) {
		v1.z -= 50.0;
		for(int j = 0; j < 8; j++) {
			v1.x += 50.0;
			if(j == 7) v1.x -= j*60; 			//carriage return:)
			if(i == 2 && j == 3) ;
			else if(i == 1 && j == 3) ;			//kihagyunk ket piramist
			else PyramidVectorContainer[p++] = v1;
		}
	}
	glPushMatrix();

	glScalef(2.0, 2.0, 2.0);

	for(int h = 0; h < 56; h++) {
		PyramidContainer[h] = Pyramid(PyramidVectorContainer[h]);
		PyramidContainer[h].DrawIt();
	}

	glPopMatrix();
}

bool isThereABullet = false;

void onDisplay() {

	glClearColor(0.15f, 0.58f, 0.74f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint g_textureId2 = MakeTexture();
	//if(Myself.CD()==false)
		Myself.SetCameraTransform();		//Ha nem utkoztunk neki semminek, mehetunk
	
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, TerrainSurface);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Zero);
	glMaterialfv(GL_FRONT, GL_SHININESS, Zero);
	glMaterialfv(GL_FRONT, GL_EMISSION, TerrainSurface);
	
	DrawTerrain();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PyramidSurface);
	glMaterialfv(GL_FRONT, GL_SPECULAR, PyramidSurface);
	glMaterialfv(GL_FRONT, GL_SHININESS, Shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, PyramidBackSurface);
	Pyramids();
	//Track.DrawCurve();			//Gorbe kirajzolasa, ha kell
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	float ShotAngle = Ellenseg.SetShooterAngle(Myself.GetEye());
	float ShotDir = Ellenseg.SetTurretDir(Myself.GetEye());
	Ellenseg.SetPosition(time);
	glPushMatrix();

	Ellenseg.DrawIt();

	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1,&g_textureId2);

	if(time > 1000) {				//1mp-nel lohetunk
		if(!isThereABullet) {					//Es csak egy loves lesz
		FirstShot.Fire(0.05, ShotAngle, -ShotDir, Ellenseg.GetPos(), time);
		isThereABullet = true;
		}
	}
	if(isThereABullet) FirstShot.DrawIt(time);

	glFinish();
	glutSwapBuffers();
}



void onInitialization( ) {

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FOG);
	glDisable(GL_COLOR_MATERIAL);

	float FogCol[3]={0.73f,0.73f,0.85f}; 
	glFogfv(GL_FOG_COLOR,FogCol);  

	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 28.f);
	glFogf(GL_FOG_END, 450.f);

	glFogf(GL_FOG_DENSITY, 1.f);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, SkyAmbient);			//Egbolt ambiens fenye, uolyan szinu mint a 'hatter'
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_SHININESS, Shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT0);
}

void onKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a' : 
		Myself.Move(true, false);		
		break;
	case 'd' : 
		Myself.Move(false, true);
		break;
	case 'w' :
		Myself.Move(true, true);
		break;
	}
}

void upKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a' : 
		//Myself.Move(true, false);		
		break;
	case 'd' : 
		//Myself.Move(false, true);
		break;
	case 'w' :
		//Myself.Move(true, true);
		break;
	}
}


void onMouse(int button, int state, int x, int y) {

}

void onIdle( ) {
	time = glutGet(GLUT_ELAPSED_TIME);
	glutPostRedisplay();
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

	glutIgnoreKeyRepeat(0);
	glutDisplayFunc(onDisplay);
	glutMouseFunc(onMouse);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboard);
	glutKeyboardUpFunc(upKeyboard);

	glutMainLoop();

	return 0;
}

