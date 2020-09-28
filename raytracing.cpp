 # //========================================================
#  // Hazi feladat keret.
#  // A //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  // sorokon beluli reszben celszeru garazdalkodni, mert
#  // a tobbit ugyis toroljuk.
#  // A Hazi feladat csak ebben a fajlban lehet
#  // Tilos:
# //========================================================
#  // Hazi feladat keret.
#  // A //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
// Nev: Kovács Krisztina     
// Neptun: G7PAHM
//--------------------------------------------------------

const int DMAX=11;
const int MAX_OBJECTS=20;
const int MAX_LIGHTS=2;
const int T_MAX=2000;
const int PI=3.14;
const GLint width=600;
const GLint height = 600;
GLint size = width * height;



class Color{

public:
	float r, g, b;
	
	Color(){}
	Color(float r0, float  g0, float b0){
		r=r0;
		g=g0;
		b=b0;
		}

	Color operator+(Color& c) {
 	return Color(r + c.r,g + c.g, b + c.b); 
   }

	Color operator*(Color& c) const {
		return Color(r * c.r, g * c.g, b * c.b);
	}

	Color operator*(float val) { 
	return Color(r*val, g*val, b*val); 
   }

	float Lum() const {
		return (r + g + b) / 3.0;
	}
};

class Vector{

	public:
	float x, y, z;
	
	Vector(){}
	Vector(float x0,float y0, float z0){
		x = x0; y = y0; z = z0; 
   }
   Vector operator*(float a) { 
	return Vector(x * a, y * a, z * a); 
   }
   Vector operator+(Vector& v) {
 	return Vector(x + v.x, y + v.y, z + v.z); 
   }
   Vector operator-(Vector& v) {
 	return Vector(x - v.x, y - v.y, z - v.z); 
   }
   float operator*(Vector& v) { 
	return (x * v.x + y * v.y + z * v.z); 
   }
   Vector operator%(Vector& v) { 
	return Vector(y*v.z-z*v.y, z*v.x - x*v.z, x*v.y-y*v.x);
   }

   Vector operator/(float a) { 
	return Vector(x / a, y /a, z / a);
	}
   
   float Length() { return sqrt(x * x + y * y + z * z); }

};

class Camera{
public:
	Vector	eyep;
	Vector	lookp;		
	Vector	updir;			

	float	viewdist;		
	float	fov, fovX, fovY;	
	long	hres, vres;			
		
	Vector	X, Y, Z;			// a szem koordinata rendszere: X=jobbfele, Y=lefele, Z=nezeti irany
	float	pixh, pixv;		// pixel hosszusaga es szelessege

	Camera(){
			eyep= Vector(0.0, 0.0, 0);
			lookp=Vector(0.0, 0.0, -10.0);
			updir=Vector(0., 1.0, 0.0);

			fov=22.5;
			hres=width;
			vres=height;
			fovX=fov;
			fovY=fov;

	// viewing direction
	Z = lookp - eyep;
	viewdist = Z.Length();

	if (viewdist < 0.001) { return; }
	Z = Z* 1.0 / viewdist;
 
	X = Z % updir;
	if (X.Length() < 0.001) { return; }
	X =X* 1.0 / X.Length();

	Y = Z % X;
	Y=Y/Y.Length();

	float tanFovH = tan(fovX * PI / 180.0);
	float tanFovV = tan(fovY * PI / 180.0);
	pixh = 2.0 * tanFovH / (float)(hres);
	pixv = 2.0 * tanFovV / (float)(vres);


	}	
};

class Material{

public:
	Color kd, ks, ka, kr, kt;
	float shininess;
	float n;
	
	Material(){}
	Material(Color kd0, Color ks0, Color kr0, Color kt0, float sh){
		kd=kd0;
		ks=ks0;
		kr=kr0;
		kt=kt0;
		shininess=sh;
		}

	Color BRDF(Vector V, Vector normal, Vector outDir){

		float cos_theta, cos_theta2;
		float cos_delta;
		Vector H=(V+outDir)/(V+outDir).Length();
		cos_delta=normal*H;
		cos_theta=V*normal;
		cos_theta2=outDir*normal;

		//az anyag belsejebol jövünk
		if (cos_theta<=0) return Color(0,0,0);

		Color brdf_s= ks*(pow(cos_delta,shininess)/cos_theta2);
		return kd+brdf_s;
		}

	};


class Ray{

	public:
	Vector sp; //kezdõpont
	Vector dir;

	Ray(){}
	Ray(Vector p, Vector irany){
		sp=p;
		dir=irany;
		}
	};

class Light{

public:
	Vector pos;
	Color emission;

	Light(){}
	Light(Vector pos0, Color em0){
		pos=pos0;
		emission=em0;
		}
	};

class Intersection{

public:
	Vector point;
	Vector normal;
	float t;
	int obj_index;

	Intersection(){}
	};

class Object{

public:
	int id;
	Material mat;
	int type; //Sphere (0) vagy Plane(1)

	Object(){}
	Object(int id0){id=id0;}
	virtual bool Intersect(Ray ray, Intersection* i){return false;};
	};

class Sphere: public Object{

public:
	float r; //sugár
	Vector kp; //középpont

	Sphere(){}
	Sphere(int id0, float r0, Vector kp0) {
		id=id0;
		r=r0;
		kp=kp0;
		type=0;
		}
	
	bool Intersect(Ray ray, Intersection* i){
			// |ray(t)-kp|^2-r^2=0  másodfokú egyenlet megoldása
			//(ray.dir ¡ray.dir) t^2 + 2 ((eye-center) ¡v) t +((eye-center) ¡(eye-center))- R^2 = 0

			double a=ray.dir*ray.dir;
			Vector v=ray.sp-kp;
			double b=v*ray.dir*2.0;
			Vector dist=ray.sp-kp;
			double c= dist*dist-r*r;

			//másodfokú megoldóképlet alkalmazása
			double disc= b*b-(4.0)*a*c;
			if (disc<=0) return false;  //nincs metszespont

			//metszespontok
			double sqrt_disc = sqrt(disc);
			double t1=(-b+sqrt_disc)/2.0/a;
			double t2=(-b-sqrt_disc)/2.0/a;
			if (t1 < 0.1) t1 = -0.1;
			if (t2 < 0.1) t2 = -0.1;
			if (t1 < 0 && t2 < 0) return false;

			float t;
			if (t1 < 0 && t2 >= 0) t = t2;
			else if (t2 < 0 && t1 >= 0) t = t1;
			else if (t1 < t2)  t = t1;  // biztosan t1 > 0 és t2 > 0
			else t = t2;

			i->t=t;
			v=ray.dir*t;
			i->point=ray.sp + v;
			i->normal=(i->point-kp)/r; 
			i->obj_index=id;
			return true;
	}
};

class Plane: public Object{
public:
	//sík egy adott pontja, és a pontban a normálvektor
	Vector point;
	Vector normal;

	Plane(){}
	Plane(int id0, Vector point0, Vector normal0) {
		id=id0;
		point=point0;
		normal=normal0;
		type=1;
	}

	bool Intersect(Ray ray, Intersection* i){
		// (ray(t)-point)*normal=0
		//normal*(Eye+t*Dir-point)=0
		//t=normal*(pont-eye)/(normal*dir)

		float nevezo=ray.dir*normal;
		if (nevezo==0) return false;
		Vector v=(point-ray.sp)/nevezo;
		float t = normal*v;
		if (t<0.1) return false;

		i->t=t;
		v=ray.dir*t;
		i->point=ray.sp +v;
		i->normal=normal;
		i->obj_index=id;
		return true;
	}
};


Camera cam;
Object** objects;
Light lights[MAX_LIGHTS];
int num_obj;
int num_lights;
Color La=Color(0.1,0.1,0.1);


Vector GetRayDir(int x, int y) {

	float	h = cam.pixh;	// pixel horizontális mérete
	float	v = cam.pixv;	// pixel vertikális mérete
	// az aktuális pixel középpontja
	float	pix_x = -h * cam.hres / 2.0 + x * h + h / 2.0;
	float	pix_y = -v * cam.vres / 2.0 + y * v + v / 2.0;

	Vector X_=cam.X*pix_x;
	Vector Y_=cam.Y*pix_y;
	Vector rayDir = cam.Z + X_ + Y_;
	rayDir=rayDir/rayDir.Length();
	return rayDir;	// a sugár iranya a szembol
}


//input: ray (sugár)  
//output: obj, az elmetszett objektum (ha van), x: a metszespont (ha van), 
//return: van e metszéspont

bool Intersect(Ray ray, Intersection* intersect){

	float t=T_MAX;
	for (int i=0; i<num_obj; i++){

		Intersection intsec;
		Object *obj=objects[i];
		bool hit=false;
		
		if(obj->type==0){
				Sphere* sph= (Sphere*)obj;
				hit=sph->Intersect(ray, &intsec);
			}
		if(obj->type==1){
				Plane* pl= (Plane*)obj;
				hit=pl->Intersect(ray, &intsec);
		}

		if (hit){
			if ((intsec.t>0)&&(intsec.t<t)){
				*intersect=intsec;
				t=intsec.t;
			}
		}
	}
	if ((intersect->t>0)&&(intersect->t<T_MAX))return true;
	return false;
}


Color trace(Ray ray,int depth){
		Color col(0,0,0);
		if (depth>DMAX) return La;
			Intersection intersect;	
			bool hit=Intersect(ray, &intersect); //vissza: metszespont es elmetszett objektum, ha van.
			if (hit){
				//eltalat objektum
				Object* obj=objects[intersect.obj_index];
				//sugar iranyvektora
				Vector inDir=ray.dir;
				//A felülettel való metszespont
				Vector x=intersect.point;
				//A felulet normalvektora az adott pontban
				Vector normal=intersect.normal;
				//A nezeti iranyba mutato egysegnyi vektor
				Vector V=inDir*(-1.0);
				//nezeti szög
				float cos_theta=normal*V;		
				//nincs sajat emisszió
				Color c=La*obj->mat.ka;
				col= col+c;				
				
				for(int i=0; i<num_lights; i++){
					//x-bõl  a fényforrás felé mutató sugár számítása
					Vector light_pos=lights[i].pos;
					Vector light_dir=(light_pos-x)/(light_pos-x).Length();
					Ray toLight=Ray(x,light_dir);
					Intersection intsec;
					bool hit2=Intersect(toLight, &intsec); 
					//ha nincs metszes, vagy a fenyforras a metszett objektum elott van
					if ((!hit2)||((intsec.point-x).Length()>(light_pos-x).Length())){

						float cos_light_norm=light_dir*intersect.normal;
						Color toAdd=(obj->mat.BRDF(V,intersect.normal,light_dir)*lights[i].emission)*cos_light_norm;
						col=col+ toAdd;
					}
				}
				//ha van visszaverodes
				if (obj->mat.kr.Lum()>0){  //pipa
					//tüköritány számítása V_r=inDir+2cos(nezeti szög)*N 
					Vector v=normal*(2*cos_theta);
					Vector Vr=inDir+v; 
					//tükörirányba küldött sugár
					Ray reflRay=Ray(x,Vr);

					Color traced=trace(reflRay,depth+1);
					Color toAdd=obj->mat.kr*traced;
					col=col+toAdd;
					}

				if (obj->mat.kt.Lum()>0){
					//törési irány számítása:
					if (fabs(cos_theta)>0){
							float n = obj->mat.n;
							Vector useNormal = normal;
							if (cos_theta < 0) {	
									// ha az anyag belsejebol jovunk
									n	= 1.0 / obj->mat.n;	 
									useNormal= normal*(-1.0);		// a toresmutato reciprokat kell hasznalni
									cos_theta= -cos_theta;
							}	
							float disc = 1 - (1 - cos_theta * cos_theta) / n / n;	 // Snellius-Descartes torveny
							if (disc>=0){	
								//törési irány
								Vector v=inDir/n;
								Vector Vt = useNormal * (cos_theta / n - sqrt(disc))+v; 

								Vt=Vt/Vt.Length();
								//törési irányba küldött sugár
								Ray refrRay =Ray(x,Vt);
								Color traced=trace(refrRay,depth+1);
								Color toAdd=obj->mat.kt*traced;
								col=col+toAdd; 	
							}
						}
				}	 //if (obj->mat.kt.Lum()>0) vége
				return col; 
			}
			else return La;
	}


void Init( ) {

	cam=Camera();

	Sphere* sph1=new Sphere(1,100.0, Vector(0.0,0.0,-600.0));
	sph1->mat.kd=Color(1.0,0.5,0.5);
	sph1->mat.ks=Color(0.0,0.0,0.0);
	sph1->mat.shininess=0;
	sph1->mat.kr=Color(0.7,0.7,0.7);
	sph1->mat.kt=Color(0.3,0.3,0.3);
	sph1->mat.ka=Color(0.1, 0.1, 0.1);
	sph1->mat.n=1.2;

	Sphere* sph2=new Sphere(0,50.0, Vector(100.0,100.0,-500.0));
	sph2->mat.kd=Color(1.0,0.3,0.3);
	sph2->mat.ks=Color(1.0,0.0,1.0);
	sph2->mat.shininess=50;
	sph2->mat.kr=Color(0,0,0);
	sph2->mat.kt=Color(0.1,0.1,0.1);
	sph2->mat.ka=Color(0.1, 0.1, 0.1);
	sph2->mat.n=1.2;

	Vector v=Vector(0.0,5.0, 1.0);
	Vector nv=v/(v.Length());
	Plane* pl1=new Plane(2,Vector(0.0,0.0,-1500.0),nv);
	pl1->mat.kd=Color(0.5,1.0,0.5);
	pl1->mat.ks=Color(0.0,0.0,0.0);
	pl1->mat.shininess=0;
	pl1->mat.kr=Color(0.0,0.0,0.0);
	pl1->mat.kt=Color(0.0,0.0,0.0);
	pl1->mat.ka=Color(0.1, 0.1, 0.1);
	pl1->mat.n=1.2;

	v=Vector(5.0,0.0, 1.0);
	nv=v/(v.Length());
	Plane* pl2=new Plane(3,Vector(0.0,0.0,-1500.0),nv);
	pl2->mat.kd=Color(0.5,0.5,1.0);
	pl2->mat.ks=Color(1.0,0.2,0.5);
	pl2->mat.shininess=50;
	pl2->mat.kr=Color(0.0,0.0,0.0);
	pl2->mat.kt=Color(0.0,0.0,0.0);
	pl2->mat.ka=Color(0.1, 0.1, 0.1);
	pl2->mat.n=1.2;

	v=Vector(0.0,0.0, 1.0);
	nv=v/(v.Length());
	Plane* pl3=new Plane(4,Vector(0.0,0.0,-1500.0),nv);
	pl3->mat.kd=Color(1.0,1.0,0.0);
	pl3->mat.ks=Color(1.0,0.0,1.0);
	pl3->mat.shininess=80;
	pl3->mat.kr=Color(1.0,1.0,1.0);
	pl3->mat.kt=Color(0.3,0.3,0.3);
	pl3->mat.ka=Color(0.1, 0.1, 0.1);
	pl3->mat.n=1.2;

	objects = new Object*[MAX_OBJECTS];
	objects[0]=sph2;
	objects[1]=sph1;
	objects[2]=pl1;
	objects[3]=pl2;
	objects[4]=pl3;
	num_obj=5;

	Vector v1=Vector(100.0,200.0,0.0);
	Color c1=Color(1,1,1);
	Light l1=Light(v1,c1);
	lights[0]=l1;
	num_lights=1;

	glEnable(GL_LIGHTING);

	float kd[] = {0.0, 1.0, 1.0};
	float ks[] = {1.0, 0.5, 1.0};

	float I_d[] = {0.0, 1.0, 1.0};
	float I_s[] = {1.0, 1.0, 1.0};
	float pos[] = {-100.0, -200.0, -10.0};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, I_d);
	glLightfv(GL_LIGHT0, GL_SPECULAR, I_s);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	}

void onDisplay( ) {
    glClearColor(1, 0, 0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    //
    // TODO: ide jon az erdemi rajzolo kod
    //

GLfloat* pixels = new GLfloat[size * 3];	

	for(int i=0; i<600;i++){ //pixelek x koordinatai
		for(int j=0; j<600; j++){ //pixelek y koordinatai

			Vector rayDir = GetRayDir(i, j);
			Ray ray=Ray(cam.eyep,rayDir);
			Color color=trace(ray,5); 

			int n=i*600+j;
			pixels[n*3] = color.r;
			pixels[n*3+1] = color.g;
			pixels[n*3+2] = color.b;

		}
	}

    glDrawPixels(600,600,GL_RGB,GL_FLOAT,pixels);
   
    // Buffercsere: rajzolas vege
    glutSwapBuffers();
}

void onMousePress(int button, int state, int x, int y) {
}

void onIdle( ) {
}

void onKeyboard(unsigned char key, int x, int y) {
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void main(int argc, char * argv[]) {
	glutInit(&argc, argv); 
	glutInitWindowSize(600, 600);
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
