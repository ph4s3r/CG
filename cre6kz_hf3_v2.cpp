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
//#include "chick.c"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Innentol modosithatod...
 
//--------------------------------------------------------
// Nev    : Kun Attila
// Neptun : cre6kz
//--------------------------------------------------------
 
// Inicializacio, a program futasanak kezdeten, az OpenGL kontextus 
// letrehozasa utan hivodik meg (ld. main() fv.)
 
 
 
int w_height = 600;
int w_width = 600;
 
int isPressed = 0;
 
GLuint g_textureId;
 
void drawfoot(void) {
 
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLES);
    glNormal3f(0.384422f, 0.066553f, 0.920755f);
    glVertex3f(0.207379f, -1.332402f, -0.754288f);
    glNormal3f(0.244061f, 0.139624f, 0.959656f);
    glVertex3f(0.182561f, -1.141235f, -0.757744f);
    glNormal3f(0.782164f, 0.158482f, 0.602580f);
    glVertex3f(0.267471f, -1.292418f, -0.800704f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.065950f, 0.071375f, 0.995267f);
    glVertex3f(0.120825f, -1.294533f, -0.740031f);
    glNormal3f(0.244061f, 0.139624f, 0.959656f);
    glVertex3f(0.182561f, -1.141235f, -0.757744f);
    glNormal3f(0.384422f, 0.066553f, 0.920755f);
    glVertex3f(0.207379f, -1.332402f, -0.754288f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.116452f, -0.944539f, 0.307057f);
    glVertex3f(0.102043f, -1.345914f, -0.863217f);
    glNormal3f(-0.119386f, -0.638511f, 0.760297f);
    glVertex3f(0.120825f, -1.294533f, -0.740031f);
    glNormal3f(0.042204f, -0.994093f, 0.099993f);
    glVertex3f(0.207379f, -1.332402f, -0.754288f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.907867f, 0.189967f, 0.373751f);
    glVertex3f(0.263320f, -1.149589f, -0.863217f);
    glNormal3f(0.806789f, 0.256421f, 0.532296f);
    glVertex3f(0.297165f, -1.256077f, -0.863217f);
    glNormal3f(0.782164f, 0.158482f, 0.602580f);
    glVertex3f(0.267471f, -1.292418f, -0.800704f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.244061f, 0.139624f, 0.959656f);
    glVertex3f(0.182561f, -1.141235f, -0.757744f);
    glNormal3f(0.790813f, 0.068424f, 0.608221f);
    glVertex3f(0.247173f, -1.082303f, -0.823754f);
    glNormal3f(0.782164f, 0.158482f, 0.602580f);
    glVertex3f(0.267471f, -1.292418f, -0.800704f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.244061f, 0.139624f, 0.959656f);
    glVertex3f(0.182561f, -1.141235f, -0.757744f);
    glNormal3f(0.134544f, 0.016566f, 0.990769f);
    glVertex3f(0.155056f, -1.019686f, -0.761061f);
    glNormal3f(0.790813f, 0.068424f, 0.608221f);
    glVertex3f(0.247173f, -1.082303f, -0.823754f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.244061f, 0.139624f, 0.959656f);
    glVertex3f(0.182561f, -1.141235f, -0.757744f);
    glNormal3f(-0.119220f, 0.182386f, 0.975972f);
    glVertex3f(0.050351f, -1.173456f, -0.759429f);
    glNormal3f(-0.396351f, 0.086322f, 0.914032f);
    glVertex3f(0.019465f, -1.066603f, -0.805803f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.554947f, 0.081229f, 0.827911f);
    glVertex3f(0.019465f, -1.066603f, -0.805803f);
    glNormal3f(0.134544f, 0.016566f, 0.990769f);
    glVertex3f(0.155056f, -1.019686f, -0.761061f);
    glNormal3f(0.244061f, 0.139624f, 0.959656f);
    glVertex3f(0.182561f, -1.141235f, -0.757744f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.065950f, 0.071375f, 0.995267f);
    glVertex3f(0.120825f, -1.294533f, -0.740031f);
    glNormal3f(-0.119220f, 0.182386f, 0.975972f);
    glVertex3f(0.050351f, -1.173456f, -0.759429f);
    glNormal3f(0.244061f, 0.139624f, 0.959656f);
    glVertex3f(0.182561f, -1.141235f, -0.757744f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.214050f, 0.014904f, 0.976709f);
    glVertex3f(0.156422f, -0.877026f, -0.767843f);
    glNormal3f(0.708567f, 0.003797f, 0.705633f);
    glVertex3f(0.236311f, -0.877208f, -0.802294f);
    glNormal3f(0.790813f, 0.068424f, 0.608221f);
    glVertex3f(0.247173f, -1.082303f, -0.823754f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.790813f, 0.068424f, 0.608221f);
    glVertex3f(0.247173f, -1.082303f, -0.823754f);
    glNormal3f(0.134544f, 0.016566f, 0.990769f);
    glVertex3f(0.155056f, -1.019686f, -0.761061f);
    glNormal3f(0.214050f, 0.014904f, 0.976709f);
    glVertex3f(0.156422f, -0.877026f, -0.767843f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.997680f, -0.009651f, 0.067394f);
    glVertex3f(0.009734f, -0.934851f, -0.863217f);
    glNormal3f(-0.996367f, 0.015709f, -0.083706f);
    glVertex3f(0.011672f, -0.811928f, -0.863217f);
    glNormal3f(-0.929786f, -0.054549f, 0.364035f);
    glVertex3f(0.010050f, -0.745063f, -0.831362f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.189346f, 0.071503f, 0.979304f);
    glVertex3f(0.031551f, -1.326731f, -0.754941f);
    glNormal3f(-0.197735f, 0.054126f, 0.978760f);
    glVertex3f(0.043495f, -1.256644f, -0.757749f);
    glNormal3f(-0.129173f, -0.131053f, 0.982924f);
    glVertex3f(0.120825f, -1.294533f, -0.740031f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.134607f, -0.986176f, 0.096632f);
    glVertex3f(0.084501f, -1.344568f, -0.863217f);
    glNormal3f(0.001976f, -0.984700f, 0.174244f);
    glVertex3f(0.031551f, -1.326731f, -0.754941f);
    glNormal3f(0.044571f, -0.958659f, 0.281044f);
    glVertex3f(0.094254f, -1.345473f, -0.863217f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.134607f, -0.986176f, 0.096632f);
    glVertex3f(0.084501f, -1.344568f, -0.863217f);
    glNormal3f(-0.177156f, -0.981319f, 0.075025f);
    glVertex3f(-0.053990f, -1.316818f, -0.827267f);
    glNormal3f(0.001976f, -0.984700f, 0.174244f);
    glVertex3f(0.031551f, -1.326731f, -0.754941f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.124434f, -0.299548f, 0.945932f);
    glVertex3f(0.120825f, -1.294533f, -0.740031f);
    glNormal3f(-0.197735f, 0.054126f, 0.978760f);
    glVertex3f(0.043495f, -1.256644f, -0.757749f);
    glNormal3f(-0.119220f, 0.182386f, 0.975972f);
    glVertex3f(0.050351f, -1.173456f, -0.759429f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.947456f, 0.019122f, 0.319316f);
    glVertex3f(0.248934f, -0.845946f, -0.859780f);
    glNormal3f(0.958977f, 0.035720f, 0.281226f);
    glVertex3f(0.255220f, -1.020745f, -0.859013f);
    glNormal3f(0.790813f, 0.068424f, 0.608221f);
    glVertex3f(0.247173f, -1.082303f, -0.823754f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.790813f, 0.068424f, 0.608221f);
    glVertex3f(0.247173f, -1.082303f, -0.823754f);
    glNormal3f(0.708567f, 0.003797f, 0.705633f);
    glVertex3f(0.236311f, -0.877208f, -0.802294f);
    glNormal3f(0.947456f, 0.019122f, 0.319316f);
    glVertex3f(0.248934f, -0.845946f, -0.859780f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.214050f, 0.014904f, 0.976709f);
    glVertex3f(0.156422f, -0.877026f, -0.767843f);
    glNormal3f(0.134544f, 0.016566f, 0.990769f);
    glVertex3f(0.155056f, -1.019686f, -0.761061f);
    glNormal3f(-0.507006f, -0.013776f, 0.861833f);
    glVertex3f(0.070767f, -0.899902f, -0.769032f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.507006f, -0.013776f, 0.861833f);
    glVertex3f(0.070767f, -0.899902f, -0.769032f);
    glNormal3f(-0.899995f, 0.023074f, 0.435289f);
    glVertex3f(0.016924f, -0.950412f, -0.833375f);
    glNormal3f(-0.929786f, -0.054549f, 0.364035f);
    glVertex3f(0.010050f, -0.745063f, -0.831362f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.554947f, 0.081229f, 0.827911f);
    glVertex3f(0.019465f, -1.066603f, -0.805803f);
    glNormal3f(-0.899995f, 0.023074f, 0.435289f);
    glVertex3f(0.016924f, -0.950412f, -0.833375f);
    glNormal3f(-0.507006f, -0.013776f, 0.861833f);
    glVertex3f(0.070767f, -0.899902f, -0.769032f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.507006f, -0.013776f, 0.861833f);
    glVertex3f(0.070767f, -0.899902f, -0.769032f);
    glNormal3f(0.134544f, 0.016566f, 0.990769f);
    glVertex3f(0.155056f, -1.019686f, -0.761061f);
    glNormal3f(-0.554947f, 0.081229f, 0.827911f);
    glVertex3f(0.019465f, -1.066603f, -0.805803f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.400288f, -0.146101f, 0.904668f);
    glVertex3f(0.069950f, -0.044639f, -0.646965f);
    glNormal3f(0.488352f, -0.170717f, 0.855785f);
    glVertex3f(0.310899f, -0.049773f, -0.766462f);
    glNormal3f(0.416471f, -0.236036f, 0.877974f);
    glVertex3f(0.195203f, -0.122804f, -0.715009f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.416471f, -0.236036f, 0.877974f);
    glVertex3f(0.195203f, -0.122804f, -0.715009f);
    glNormal3f(0.373474f, -0.176446f, 0.910705f);
    glVertex3f(0.119633f, -0.285675f, -0.733339f);
    glNormal3f(0.144757f, -0.479912f, 0.865292f);
    glVertex3f(0.008743f, -0.234318f, -0.677689f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.416471f, -0.236036f, 0.877974f);
    glVertex3f(0.195203f, -0.122804f, -0.715009f);
    glNormal3f(0.488352f, -0.170717f, 0.855785f);
    glVertex3f(0.310899f, -0.049773f, -0.766462f);
    glNormal3f(0.372993f, 0.013195f, 0.927740f);
    glVertex3f(0.250468f, -0.208556f, -0.779856f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.372993f, 0.013195f, 0.927740f);
    glVertex3f(0.250468f, -0.208556f, -0.779856f);
    glNormal3f(0.373474f, -0.176446f, 0.910705f);
    glVertex3f(0.119633f, -0.285675f, -0.733339f);
    glNormal3f(0.416471f, -0.236036f, 0.877974f);
    glVertex3f(0.195203f, -0.122804f, -0.715009f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.417005f, -0.092715f, 0.904163f);
    glVertex3f(0.027071f, -0.683116f, -0.783065f);
    glNormal3f(-0.702549f, -0.139202f, 0.697888f);
    glVertex3f(0.028756f, -0.494042f, -0.753918f);
    glNormal3f(-0.011116f, -0.134404f, 0.990864f);
    glVertex3f(0.092273f, -0.553792f, -0.746232f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.011116f, -0.134404f, 0.990864f);
    glVertex3f(0.092273f, -0.553792f, -0.746232f);
    glNormal3f(0.252339f, -0.043591f, 0.966656f);
    glVertex3f(0.169744f, -0.683116f, -0.772239f);
    glNormal3f(-0.417005f, -0.092715f, 0.904163f);
    glVertex3f(0.027071f, -0.683116f, -0.783065f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.929786f, -0.054549f, 0.364035f);
    glVertex3f(0.010050f, -0.745063f, -0.831362f);
    glNormal3f(-0.702549f, -0.139202f, 0.697888f);
    glVertex3f(0.028756f, -0.494042f, -0.753918f);
    glNormal3f(-0.417005f, -0.092715f, 0.904163f);
    glVertex3f(0.027071f, -0.683116f, -0.783065f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.417005f, -0.092715f, 0.904163f);
    glVertex3f(0.027071f, -0.683116f, -0.783065f);
    glNormal3f(-0.507006f, -0.013776f, 0.861833f);
    glVertex3f(0.070767f, -0.899902f, -0.769032f);
    glNormal3f(-0.929786f, -0.054549f, 0.364035f);
    glVertex3f(0.010050f, -0.745063f, -0.831362f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.417005f, -0.092715f, 0.904163f);
    glVertex3f(0.027071f, -0.683116f, -0.783065f);
    glNormal3f(0.252339f, -0.043591f, 0.966656f);
    glVertex3f(0.169744f, -0.683116f, -0.772239f);
    glNormal3f(0.214050f, 0.014904f, 0.976709f);
    glVertex3f(0.156422f, -0.877026f, -0.767843f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.214050f, 0.014904f, 0.976709f);
    glVertex3f(0.156422f, -0.877026f, -0.767843f);
    glNormal3f(-0.507006f, -0.013776f, 0.861833f);
    glVertex3f(0.070767f, -0.899902f, -0.769032f);
    glNormal3f(-0.417005f, -0.092715f, 0.904163f);
    glVertex3f(0.027071f, -0.683116f, -0.783065f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.759919f, -0.007888f, 0.649969f);
    glVertex3f(0.223525f, -0.619366f, -0.802212f);
    glNormal3f(0.880802f, -0.083835f, 0.466003f);
    glVertex3f(0.254234f, -0.553982f, -0.848493f);
    glNormal3f(0.947456f, 0.019122f, 0.319316f);
    glVertex3f(0.248934f, -0.845946f, -0.859780f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.708567f, 0.003797f, 0.705633f);
    glVertex3f(0.236311f, -0.877208f, -0.802294f);
    glNormal3f(0.759919f, -0.007888f, 0.649969f);
    glVertex3f(0.223525f, -0.619366f, -0.802212f);
    glNormal3f(0.947456f, 0.019122f, 0.319316f);
    glVertex3f(0.248934f, -0.845946f, -0.859780f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.835086f, -0.509717f, 0.206933f);
    glVertex3f(-0.064120f, -0.290679f, -0.828945f);
    glNormal3f(-0.614338f, -0.756525f, 0.224183f);
    glVertex3f(-0.116689f, -0.250694f, -0.863217f);
    glNormal3f(-0.612993f, -0.711701f, 0.343105f);
    glVertex3f(-0.097175f, -0.225718f, -0.725458f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.632528f, -0.637494f, 0.439897f);
    glVertex3f(-0.097175f, -0.225718f, -0.725458f);
    glNormal3f(-0.143762f, -0.272842f, 0.951257f);
    glVertex3f(0.054650f, -0.342011f, -0.721095f);
    glNormal3f(-0.813622f, -0.375971f, 0.443469f);
    glVertex3f(-0.034216f, -0.341212f, -0.795286f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.813622f, -0.375971f, 0.443469f);
    glVertex3f(-0.034216f, -0.341212f, -0.795286f);
    glNormal3f(-0.835086f, -0.509717f, 0.206933f);
    glVertex3f(-0.064120f, -0.290679f, -0.828945f);
    glNormal3f(-0.665355f, -0.713810f, 0.218581f);
    glVertex3f(-0.097175f, -0.225718f, -0.725458f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.632528f, -0.637494f, 0.439897f);
    glVertex3f(-0.097175f, -0.225718f, -0.725458f);
    glNormal3f(0.144757f, -0.479912f, 0.865292f);
    glVertex3f(0.008743f, -0.234318f, -0.677689f);
    glNormal3f(-0.143762f, -0.272842f, 0.951257f);
    glVertex3f(0.054650f, -0.342011f, -0.721095f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.283410f, 0.238432f, 0.928886f);
    glVertex3f(0.461922f, -0.197001f, -0.837322f);
    glNormal3f(0.461861f, -0.492611f, 0.737576f);
    glVertex3f(0.460735f, -0.251681f, -0.851292f);
    glNormal3f(0.338905f, -0.268519f, 0.901688f);
    glVertex3f(0.387697f, -0.255172f, -0.815163f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.768704f, -0.242640f, -0.591794f);
    glVertex3f(0.250468f, -0.208556f, -0.779856f);
    glNormal3f(0.768704f, -0.242640f, -0.591794f);
    glVertex3f(0.310899f, -0.049773f, -0.766462f);
    glNormal3f(0.768704f, -0.242640f, -0.591794f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.258332f, 0.459728f, 0.849656f);
    glVertex3f(0.365111f, -0.138507f, -0.854915f);
    glNormal3f(0.372993f, 0.013195f, 0.927740f);
    glVertex3f(0.250468f, -0.208556f, -0.779856f);
    glNormal3f(0.091110f, 0.740082f, 0.666316f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.252339f, -0.043591f, 0.966656f);
    glVertex3f(0.169744f, -0.683116f, -0.772239f);
    glNormal3f(0.759919f, -0.007888f, 0.649969f);
    glVertex3f(0.223525f, -0.619366f, -0.802212f);
    glNormal3f(0.708567f, 0.003797f, 0.705633f);
    glVertex3f(0.236311f, -0.877208f, -0.802294f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.708567f, 0.003797f, 0.705633f);
    glVertex3f(0.236311f, -0.877208f, -0.802294f);
    glNormal3f(0.214050f, 0.014904f, 0.976709f);
    glVertex3f(0.156422f, -0.877026f, -0.767843f);
    glNormal3f(0.252339f, -0.043591f, 0.966656f);
    glVertex3f(0.169744f, -0.683116f, -0.772239f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.252339f, -0.043591f, 0.966656f);
    glVertex3f(0.169744f, -0.683116f, -0.772239f);
    glNormal3f(0.423941f, -0.059070f, 0.903761f);
    glVertex3f(0.146301f, -0.437737f, -0.754884f);
    glNormal3f(0.759919f, -0.007888f, 0.649969f);
    glVertex3f(0.223525f, -0.619366f, -0.802212f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.011116f, -0.134404f, 0.990864f);
    glVertex3f(0.092273f, -0.553792f, -0.746232f);
    glNormal3f(0.423941f, -0.059070f, 0.903761f);
    glVertex3f(0.146301f, -0.437737f, -0.754884f);
    glNormal3f(0.252339f, -0.043591f, 0.966656f);
    glVertex3f(0.169744f, -0.683116f, -0.772239f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.423941f, -0.059070f, 0.903761f);
    glVertex3f(0.146301f, -0.437737f, -0.754884f);
    glNormal3f(0.658787f, -0.145683f, 0.738089f);
    glVertex3f(0.270979f, -0.457437f, -0.854275f);
    glNormal3f(0.759919f, -0.007888f, 0.649969f);
    glVertex3f(0.223525f, -0.619366f, -0.802212f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.423941f, -0.059070f, 0.903761f);
    glVertex3f(0.146301f, -0.437737f, -0.754884f);
    glNormal3f(0.373474f, -0.176446f, 0.910705f);
    glVertex3f(0.119633f, -0.285675f, -0.733339f);
    glNormal3f(0.397346f, -0.212295f, 0.892775f);
    glVertex3f(0.228631f, -0.303608f, -0.782524f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.397346f, -0.212295f, 0.892775f);
    glVertex3f(0.228631f, -0.303608f, -0.782524f);
    glNormal3f(0.658787f, -0.145683f, 0.738089f);
    glVertex3f(0.270979f, -0.457437f, -0.854275f);
    glNormal3f(0.423941f, -0.059070f, 0.903761f);
    glVertex3f(0.146301f, -0.437737f, -0.754884f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.423941f, -0.059070f, 0.903761f);
    glVertex3f(0.146301f, -0.437737f, -0.754884f);
    glNormal3f(-0.011116f, -0.134404f, 0.990864f);
    glVertex3f(0.092273f, -0.553792f, -0.746232f);
    glNormal3f(-0.143762f, -0.272842f, 0.951257f);
    glVertex3f(0.054650f, -0.342011f, -0.721095f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.143762f, -0.272842f, 0.951257f);
    glVertex3f(0.054650f, -0.342011f, -0.721095f);
    glNormal3f(0.373474f, -0.176446f, 0.910705f);
    glVertex3f(0.119633f, -0.285675f, -0.733339f);
    glNormal3f(0.423941f, -0.059070f, 0.903761f);
    glVertex3f(0.146301f, -0.437737f, -0.754884f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.005559f, 0.866332f, 0.499438f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glNormal3f(0.166632f, 0.940674f, 0.295576f);
    glVertex3f(0.310899f, -0.049773f, -0.766462f);
    glNormal3f(-0.087713f, 0.994488f, 0.057447f);
    glVertex3f(0.069950f, -0.044639f, -0.646965f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.048642f, 0.755790f, 0.653005f);
    glVertex3f(-0.138077f, -0.026121f, -0.863217f);
    glNormal3f(-0.051833f, 0.565882f, 0.822855f);
    glVertex3f(0.041470f, -0.009675f, -0.863217f);
    glNormal3f(0.036916f, 0.810000f, 0.585266f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.275384f, 0.320868f, 0.906205f);
    glVertex3f(-0.169610f, -0.116025f, -0.792318f);
    glNormal3f(-0.066285f, 0.664089f, 0.744710f);
    glVertex3f(-0.166645f, -0.040188f, -0.837342f);
    glNormal3f(0.091110f, 0.740082f, 0.666316f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.005559f, 0.866332f, 0.499438f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glNormal3f(-0.302506f, 0.631654f, 0.713795f);
    glVertex3f(-0.084380f, -0.121112f, -0.751696f);
    glNormal3f(-0.189309f, 0.537988f, 0.821420f);
    glVertex3f(-0.169610f, -0.116025f, -0.792318f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.019994f, 0.506310f, 0.862120f);
    glVertex3f(-0.356588f, -0.047576f, -0.863217f);
    glNormal3f(-0.066285f, 0.664089f, 0.744710f);
    glVertex3f(-0.166645f, -0.040188f, -0.837342f);
    glNormal3f(-0.275384f, 0.320868f, 0.906205f);
    glVertex3f(-0.169610f, -0.116025f, -0.792318f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.281525f, 0.193042f, 0.939935f);
    glVertex3f(-0.169610f, -0.116025f, -0.792318f);
    glNormal3f(-0.431620f, -0.752985f, 0.496708f);
    glVertex3f(-0.190139f, -0.193962f, -0.837819f);
    glNormal3f(0.118243f, -0.607455f, 0.785504f);
    glVertex3f(-0.373172f, -0.171400f, -0.813573f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.114994f, -0.088376f, 0.989427f);
    glVertex3f(-0.373172f, -0.171400f, -0.813573f);
    glNormal3f(0.019994f, 0.506310f, 0.862120f);
    glVertex3f(-0.356588f, -0.047576f, -0.863217f);
    glNormal3f(-0.275384f, 0.320868f, 0.906205f);
    glVertex3f(-0.169610f, -0.116025f, -0.792318f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.275384f, 0.320868f, 0.906205f);
    glVertex3f(-0.169610f, -0.116025f, -0.792318f);
    glNormal3f(-0.302506f, 0.631654f, 0.713795f);
    glVertex3f(-0.084380f, -0.121112f, -0.751696f);
    glNormal3f(-0.565981f, -0.270603f, 0.778742f);
    glVertex3f(-0.097175f, -0.225718f, -0.725458f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.632528f, -0.637494f, 0.439897f);
    glVertex3f(-0.097175f, -0.225718f, -0.725458f);
    glNormal3f(-0.496333f, -0.570120f, 0.654689f);
    glVertex3f(-0.190139f, -0.193962f, -0.837819f);
    glNormal3f(-0.281525f, 0.193042f, 0.939935f);
    glVertex3f(-0.169610f, -0.116025f, -0.792318f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.240961f, -0.888456f, 0.390620f);
    glVertex3f(-0.190139f, -0.193962f, -0.837819f);
    glNormal3f(0.019467f, -0.989804f, 0.141101f);
    glVertex3f(-0.305042f, -0.177137f, -0.863217f);
    glNormal3f(0.079412f, -0.850489f, 0.519963f);
    glVertex3f(-0.373172f, -0.171400f, -0.813573f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.095055f, 0.878142f, 0.468861f);
    glVertex3f(-0.594790f, -0.086759f, -0.774949f);
    glNormal3f(-0.134276f, 0.970800f, 0.198791f);
    glVertex3f(-0.568352f, -0.065048f, -0.863117f);
    glNormal3f(0.037076f, 0.852286f, 0.521761f);
    glVertex3f(-0.471030f, -0.055032f, -0.862871f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.195293f, 0.484991f, 0.852435f);
    glVertex3f(-0.459383f, -0.127919f, -0.781238f);
    glNormal3f(0.037076f, 0.852286f, 0.521761f);
    glVertex3f(-0.471030f, -0.055032f, -0.862871f);
    glNormal3f(0.019994f, 0.506310f, 0.862120f);
    glVertex3f(-0.356588f, -0.047576f, -0.863217f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.186790f, 0.162189f, 0.968919f);
    glVertex3f(-0.459383f, -0.127919f, -0.781238f);
    glNormal3f(-0.057865f, 0.080785f, 0.995050f);
    glVertex3f(-0.714096f, -0.165166f, -0.766469f);
    glNormal3f(-0.011796f, 0.501080f, 0.865321f);
    glVertex3f(-0.594790f, -0.086759f, -0.774949f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.069782f, 0.766784f, 0.638101f);
    glVertex3f(-0.594790f, -0.086759f, -0.774949f);
    glNormal3f(0.037076f, 0.852286f, 0.521761f);
    glVertex3f(-0.471030f, -0.055032f, -0.862871f);
    glNormal3f(0.195293f, 0.484991f, 0.852435f);
    glVertex3f(-0.459383f, -0.127919f, -0.781238f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.197087f, -0.179341f, 0.963843f);
    glVertex3f(-0.459383f, -0.127919f, -0.781238f);
    glNormal3f(0.118243f, -0.607455f, 0.785504f);
    glVertex3f(-0.373172f, -0.171400f, -0.813573f);
    glNormal3f(0.057814f, -0.765680f, 0.640619f);
    glVertex3f(-0.636701f, -0.218657f, -0.809379f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.057814f, -0.765680f, 0.640619f);
    glVertex3f(-0.636701f, -0.218657f, -0.809379f);
    glNormal3f(0.056457f, -0.392617f, 0.917967f);
    glVertex3f(-0.714096f, -0.165166f, -0.766469f);
    glNormal3f(0.197087f, -0.179341f, 0.963843f);
    glVertex3f(-0.459383f, -0.127919f, -0.781238f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.186790f, 0.162189f, 0.968919f);
    glVertex3f(-0.459383f, -0.127919f, -0.781238f);
    glNormal3f(0.019994f, 0.506310f, 0.862120f);
    glVertex3f(-0.356588f, -0.047576f, -0.863217f);
    glNormal3f(0.114994f, -0.088376f, 0.989427f);
    glVertex3f(-0.373172f, -0.171400f, -0.813573f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.019467f, -0.989804f, 0.141101f);
    glVertex3f(-0.305042f, -0.177137f, -0.863217f);
    glNormal3f(0.123033f, -0.945887f, 0.300266f);
    glVertex3f(-0.599245f, -0.230560f, -0.863171f);
    glNormal3f(0.079412f, -0.850489f, 0.519963f);
    glVertex3f(-0.373172f, -0.171400f, -0.813573f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.057814f, -0.765680f, 0.640619f);
    glVertex3f(-0.636701f, -0.218657f, -0.809379f);
    glNormal3f(0.079412f, -0.850489f, 0.519963f);
    glVertex3f(-0.373172f, -0.171400f, -0.813573f);
    glNormal3f(0.123033f, -0.945887f, 0.300266f);
    glVertex3f(-0.599245f, -0.230560f, -0.863171f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.762750f, 0.059562f, -0.643944f);
    glVertex3f(-0.902275f, -0.170380f, -0.774857f);
    glNormal3f(-0.762750f, 0.059562f, -0.643944f);
    glVertex3f(-0.832987f, -0.237200f, -0.863109f);
    glNormal3f(-0.762750f, 0.059562f, -0.643944f);
    glVertex3f(-0.822950f, -0.109174f, -0.863156f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.112325f, 0.989750f, 0.088189f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glNormal3f(0.109989f, 0.968878f, 0.221759f);
    glVertex3f(-0.155532f, -0.041710f, -0.622009f);
    glNormal3f(-0.280883f, 0.709469f, -0.646343f);
    glVertex3f(-0.122168f, -0.055722f, -0.688835f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.108538f, 0.972948f, 0.203942f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glNormal3f(-0.087713f, 0.994488f, 0.057447f);
    glVertex3f(0.069950f, -0.044639f, -0.646965f);
    glNormal3f(0.080555f, 0.910371f, 0.405877f);
    glVertex3f(-0.082268f, -0.089253f, -0.598229f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.272652f, 0.408449f, 0.871109f);
    glVertex3f(-0.082268f, -0.089253f, -0.598229f);
    glNormal3f(0.109989f, 0.968878f, 0.221759f);
    glVertex3f(-0.155532f, -0.041710f, -0.622009f);
    glNormal3f(0.005559f, 0.866332f, 0.499438f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.400288f, -0.146101f, 0.904668f);
    glVertex3f(0.069950f, -0.044639f, -0.646965f);
    glNormal3f(0.416471f, -0.236036f, 0.877974f);
    glVertex3f(0.195203f, -0.122804f, -0.715009f);
    glNormal3f(0.366226f, 0.113331f, 0.923599f);
    glVertex3f(-0.082268f, -0.089253f, -0.598229f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.366226f, 0.113331f, 0.923599f);
    glVertex3f(-0.082268f, -0.089253f, -0.598229f);
    glNormal3f(0.144757f, -0.479912f, 0.865292f);
    glVertex3f(0.008743f, -0.234318f, -0.677689f);
    glNormal3f(0.349199f, -0.702327f, 0.620320f);
    glVertex3f(-0.217581f, -0.184721f, -0.592074f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.332132f, -0.804332f, 0.492685f);
    glVertex3f(-0.217581f, -0.184721f, -0.592074f);
    glNormal3f(0.467873f, -0.060944f, 0.881692f);
    glVertex3f(-0.261022f, -0.120101f, -0.519834f);
    glNormal3f(0.354471f, -0.171755f, 0.919158f);
    glVertex3f(-0.082268f, -0.089253f, -0.598229f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.366226f, 0.113331f, 0.923599f);
    glVertex3f(-0.082268f, -0.089253f, -0.598229f);
    glNormal3f(0.416471f, -0.236036f, 0.877974f);
    glVertex3f(0.195203f, -0.122804f, -0.715009f);
    glNormal3f(0.144757f, -0.479912f, 0.865292f);
    glVertex3f(0.008743f, -0.234318f, -0.677689f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.209316f, -0.931004f, 0.299028f);
    glVertex3f(-0.217581f, -0.184721f, -0.592074f);
    glNormal3f(0.093513f, -0.533097f, 0.840870f);
    glVertex3f(0.008743f, -0.234318f, -0.677689f);
    glNormal3f(-0.612993f, -0.711701f, 0.343105f);
    glVertex3f(-0.097175f, -0.225718f, -0.725458f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.354146f, -0.692305f, -0.628724f);
    glVertex3f(-0.225230f, -0.167798f, -0.660112f);
    glNormal3f(0.004487f, -0.994609f, -0.103603f);
    glVertex3f(-0.217581f, -0.184721f, -0.592074f);
    glNormal3f(-0.665355f, -0.713810f, 0.218581f);
    glVertex3f(-0.097175f, -0.225718f, -0.725458f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.504981f, -0.242371f, -0.828403f);
    glVertex3f(-0.225230f, -0.167798f, -0.660112f);
    glNormal3f(-0.715821f, -0.585635f, -0.380305f);
    glVertex3f(-0.097175f, -0.225718f, -0.725458f);
    glNormal3f(-0.510876f, 0.255837f, -0.820703f);
    glVertex3f(-0.084380f, -0.121112f, -0.751696f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.288814f, 0.620054f, -0.729465f);
    glVertex3f(-0.122168f, -0.055722f, -0.688835f);
    glNormal3f(-0.446226f, -0.046676f, -0.893702f);
    glVertex3f(-0.225230f, -0.167798f, -0.660112f);
    glNormal3f(-0.510876f, 0.255837f, -0.820703f);
    glVertex3f(-0.084380f, -0.121112f, -0.751696f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.322339f, 0.836618f, -0.442908f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glNormal3f(-0.288814f, 0.620054f, -0.729465f);
    glVertex3f(-0.122168f, -0.055722f, -0.688835f);
    glNormal3f(-0.510876f, 0.255837f, -0.820703f);
    glVertex3f(-0.084380f, -0.121112f, -0.751696f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.029527f, 0.998471f, -0.046733f);
    glVertex3f(-0.388826f, -0.015839f, -0.556270f);
    glNormal3f(-0.399310f, 0.478277f, -0.782178f);
    glVertex3f(-0.434967f, -0.043784f, -0.602240f);
    glNormal3f(-0.288814f, 0.620054f, -0.729465f);
    glVertex3f(-0.122168f, -0.055722f, -0.688835f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.263959f, 0.805758f, -0.530170f);
    glVertex3f(-0.122168f, -0.055722f, -0.688835f);
    glNormal3f(0.109989f, 0.968878f, 0.221759f);
    glVertex3f(-0.155532f, -0.041710f, -0.622009f);
    glNormal3f(0.062909f, 0.976734f, 0.205019f);
    glVertex3f(-0.388826f, -0.015839f, -0.556270f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.062909f, 0.976734f, 0.205019f);
    glVertex3f(-0.388826f, -0.015839f, -0.556270f);
    glNormal3f(0.457985f, 0.396812f, 0.795481f);
    glVertex3f(-0.261022f, -0.120101f, -0.519834f);
    glNormal3f(0.208701f, 0.782065f, 0.587213f);
    glVertex3f(-0.397746f, -0.040502f, -0.478749f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.089221f, 0.943019f, 0.320553f);
    glVertex3f(-0.388826f, -0.015839f, -0.556270f);
    glNormal3f(0.109989f, 0.968878f, 0.221759f);
    glVertex3f(-0.155532f, -0.041710f, -0.622009f);
    glNormal3f(0.272652f, 0.408449f, 0.871109f);
    glVertex3f(-0.082268f, -0.089253f, -0.598229f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.366226f, 0.113331f, 0.923599f);
    glVertex3f(-0.082268f, -0.089253f, -0.598229f);
    glNormal3f(0.524061f, 0.099075f, 0.845899f);
    glVertex3f(-0.261022f, -0.120101f, -0.519834f);
    glNormal3f(0.190957f, 0.892612f, 0.408385f);
    glVertex3f(-0.388826f, -0.015839f, -0.556270f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.209316f, -0.931004f, 0.299028f);
    glVertex3f(-0.217581f, -0.184721f, -0.592074f);
    glNormal3f(0.176586f, -0.904340f, 0.388570f);
    glVertex3f(-0.459037f, -0.268397f, -0.485736f);
    glNormal3f(0.445692f, -0.532170f, 0.719829f);
    glVertex3f(-0.381287f, -0.229778f, -0.476858f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.445692f, -0.532170f, 0.719829f);
    glVertex3f(-0.381287f, -0.229778f, -0.476858f);
    glNormal3f(0.467873f, -0.060944f, 0.881692f);
    glVertex3f(-0.261022f, -0.120101f, -0.519834f);
    glNormal3f(0.349199f, -0.702327f, 0.620320f);
    glVertex3f(-0.217581f, -0.184721f, -0.592074f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.154451f, -0.691878f, -0.705301f);
    glVertex3f(-0.380847f, -0.211456f, -0.577348f);
    glNormal3f(-0.034582f, -0.911971f, -0.408794f);
    glVertex3f(-0.459037f, -0.268397f, -0.485736f);
    glNormal3f(0.004487f, -0.994609f, -0.103603f);
    glVertex3f(-0.217581f, -0.184721f, -0.592074f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.264453f, -0.833305f, -0.485455f);
    glVertex3f(-0.225230f, -0.167798f, -0.660112f);
    glNormal3f(-0.154451f, -0.691878f, -0.705301f);
    glVertex3f(-0.380847f, -0.211456f, -0.577348f);
    glNormal3f(0.084868f, -0.995126f, 0.050211f);
    glVertex3f(-0.217581f, -0.184721f, -0.592074f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.315730f, -0.167920f, -0.933872f);
    glVertex3f(-0.353801f, -0.120100f, -0.627383f);
    glNormal3f(-0.154451f, -0.691878f, -0.705301f);
    glVertex3f(-0.380847f, -0.211456f, -0.577348f);
    glNormal3f(-0.427605f, -0.419585f, -0.800689f);
    glVertex3f(-0.225230f, -0.167798f, -0.660112f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.315730f, -0.167920f, -0.933872f);
    glVertex3f(-0.353801f, -0.120100f, -0.627383f);
    glNormal3f(-0.446226f, -0.046676f, -0.893702f);
    glVertex3f(-0.225230f, -0.167798f, -0.660112f);
    glNormal3f(-0.344150f, 0.393966f, -0.852263f);
    glVertex3f(-0.122168f, -0.055722f, -0.688835f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.336858f, 0.513511f, -0.789198f);
    glVertex3f(-0.122168f, -0.055722f, -0.688835f);
    glNormal3f(-0.362141f, 0.309779f, -0.879142f);
    glVertex3f(-0.434967f, -0.043784f, -0.602240f);
    glNormal3f(-0.315730f, -0.167920f, -0.933872f);
    glVertex3f(-0.353801f, -0.120100f, -0.627383f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.384754f, 0.764625f, -0.517024f);
    glVertex3f(-0.434967f, -0.043784f, -0.602240f);
    glNormal3f(0.024491f, 0.996296f, 0.082433f);
    glVertex3f(-0.388826f, -0.015839f, -0.556270f);
    glNormal3f(-0.535837f, 0.844239f, 0.011799f);
    glVertex3f(-0.659353f, -0.116373f, -0.467530f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.439710f, 0.866516f, 0.236233f);
    glVertex3f(-0.659353f, -0.116373f, -0.467530f);
    glNormal3f(0.062909f, 0.976734f, 0.205019f);
    glVertex3f(-0.388826f, -0.015839f, -0.556270f);
    glNormal3f(0.125360f, 0.887228f, 0.443973f);
    glVertex3f(-0.397746f, -0.040502f, -0.478749f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.003358f, 0.978514f, 0.206152f);
    glVertex3f(-0.397746f, -0.040502f, -0.478749f);
    glNormal3f(-0.536757f, 0.724277f, 0.432799f);
    glVertex3f(-0.557076f, -0.085524f, -0.392311f);
    glNormal3f(-0.535837f, 0.844239f, 0.011799f);
    glVertex3f(-0.659353f, -0.116373f, -0.467530f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.360320f, -0.125710f, 0.924319f);
    glVertex3f(-0.494179f, -0.156218f, -0.405392f);
    glNormal3f(-0.009979f, 0.166114f, 0.986056f);
    glVertex3f(-0.557076f, -0.085524f, -0.392311f);
    glNormal3f(0.493000f, 0.439298f, 0.750978f);
    glVertex3f(-0.397746f, -0.040502f, -0.478749f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.329031f, 0.637291f, 0.696849f);
    glVertex3f(-0.397746f, -0.040502f, -0.478749f);
    glNormal3f(0.524061f, 0.099075f, 0.845899f);
    glVertex3f(-0.261022f, -0.120101f, -0.519834f);
    glNormal3f(0.360320f, -0.125710f, 0.924319f);
    glVertex3f(-0.494179f, -0.156218f, -0.405392f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.360320f, -0.125710f, 0.924319f);
    glVertex3f(-0.494179f, -0.156218f, -0.405392f);
    glNormal3f(-0.008508f, -0.081603f, 0.996629f);
    glVertex3f(-0.612213f, -0.236795f, -0.386462f);
    glNormal3f(-0.009979f, 0.166114f, 0.986056f);
    glVertex3f(-0.557076f, -0.085524f, -0.392311f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.360320f, -0.125710f, 0.924319f);
    glVertex3f(-0.494179f, -0.156218f, -0.405392f);
    glNormal3f(0.524061f, 0.099075f, 0.845899f);
    glVertex3f(-0.261022f, -0.120101f, -0.519834f);
    glNormal3f(0.445692f, -0.532170f, 0.719829f);
    glVertex3f(-0.381287f, -0.229778f, -0.476858f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.214937f, -0.620163f, 0.754453f);
    glVertex3f(-0.459037f, -0.268397f, -0.485736f);
    glNormal3f(0.360320f, -0.125710f, 0.924319f);
    glVertex3f(-0.494179f, -0.156218f, -0.405392f);
    glNormal3f(0.445692f, -0.532170f, 0.719829f);
    glVertex3f(-0.381287f, -0.229778f, -0.476858f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.184532f, -0.795635f, -0.576987f);
    glVertex3f(-0.459037f, -0.268397f, -0.485736f);
    glNormal3f(-0.666148f, -0.315664f, -0.675724f);
    glVertex3f(-0.659353f, -0.116373f, -0.467530f);
    glNormal3f(-0.516296f, -0.608083f, -0.603054f);
    glVertex3f(-0.612213f, -0.236795f, -0.386462f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.310569f, -0.238787f, 0.920069f);
    glVertex3f(-0.612213f, -0.236795f, -0.386462f);
    glNormal3f(0.360320f, -0.125710f, 0.924319f);
    glVertex3f(-0.494179f, -0.156218f, -0.405392f);
    glNormal3f(0.214937f, -0.620163f, 0.754453f);
    glVertex3f(-0.459037f, -0.268397f, -0.485736f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.214937f, -0.620163f, 0.754453f);
    glVertex3f(-0.459037f, -0.268397f, -0.485736f);
    glNormal3f(-0.225291f, -0.403082f, 0.887000f);
    glVertex3f(-0.549598f, -0.245657f, -0.498404f);
    glNormal3f(-0.460110f, -0.080334f, 0.884220f);
    glVertex3f(-0.659353f, -0.116373f, -0.467530f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.154451f, -0.691878f, -0.705301f);
    glVertex3f(-0.380847f, -0.211456f, -0.577348f);
    glNormal3f(-0.412012f, -0.617016f, -0.670475f);
    glVertex3f(-0.549598f, -0.245657f, -0.498404f);
    glNormal3f(-0.034582f, -0.911971f, -0.408794f);
    glVertex3f(-0.459037f, -0.268397f, -0.485736f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.491313f, -0.248244f, -0.834857f);
    glVertex3f(-0.595569f, -0.156218f, -0.526427f);
    glNormal3f(-0.412012f, -0.617016f, -0.670475f);
    glVertex3f(-0.549598f, -0.245657f, -0.498404f);
    glNormal3f(-0.154451f, -0.691878f, -0.705301f);
    glVertex3f(-0.380847f, -0.211456f, -0.577348f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.154451f, -0.691878f, -0.705301f);
    glVertex3f(-0.380847f, -0.211456f, -0.577348f);
    glNormal3f(-0.315730f, -0.167920f, -0.933872f);
    glVertex3f(-0.353801f, -0.120100f, -0.627383f);
    glNormal3f(-0.491313f, -0.248244f, -0.834857f);
    glVertex3f(-0.595569f, -0.156218f, -0.526427f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.666148f, -0.315664f, -0.675724f);
    glVertex3f(-0.659353f, -0.116373f, -0.467530f);
    glNormal3f(-0.412012f, -0.617016f, -0.670475f);
    glVertex3f(-0.549598f, -0.245657f, -0.498404f);
    glNormal3f(-0.491313f, -0.248244f, -0.834857f);
    glVertex3f(-0.595569f, -0.156218f, -0.526427f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.491313f, -0.248244f, -0.834857f);
    glVertex3f(-0.595569f, -0.156218f, -0.526427f);
    glNormal3f(-0.315730f, -0.167920f, -0.933872f);
    glVertex3f(-0.353801f, -0.120100f, -0.627383f);
    glNormal3f(-0.362141f, 0.309779f, -0.879142f);
    glVertex3f(-0.434967f, -0.043784f, -0.602240f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.399310f, 0.478277f, -0.782178f);
    glVertex3f(-0.434967f, -0.043784f, -0.602240f);
    glNormal3f(-0.740376f, 0.302321f, -0.600370f);
    glVertex3f(-0.659353f, -0.116373f, -0.467530f);
    glNormal3f(-0.491313f, -0.248244f, -0.834857f);
    glVertex3f(-0.595569f, -0.156218f, -0.526427f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.103104f, 0.472361f, 0.875354f);
    glVertex3f(-0.557076f, -0.085524f, -0.392311f);
    glNormal3f(-0.248361f, 0.127653f, 0.960220f);
    glVertex3f(-0.612213f, -0.236795f, -0.386462f);
    glNormal3f(-0.489794f, 0.731294f, 0.474670f);
    glVertex3f(-0.659353f, -0.116373f, -0.467530f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.143762f, -0.272842f, 0.951257f);
    glVertex3f(0.054650f, -0.342011f, -0.721095f);
    glNormal3f(-0.011116f, -0.134404f, 0.990864f);
    glVertex3f(0.092273f, -0.553792f, -0.746232f);
    glNormal3f(-0.702549f, -0.139202f, 0.697888f);
    glVertex3f(0.028756f, -0.494042f, -0.753918f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.702549f, -0.139202f, 0.697888f);
    glVertex3f(0.028756f, -0.494042f, -0.753918f);
    glNormal3f(-0.899765f, -0.217097f, 0.378538f);
    glVertex3f(-0.031199f, -0.430955f, -0.863217f);
    glNormal3f(-0.813622f, -0.375971f, 0.443469f);
    glVertex3f(-0.034216f, -0.341212f, -0.795286f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.813622f, -0.375971f, 0.443469f);
    glVertex3f(-0.034216f, -0.341212f, -0.795286f);
    glNormal3f(-0.143762f, -0.272842f, 0.951257f);
    glVertex3f(0.054650f, -0.342011f, -0.721095f);
    glNormal3f(-0.702549f, -0.139202f, 0.697888f);
    glVertex3f(0.028756f, -0.494042f, -0.753918f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.929786f, -0.054549f, 0.364035f);
    glVertex3f(0.010050f, -0.745063f, -0.831362f);
    glNormal3f(-0.899765f, -0.217097f, 0.378538f);
    glVertex3f(-0.031199f, -0.430955f, -0.863217f);
    glNormal3f(-0.702549f, -0.139202f, 0.697888f);
    glVertex3f(0.028756f, -0.494042f, -0.753918f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.658787f, -0.145683f, 0.738089f);
    glVertex3f(0.270979f, -0.457437f, -0.854275f);
    glNormal3f(0.880802f, -0.083835f, 0.466003f);
    glVertex3f(0.254234f, -0.553982f, -0.848493f);
    glNormal3f(0.759919f, -0.007888f, 0.649969f);
    glVertex3f(0.223525f, -0.619366f, -0.802212f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.143762f, -0.272842f, 0.951257f);
    glVertex3f(0.054650f, -0.342011f, -0.721095f);
    glNormal3f(0.192491f, -0.327101f, 0.925177f);
    glVertex3f(0.008743f, -0.234318f, -0.677689f);
    glNormal3f(0.373474f, -0.176446f, 0.910705f);
    glVertex3f(0.119633f, -0.285675f, -0.733339f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.372993f, 0.013195f, 0.927740f);
    glVertex3f(0.250468f, -0.208556f, -0.779856f);
    glNormal3f(0.397346f, -0.212295f, 0.892775f);
    glVertex3f(0.228631f, -0.303608f, -0.782524f);
    glNormal3f(0.373474f, -0.176446f, 0.910705f);
    glVertex3f(0.119633f, -0.285675f, -0.733339f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.258332f, 0.459728f, 0.849656f);
    glVertex3f(0.365111f, -0.138507f, -0.854915f);
    glNormal3f(0.283410f, 0.238432f, 0.928886f);
    glVertex3f(0.461922f, -0.197001f, -0.837322f);
    glNormal3f(0.372993f, 0.013195f, 0.927740f);
    glVertex3f(0.250468f, -0.208556f, -0.779856f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.258332f, 0.459728f, 0.849656f);
    glVertex3f(0.365111f, -0.138507f, -0.854915f);
    glNormal3f(0.169445f, 0.530291f, 0.830711f);
    glVertex3f(0.469989f, -0.179640f, -0.850050f);
    glNormal3f(0.283410f, 0.238432f, 0.928886f);
    glVertex3f(0.461922f, -0.197001f, -0.837322f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.527623f, -0.733792f, 0.427976f);
    glVertex3f(0.454444f, -0.265600f, -0.863217f);
    glNormal3f(0.540819f, -0.776697f, 0.322886f);
    glVertex3f(0.390768f, -0.309938f, -0.863217f);
    glNormal3f(0.451746f, -0.576724f, 0.680672f);
    glVertex3f(0.345968f, -0.335014f, -0.848499f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.338905f, -0.268519f, 0.901688f);
    glVertex3f(0.387697f, -0.255172f, -0.815163f);
    glNormal3f(0.461861f, -0.492611f, 0.737576f);
    glVertex3f(0.460735f, -0.251681f, -0.851292f);
    glNormal3f(0.451746f, -0.576724f, 0.680672f);
    glVertex3f(0.345968f, -0.335014f, -0.848499f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.451746f, -0.576724f, 0.680672f);
    glVertex3f(0.345968f, -0.335014f, -0.848499f);
    glNormal3f(0.658787f, -0.145683f, 0.738089f);
    glVertex3f(0.270979f, -0.457437f, -0.854275f);
    glNormal3f(0.397346f, -0.212295f, 0.892775f);
    glVertex3f(0.228631f, -0.303608f, -0.782524f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.397346f, -0.212295f, 0.892775f);
    glVertex3f(0.228631f, -0.303608f, -0.782524f);
    glNormal3f(0.338905f, -0.268519f, 0.901688f);
    glVertex3f(0.387697f, -0.255172f, -0.815163f);
    glNormal3f(0.451746f, -0.576724f, 0.680672f);
    glVertex3f(0.345968f, -0.335014f, -0.848499f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.338905f, -0.268519f, 0.901688f);
    glVertex3f(0.387697f, -0.255172f, -0.815163f);
    glNormal3f(0.397346f, -0.212295f, 0.892775f);
    glVertex3f(0.228631f, -0.303608f, -0.782524f);
    glNormal3f(0.372993f, 0.013195f, 0.927740f);
    glVertex3f(0.250468f, -0.208556f, -0.779856f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.372993f, 0.013195f, 0.927740f);
    glVertex3f(0.250468f, -0.208556f, -0.779856f);
    glNormal3f(0.283410f, 0.238432f, 0.928886f);
    glVertex3f(0.461922f, -0.197001f, -0.837322f);
    glNormal3f(0.338905f, -0.268519f, 0.901688f);
    glVertex3f(0.387697f, -0.255172f, -0.815163f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.134276f, 0.970800f, 0.198791f);
    glVertex3f(-0.568352f, -0.065048f, -0.863117f);
    glNormal3f(-0.095055f, 0.878142f, 0.468861f);
    glVertex3f(-0.594790f, -0.086759f, -0.774949f);
    glNormal3f(-0.193733f, 0.839195f, 0.508152f);
    glVertex3f(-0.822950f, -0.109174f, -0.863156f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.122589f, 0.538020f, 0.833970f);
    glVertex3f(-0.714096f, -0.165166f, -0.766469f);
    glNormal3f(-0.047353f, 0.840354f, 0.539966f);
    glVertex3f(-0.902275f, -0.170380f, -0.774857f);
    glNormal3f(-0.193733f, 0.839195f, 0.508152f);
    glVertex3f(-0.822950f, -0.109174f, -0.863156f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.193733f, 0.839195f, 0.508152f);
    glVertex3f(-0.822950f, -0.109174f, -0.863156f);
    glNormal3f(-0.069782f, 0.766784f, 0.638101f);
    glVertex3f(-0.594790f, -0.086759f, -0.774949f);
    glNormal3f(-0.122589f, 0.538020f, 0.833970f);
    glVertex3f(-0.714096f, -0.165166f, -0.766469f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.056457f, -0.392617f, 0.917967f);
    glVertex3f(-0.714096f, -0.165166f, -0.766469f);
    glNormal3f(0.057814f, -0.765680f, 0.640619f);
    glVertex3f(-0.636701f, -0.218657f, -0.809379f);
    glNormal3f(-0.046914f, -0.738812f, 0.672277f);
    glVertex3f(-0.902275f, -0.170380f, -0.774857f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.057814f, -0.765680f, 0.640619f);
    glVertex3f(-0.636701f, -0.218657f, -0.809379f);
    glNormal3f(0.123033f, -0.945887f, 0.300266f);
    glVertex3f(-0.599245f, -0.230560f, -0.863171f);
    glNormal3f(-0.024804f, -0.913580f, 0.405903f);
    glVertex3f(-0.832987f, -0.237200f, -0.863109f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.046914f, -0.738812f, 0.672277f);
    glVertex3f(-0.902275f, -0.170380f, -0.774857f);
    glNormal3f(0.057814f, -0.765680f, 0.640619f);
    glVertex3f(-0.636701f, -0.218657f, -0.809379f);
    glNormal3f(-0.024804f, -0.913580f, 0.405903f);
    glVertex3f(-0.832987f, -0.237200f, -0.863109f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.414459f, -0.870247f, -0.266259f);
    glVertex3f(0.267471f, -1.292418f, -0.800704f);
    glNormal3f(0.422321f, -0.856335f, -0.297213f);
    glVertex3f(0.297165f, -1.256077f, -0.863217f);
    glNormal3f(0.292994f, -0.944622f, -0.147797f);
    glVertex3f(0.115541f, -1.345649f, -0.863217f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.042204f, -0.994093f, 0.099993f);
    glVertex3f(0.207379f, -1.332402f, -0.754288f);
    glNormal3f(0.292994f, -0.944622f, -0.147797f);
    glVertex3f(0.115541f, -1.345649f, -0.863217f);
    glNormal3f(-0.116452f, -0.944539f, 0.307057f);
    glVertex3f(0.102043f, -1.345914f, -0.863217f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.042204f, -0.994093f, 0.099993f);
    glVertex3f(0.207379f, -1.332402f, -0.754288f);
    glNormal3f(0.414459f, -0.870247f, -0.266259f);
    glVertex3f(0.267471f, -1.292418f, -0.800704f);
    glNormal3f(0.292994f, -0.944622f, -0.147797f);
    glVertex3f(0.115541f, -1.345649f, -0.863217f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.782164f, 0.158482f, 0.602580f);
    glVertex3f(0.267471f, -1.292418f, -0.800704f);
    glNormal3f(0.790813f, 0.068424f, 0.608221f);
    glVertex3f(0.247173f, -1.082303f, -0.823754f);
    glNormal3f(0.907867f, 0.189967f, 0.373751f);
    glVertex3f(0.263320f, -1.149589f, -0.863217f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.651825f, -0.003520f, 0.758361f);
    glVertex3f(0.019465f, -1.066603f, -0.805803f);
    glNormal3f(-0.969516f, 0.036300f, 0.242323f);
    glVertex3f(0.005287f, -1.062005f, -0.863217f);
    glNormal3f(-0.899995f, 0.023074f, 0.435289f);
    glVertex3f(0.016924f, -0.950412f, -0.833375f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.929786f, -0.054549f, 0.364035f);
    glVertex3f(0.010050f, -0.745063f, -0.831362f);
    glNormal3f(-0.899995f, 0.023074f, 0.435289f);
    glVertex3f(0.016924f, -0.950412f, -0.833375f);
    glNormal3f(-0.997680f, -0.009651f, 0.067394f);
    glVertex3f(0.009734f, -0.934851f, -0.863217f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.044571f, -0.958659f, 0.281044f);
    glVertex3f(0.094254f, -1.345473f, -0.863217f);
    glNormal3f(-0.086408f, -0.782099f, 0.617135f);
    glVertex3f(0.120825f, -1.294533f, -0.740031f);
    glNormal3f(-0.116452f, -0.944539f, 0.307057f);
    glVertex3f(0.102043f, -1.345914f, -0.863217f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.001976f, -0.984700f, 0.174244f);
    glVertex3f(0.031551f, -1.326731f, -0.754941f);
    glNormal3f(-0.029811f, -0.923425f, 0.382620f);
    glVertex3f(0.120825f, -1.294533f, -0.740031f);
    glNormal3f(0.044571f, -0.958659f, 0.281044f);
    glVertex3f(0.094254f, -1.345473f, -0.863217f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.813622f, -0.375971f, 0.443469f);
    glVertex3f(-0.034216f, -0.341212f, -0.795286f);
    glNormal3f(-0.899765f, -0.217097f, 0.378538f);
    glVertex3f(-0.031199f, -0.430955f, -0.863217f);
    glNormal3f(-0.835086f, -0.509717f, 0.206933f);
    glVertex3f(-0.064120f, -0.290679f, -0.828945f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.005559f, 0.866332f, 0.499438f);
    glVertex3f(0.261148f, -0.016348f, -0.844790f);
    glNormal3f(-0.066285f, 0.664089f, 0.744710f);
    glVertex3f(-0.166645f, -0.040188f, -0.837342f);
    glNormal3f(-0.048642f, 0.755790f, 0.653005f);
    glVertex3f(-0.138077f, -0.026121f, -0.863217f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.612993f, -0.711701f, 0.343105f);
    glVertex3f(-0.097175f, -0.225718f, -0.725458f);
    glNormal3f(-0.614338f, -0.756525f, 0.224183f);
    glVertex3f(-0.116689f, -0.250694f, -0.863217f);
    glNormal3f(-0.431620f, -0.752985f, 0.496708f);
    glVertex3f(-0.190139f, -0.193962f, -0.837819f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.353161f, 0.855742f, -0.378130f);
    glVertex3f(0.365111f, -0.138507f, -0.854915f);
    glNormal3f(0.353161f, 0.855742f, -0.378130f);
    glVertex3f(0.409942f, -0.160677f, -0.863217f);
    glNormal3f(0.353161f, 0.855742f, -0.378130f);
    glVertex3f(0.469989f, -0.179640f, -0.850050f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.451746f, -0.576724f, 0.680672f);
    glVertex3f(0.345968f, -0.335014f, -0.848499f);
    glNormal3f(0.461861f, -0.492611f, 0.737576f);
    glVertex3f(0.460735f, -0.251681f, -0.851292f);
    glNormal3f(0.527623f, -0.733792f, 0.427976f);
    glVertex3f(0.454444f, -0.265600f, -0.863217f);
    glEnd();
 
}
 
void drawchicken(void)
{
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLES);
    glNormal3f(0.020671f, 0.979842f, -0.198702f);
    glVertex3f(-0.562243f, -1.703523f, -1.483621f);
    glNormal3f(-0.030546f, 0.996522f, -0.077531f);
    glVertex3f(0.117264f, -1.808532f, -1.483621f);
    glNormal3f(0.254672f, 0.916706f, 0.307883f);
    glVertex3f(0.121416f, -1.763513f, -0.906619f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.150284f, -0.253136f, -0.955687f);
    glVertex3f(-2.183403f, -6.265966f, -1.483621f);
    glNormal3f(-0.219515f, -0.145643f, -0.964677f);
    glVertex3f(-2.449321f, -6.199059f, -1.459527f);
    glNormal3f(-0.154250f, -0.270885f, -0.950173f);
    glVertex3f(-1.895099f, -6.514649f, -1.459527f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.002496f, -0.185391f, -0.982662f);
    glVertex3f(-1.969206f, -6.387937f, -1.483621f);
    glNormal3f(-0.150284f, -0.253136f, -0.955687f);
    glVertex3f(-2.183403f, -6.265966f, -1.483621f);
    glNormal3f(-0.154250f, -0.270885f, -0.950173f);
    glVertex3f(-1.895099f, -6.514649f, -1.459527f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.324784f, -0.147143f, -0.934272f);
    glVertex3f(-2.439833f, -5.803646f, -1.480953f);
    glNormal3f(-0.241292f, -0.074992f, -0.967551f);
    glVertex3f(-2.552290f, -5.843759f, -1.449799f);
    glNormal3f(-0.241292f, -0.074992f, -0.967551f);
    glVertex3f(-2.454767f, -6.032035f, -1.459527f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.734809f, 0.624909f, 0.263714f);
    glVertex3f(-1.918716f, -6.215930f, -1.483621f);
    glNormal3f(0.734810f, 0.624909f, 0.263710f);
    glVertex3f(-1.807655f, -6.346523f, -1.483621f);
    glNormal3f(0.734809f, 0.624909f, 0.263714f);
    glVertex3f(-1.798483f, -6.361631f, -1.473377f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.734808f, 0.624908f, 0.263717f);
    glVertex3f(-1.915291f, -6.250783f, -1.410576f);
    glNormal3f(0.734809f, 0.624909f, 0.263714f);
    glVertex3f(-1.918716f, -6.215930f, -1.483621f);
    glNormal3f(0.734809f, 0.624909f, 0.263714f);
    glVertex3f(-1.798483f, -6.361631f, -1.473377f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.246291f, -0.951458f, 0.184576f);
    glVertex3f(-1.430155f, -6.179546f, -1.483621f);
    glNormal3f(-0.027457f, -0.999523f, 0.014120f);
    glVertex3f(-1.690319f, -6.243786f, -1.483621f);
    glNormal3f(-0.077139f, -0.887144f, 0.455000f);
    glVertex3f(-1.795489f, -6.238288f, -1.298942f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.794601f, -0.587710f, 0.152335f);
    glVertex3f(-0.540273f, -4.276410f, -1.483621f);
    glNormal3f(0.888797f, -0.386732f, 0.245925f);
    glVertex3f(-0.548764f, -4.287696f, -1.474137f);
    glNormal3f(0.386036f, -0.734678f, 0.557875f);
    glVertex3f(0.128832f, -3.497013f, -0.839684f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.479138f, -0.831240f, 0.281898f);
    glVertex3f(-0.064916f, -3.827070f, -1.483621f);
    glNormal3f(0.794601f, -0.587710f, 0.152335f);
    glVertex3f(-0.540273f, -4.276410f, -1.483621f);
    glNormal3f(0.386036f, -0.734678f, 0.557875f);
    glVertex3f(0.128832f, -3.497013f, -0.839684f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.219605f, -0.123238f, 0.967774f);
    glVertex3f(-1.512525f, -5.383174f, -1.094263f);
    glNormal3f(0.406495f, -0.260941f, 0.875598f);
    glVertex3f(-0.995160f, -4.966409f, -1.077400f);
    glNormal3f(0.072847f, -0.231322f, 0.970146f);
    glVertex3f(-1.467060f, -6.143144f, -1.214818f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.032320f, -0.834832f, 0.549555f);
    glVertex3f(-1.795489f, -6.238288f, -1.298942f);
    glNormal3f(-0.177453f, -0.158008f, 0.971362f);
    glVertex3f(-1.916278f, -5.938331f, -1.215049f);
    glNormal3f(0.121964f, -0.427808f, 0.895603f);
    glVertex3f(-1.467060f, -6.143144f, -1.214818f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.072847f, -0.231322f, 0.970146f);
    glVertex3f(-1.467060f, -6.143144f, -1.214818f);
    glNormal3f(-0.177453f, -0.158008f, 0.971362f);
    glVertex3f(-1.916278f, -5.938331f, -1.215049f);
    glNormal3f(-0.219605f, -0.123238f, 0.967774f);
    glVertex3f(-1.512525f, -5.383174f, -1.094263f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.219605f, -0.123238f, 0.967774f);
    glVertex3f(-1.512525f, -5.383174f, -1.094263f);
    glNormal3f(-0.714142f, 0.036544f, 0.699047f);
    glVertex3f(-1.866830f, -5.080328f, -1.260121f);
    glNormal3f(-0.552723f, -0.154152f, 0.818984f);
    glVertex3f(-1.668087f, -4.425849f, -0.976315f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.552723f, -0.154152f, 0.818984f);
    glVertex3f(-1.668087f, -4.425849f, -0.976315f);
    glNormal3f(-0.307267f, -0.184475f, 0.933572f);
    glVertex3f(-1.377011f, -3.449316f, -0.632700f);
    glNormal3f(-0.219605f, -0.123238f, 0.967774f);
    glVertex3f(-1.512525f, -5.383174f, -1.094263f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.687600f, -0.107402f, 0.718102f);
    glVertex3f(-2.037294f, -3.547497f, -1.126574f);
    glNormal3f(-0.307267f, -0.184475f, 0.933572f);
    glVertex3f(-1.377011f, -3.449316f, -0.632700f);
    glNormal3f(-0.552723f, -0.154152f, 0.818984f);
    glVertex3f(-1.668087f, -4.425849f, -0.976315f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.406495f, -0.260941f, 0.875598f);
    glVertex3f(-0.995160f, -4.966409f, -1.077400f);
    glNormal3f(0.344180f, -0.401103f, 0.848915f);
    glVertex3f(-0.952670f, -3.810249f, -0.695572f);
    glNormal3f(0.801345f, -0.175494f, 0.571881f);
    glVertex3f(-0.745468f, -4.393013f, -1.123988f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.307267f, -0.184475f, 0.933572f);
    glVertex3f(-1.377011f, -3.449316f, -0.632700f);
    glNormal3f(0.344180f, -0.401103f, 0.848915f);
    glVertex3f(-0.952670f, -3.810249f, -0.695572f);
    glNormal3f(0.406495f, -0.260941f, 0.875598f);
    glVertex3f(-0.995160f, -4.966409f, -1.077400f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.219605f, -0.123238f, 0.967774f);
    glVertex3f(-1.512525f, -5.383174f, -1.094263f);
    glNormal3f(-0.307267f, -0.184475f, 0.933572f);
    glVertex3f(-1.377011f, -3.449316f, -0.632700f);
    glNormal3f(0.406495f, -0.260941f, 0.875598f);
    glVertex3f(-0.995160f, -4.966409f, -1.077400f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.307267f, -0.184475f, 0.933572f);
    glVertex3f(-1.377011f, -3.449316f, -0.632700f);
    glNormal3f(-0.562626f, 0.291095f, 0.773767f);
    glVertex3f(-1.446066f, -2.736554f, -0.649509f);
    glNormal3f(-0.021998f, -0.206025f, 0.978299f);
    glVertex3f(-0.803455f, -3.211341f, -0.438358f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.307267f, -0.184475f, 0.933572f);
    glVertex3f(-1.377011f, -3.449316f, -0.632700f);
    glNormal3f(-0.687600f, -0.107402f, 0.718102f);
    glVertex3f(-2.037294f, -3.547497f, -1.126574f);
    glNormal3f(-0.562626f, 0.291095f, 0.773767f);
    glVertex3f(-1.446066f, -2.736554f, -0.649509f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.307267f, -0.184475f, 0.933572f);
    glVertex3f(-1.377011f, -3.449316f, -0.632700f);
    glNormal3f(-0.021998f, -0.206025f, 0.978299f);
    glVertex3f(-0.803455f, -3.211341f, -0.438358f);
    glNormal3f(0.204659f, -0.450714f, 0.868891f);
    glVertex3f(-0.952670f, -3.810249f, -0.695572f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.562626f, 0.291095f, 0.773767f);
    glVertex3f(-1.446066f, -2.736554f, -0.649509f);
    glNormal3f(-0.279509f, 0.764040f, 0.581479f);
    glVertex3f(-0.903243f, -1.652638f, -1.230848f);
    glNormal3f(0.177295f, 0.196851f, 0.964270f);
    glVertex3f(0.597657f, -2.637386f, -0.495528f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.177295f, 0.196851f, 0.964270f);
    glVertex3f(0.597657f, -2.637386f, -0.495528f);
    glNormal3f(-0.021998f, -0.206025f, 0.978299f);
    glVertex3f(-0.803455f, -3.211341f, -0.438358f);
    glNormal3f(-0.562626f, 0.291095f, 0.773767f);
    glVertex3f(-1.446066f, -2.736554f, -0.649509f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.021998f, -0.206025f, 0.978299f);
    glVertex3f(-0.803455f, -3.211341f, -0.438358f);
    glNormal3f(0.386036f, -0.734678f, 0.557875f);
    glVertex3f(0.128832f, -3.497013f, -0.839684f);
    glNormal3f(0.344180f, -0.401103f, 0.848915f);
    glVertex3f(-0.952670f, -3.810249f, -0.695572f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.519867f, -0.166493f, 0.837866f);
    glVertex3f(2.161793f, -3.476651f, -1.343896f);
    glNormal3f(0.386036f, -0.734678f, 0.557875f);
    glVertex3f(0.128832f, -3.497013f, -0.839684f);
    glNormal3f(0.177295f, 0.196851f, 0.964270f);
    glVertex3f(0.597657f, -2.637386f, -0.495528f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.550452f, 0.529892f, 0.645148f);
    glVertex3f(0.946989f, -2.208163f, -1.089458f);
    glNormal3f(0.549389f, 0.172110f, 0.817649f);
    glVertex3f(2.161793f, -3.476651f, -1.343896f);
    glNormal3f(0.177295f, 0.196851f, 0.964270f);
    glVertex3f(0.597657f, -2.637386f, -0.495528f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.550452f, 0.529892f, 0.645148f);
    glVertex3f(0.946989f, -2.208163f, -1.089458f);
    glNormal3f(0.177295f, 0.196851f, 0.964270f);
    glVertex3f(0.597657f, -2.637386f, -0.495528f);
    glNormal3f(0.186848f, 0.880657f, 0.435351f);
    glVertex3f(0.121416f, -1.763513f, -0.906619f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.406495f, -0.260941f, 0.875598f);
    glVertex3f(-0.995160f, -4.966409f, -1.077400f);
    glNormal3f(0.585883f, -0.698927f, 0.410173f);
    glVertex3f(-1.098989f, -6.067812f, -1.367007f);
    glNormal3f(0.121964f, -0.427808f, 0.895603f);
    glVertex3f(-1.467060f, -6.143144f, -1.214818f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.419327f, 0.060275f, 0.905832f);
    glVertex3f(-1.924889f, -5.842941f, -1.219211f);
    glNormal3f(-0.714142f, 0.036544f, 0.699047f);
    glVertex3f(-1.866830f, -5.080328f, -1.260121f);
    glNormal3f(-0.219605f, -0.123238f, 0.967774f);
    glVertex3f(-1.512525f, -5.383174f, -1.094263f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.394568f, -0.085893f, 0.914844f);
    glVertex3f(-1.950699f, -5.894910f, -1.220977f);
    glNormal3f(-0.327911f, -0.314425f, 0.890848f);
    glVertex3f(-2.205431f, -6.075234f, -1.392408f);
    glNormal3f(-0.484879f, -0.136328f, 0.863890f);
    glVertex3f(-2.348411f, -5.693839f, -1.412472f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.799289f, 0.058336f, 0.598109f);
    glVertex3f(-2.037294f, -3.547497f, -1.126574f);
    glNormal3f(-0.714142f, 0.036544f, 0.699047f);
    glVertex3f(-1.866830f, -5.080328f, -1.260121f);
    glNormal3f(-0.973279f, 0.092730f, 0.210068f);
    glVertex3f(-2.162100f, -3.814569f, -1.452824f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.552723f, -0.154152f, 0.818984f);
    glVertex3f(-1.668087f, -4.425849f, -0.976315f);
    glNormal3f(-0.714142f, 0.036544f, 0.699047f);
    glVertex3f(-1.866830f, -5.080328f, -1.260121f);
    glNormal3f(-0.687600f, -0.107402f, 0.718102f);
    glVertex3f(-2.037294f, -3.547497f, -1.126574f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.942568f, 0.318825f, 0.099583f);
    glVertex3f(-2.037294f, -3.547497f, -1.126574f);
    glNormal3f(-0.989142f, 0.145587f, 0.020037f);
    glVertex3f(-2.162100f, -3.814569f, -1.452824f);
    glNormal3f(-0.776068f, 0.422009f, 0.468643f);
    glVertex3f(-1.446066f, -2.736554f, -0.649509f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.550452f, 0.529892f, 0.645148f);
    glVertex3f(0.946989f, -2.208163f, -1.089458f);
    glNormal3f(0.607688f, 0.512978f, 0.606275f);
    glVertex3f(1.145313f, -2.181149f, -1.311101f);
    glNormal3f(0.549389f, 0.172110f, 0.817649f);
    glVertex3f(2.161793f, -3.476651f, -1.343896f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.344180f, -0.401103f, 0.848915f);
    glVertex3f(-0.952670f, -3.810249f, -0.695572f);
    glNormal3f(0.386036f, -0.734678f, 0.557875f);
    glVertex3f(0.128832f, -3.497013f, -0.839684f);
    glNormal3f(0.888797f, -0.386732f, 0.245925f);
    glVertex3f(-0.548764f, -4.287696f, -1.474137f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.801345f, -0.175494f, 0.571881f);
    glVertex3f(-0.745468f, -4.393013f, -1.123988f);
    glNormal3f(0.446028f, -0.397102f, 0.802103f);
    glVertex3f(-0.952670f, -3.810249f, -0.695572f);
    glNormal3f(0.888797f, -0.386732f, 0.245925f);
    glVertex3f(-0.548764f, -4.287696f, -1.474137f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.888797f, -0.386732f, 0.245925f);
    glVertex3f(-0.548764f, -4.287696f, -1.474137f);
    glNormal3f(0.881454f, -0.245186f, 0.403636f);
    glVertex3f(-0.704663f, -4.919529f, -1.375258f);
    glNormal3f(0.801345f, -0.175494f, 0.571881f);
    glVertex3f(-0.745468f, -4.393013f, -1.123988f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.801345f, -0.175494f, 0.571881f);
    glVertex3f(-0.745468f, -4.393013f, -1.123988f);
    glNormal3f(0.881454f, -0.245186f, 0.403636f);
    glVertex3f(-0.704663f, -4.919529f, -1.375258f);
    glNormal3f(0.406495f, -0.260941f, 0.875598f);
    glVertex3f(-0.995160f, -4.966409f, -1.077400f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.415059f, -0.740667f, 0.528336f);
    glVertex3f(-1.915291f, -6.250784f, -1.410576f);
    glNormal3f(-0.327911f, -0.314425f, 0.890848f);
    glVertex3f(-2.205431f, -6.075234f, -1.392408f);
    glNormal3f(-0.077139f, -0.887144f, 0.455000f);
    glVertex3f(-1.795489f, -6.238288f, -1.298942f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.286509f, -0.196852f, 0.937636f);
    glVertex3f(-2.552290f, -5.843760f, -1.449799f);
    glNormal3f(-0.286509f, -0.196852f, 0.937636f);
    glVertex3f(-2.205431f, -6.075235f, -1.392408f);
    glNormal3f(-0.286509f, -0.196852f, 0.937636f);
    glVertex3f(-2.454767f, -6.032036f, -1.459527f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.157687f, -0.098167f, 0.982598f);
    glVertex3f(-2.205431f, -6.075233f, -1.392408f);
    glNormal3f(-0.051061f, -0.185941f, 0.981233f);
    glVertex3f(-1.915291f, -6.250783f, -1.410576f);
    glNormal3f(-0.051061f, -0.185941f, 0.981233f);
    glVertex3f(-1.895099f, -6.514648f, -1.459527f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.202240f, -0.127957f, 0.970941f);
    glVertex3f(-2.449321f, -6.199059f, -1.459527f);
    glNormal3f(-0.261304f, -0.008520f, 0.965219f);
    glVertex3f(-2.454767f, -6.032034f, -1.459527f);
    glNormal3f(-0.157687f, -0.098167f, 0.982598f);
    glVertex3f(-2.205431f, -6.075233f, -1.392408f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.744244f, 0.660742f, -0.097571f);
    glVertex3f(-2.118082f, -5.561371f, -1.483621f);
    glNormal3f(-0.892968f, 0.279306f, 0.352982f);
    glVertex3f(-2.070618f, -5.314438f, -1.483621f);
    glNormal3f(-0.770132f, 0.391112f, 0.503912f);
    glVertex3f(-2.085863f, -5.508141f, -1.368911f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.892968f, 0.279306f, 0.352982f);
    glVertex3f(-2.070618f, -5.314438f, -1.483621f);
    glNormal3f(-0.789420f, 0.063614f, 0.610548f);
    glVertex3f(-2.055329f, -5.274394f, -1.483621f);
    glNormal3f(-0.714142f, 0.036544f, 0.699047f);
    glVertex3f(-1.866830f, -5.080328f, -1.260121f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.770132f, 0.391112f, 0.503912f);
    glVertex3f(-2.085863f, -5.508141f, -1.368911f);
    glNormal3f(-0.892968f, 0.279306f, 0.352982f);
    glVertex3f(-2.070618f, -5.314438f, -1.483621f);
    glNormal3f(-0.714142f, 0.036544f, 0.699047f);
    glVertex3f(-1.866830f, -5.080328f, -1.260121f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.789420f, 0.063614f, 0.610548f);
    glVertex3f(-2.055329f, -5.274394f, -1.483621f);
    glNormal3f(-0.938718f, -0.070249f, 0.337453f);
    glVertex3f(-2.100077f, -4.791301f, -1.483621f);
    glNormal3f(-0.961209f, -0.003665f, 0.275796f);
    glVertex3f(-2.162100f, -3.814569f, -1.452824f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.714142f, 0.036544f, 0.699047f);
    glVertex3f(-1.866830f, -5.080328f, -1.260121f);
    glNormal3f(-0.789420f, 0.063614f, 0.610548f);
    glVertex3f(-2.055329f, -5.274394f, -1.483621f);
    glNormal3f(-0.961209f, -0.003665f, 0.275796f);
    glVertex3f(-2.162100f, -3.814569f, -1.452824f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.952661f, 0.120974f, 0.278931f);
    glVertex3f(-2.141615f, -3.582242f, -1.483621f);
    glNormal3f(-0.790830f, 0.268724f, 0.549887f);
    glVertex3f(-1.958817f, -2.538699f, -1.483621f);
    glNormal3f(-0.614989f, 0.354099f, 0.704558f);
    glVertex3f(-1.446066f, -2.736554f, -0.649509f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.973279f, 0.092730f, 0.210068f);
    glVertex3f(-2.162100f, -3.814569f, -1.452824f);
    glNormal3f(-0.952661f, 0.120974f, 0.278931f);
    glVertex3f(-2.141615f, -3.582242f, -1.483621f);
    glNormal3f(-0.614989f, 0.354099f, 0.704558f);
    glVertex3f(-1.446066f, -2.736554f, -0.649509f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.762824f, 0.563225f, 0.317610f);
    glVertex3f(-1.828816f, -2.290380f, -1.483621f);
    glNormal3f(-0.614989f, 0.354099f, 0.704558f);
    glVertex3f(-1.446066f, -2.736554f, -0.649509f);
    glNormal3f(-0.790830f, 0.268724f, 0.549887f);
    glVertex3f(-1.958817f, -2.538699f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.614989f, 0.354099f, 0.704558f);
    glVertex3f(-1.446066f, -2.736554f, -0.649509f);
    glNormal3f(-0.762824f, 0.563225f, 0.317610f);
    glVertex3f(-1.828816f, -2.290380f, -1.483621f);
    glNormal3f(-0.634811f, 0.717199f, 0.287474f);
    glVertex3f(-1.594233f, -2.059410f, -1.329791f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.634811f, 0.717199f, 0.287474f);
    glVertex3f(-1.594233f, -2.059410f, -1.329791f);
    glNormal3f(-0.459048f, 0.859863f, -0.223407f);
    glVertex3f(-1.322273f, -1.890212f, -1.483621f);
    glNormal3f(-0.292564f, 0.859180f, 0.419781f);
    glVertex3f(-0.903243f, -1.652638f, -1.230848f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.177453f, -0.158008f, 0.971362f);
    glVertex3f(-1.916278f, -5.938331f, -1.215049f);
    glNormal3f(-0.419327f, 0.060275f, 0.905832f);
    glVertex3f(-1.924889f, -5.842941f, -1.219211f);
    glNormal3f(-0.219605f, -0.123238f, 0.967774f);
    glVertex3f(-1.512525f, -5.383174f, -1.094263f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.077139f, -0.887144f, 0.455000f);
    glVertex3f(-1.795489f, -6.238288f, -1.298942f);
    glNormal3f(0.203812f, -0.613455f, 0.762976f);
    glVertex3f(-1.467060f, -6.143144f, -1.214818f);
    glNormal3f(0.585883f, -0.698927f, 0.410173f);
    glVertex3f(-1.098989f, -6.067812f, -1.367007f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.394568f, -0.085893f, 0.914844f);
    glVertex3f(-1.950699f, -5.894910f, -1.220977f);
    glNormal3f(-0.186613f, -0.099513f, 0.977381f);
    glVertex3f(-2.348411f, -5.693838f, -1.412472f);
    glNormal3f(-0.735532f, 0.226691f, 0.638439f);
    glVertex3f(-2.085863f, -5.508141f, -1.368911f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.327911f, -0.314425f, 0.890848f);
    glVertex3f(-2.205431f, -6.075234f, -1.392408f);
    glNormal3f(-0.394568f, -0.085893f, 0.914844f);
    glVertex3f(-1.950699f, -5.894910f, -1.220977f);
    glNormal3f(-0.032320f, -0.834832f, 0.549555f);
    glVertex3f(-1.795489f, -6.238288f, -1.298942f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.171262f, -0.012378f, 0.985148f);
    glVertex3f(-2.552290f, -5.843759f, -1.449799f);
    glNormal3f(-0.186613f, -0.099513f, 0.977381f);
    glVertex3f(-2.348411f, -5.693838f, -1.412472f);
    glNormal3f(-0.327911f, -0.314425f, 0.890848f);
    glVertex3f(-2.205431f, -6.075234f, -1.392408f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.419327f, 0.060275f, 0.905832f);
    glVertex3f(-1.924889f, -5.842941f, -1.219211f);
    glNormal3f(-0.735532f, 0.226691f, 0.638439f);
    glVertex3f(-2.085863f, -5.508141f, -1.368911f);
    glNormal3f(-0.714142f, 0.036544f, 0.699047f);
    glVertex3f(-1.866830f, -5.080328f, -1.260121f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.202240f, -0.127957f, 0.970941f);
    glVertex3f(-2.449321f, -6.199059f, -1.459527f);
    glNormal3f(-0.327911f, -0.314425f, 0.890848f);
    glVertex3f(-2.205431f, -6.075234f, -1.392408f);
    glNormal3f(-0.139578f, -0.245119f, 0.959393f);
    glVertex3f(-1.895099f, -6.514649f, -1.459527f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.035461f, -0.507416f, 0.860972f);
    glVertex3f(-2.587419f, -5.730149f, -1.443716f);
    glNormal3f(-0.186613f, -0.099513f, 0.977381f);
    glVertex3f(-2.348411f, -5.693838f, -1.412472f);
    glNormal3f(-0.035461f, -0.507416f, 0.860972f);
    glVertex3f(-2.439833f, -5.803646f, -1.480953f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.281479f, 0.604955f, 0.744848f);
    glVertex3f(0.121416f, -1.763513f, -0.906619f);
    glNormal3f(0.177295f, 0.196851f, 0.964270f);
    glVertex3f(0.597657f, -2.637386f, -0.495528f);
    glNormal3f(-0.361705f, 0.622414f, 0.694097f);
    glVertex3f(-0.903243f, -1.652638f, -1.230848f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.386036f, -0.734678f, 0.557875f);
    glVertex3f(0.128832f, -3.497013f, -0.839684f);
    glNormal3f(-0.021998f, -0.206025f, 0.978299f);
    glVertex3f(-0.803455f, -3.211341f, -0.438358f);
    glNormal3f(0.177295f, 0.196851f, 0.964270f);
    glVertex3f(0.597657f, -2.637386f, -0.495528f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.279509f, 0.764040f, 0.581479f);
    glVertex3f(-0.903243f, -1.652638f, -1.230848f);
    glNormal3f(-0.614989f, 0.354099f, 0.704558f);
    glVertex3f(-1.446066f, -2.736554f, -0.649509f);
    glNormal3f(-0.634811f, 0.717199f, 0.287474f);
    glVertex3f(-1.594233f, -2.059410f, -1.329791f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.482135f, 0.648859f, 0.588666f);
    glVertex3f(0.953096f, -1.789080f, -1.483621f);
    glNormal3f(0.550452f, 0.529892f, 0.645148f);
    glVertex3f(0.946989f, -2.208163f, -1.089458f);
    glNormal3f(0.186848f, 0.880657f, 0.435351f);
    glVertex3f(0.121416f, -1.763513f, -0.906619f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.607688f, 0.512978f, 0.606275f);
    glVertex3f(1.145313f, -2.181149f, -1.311101f);
    glNormal3f(0.550452f, 0.529892f, 0.645148f);
    glVertex3f(0.946989f, -2.208163f, -1.089458f);
    glNormal3f(0.482135f, 0.648859f, 0.588666f);
    glVertex3f(0.953096f, -1.789080f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.169679f, -0.920068f, 0.353106f);
    glVertex3f(0.380276f, -3.655559f, -1.373626f);
    glNormal3f(0.386036f, -0.734678f, 0.557875f);
    glVertex3f(0.128832f, -3.497013f, -0.839684f);
    glNormal3f(0.164958f, -0.755018f, 0.634615f);
    glVertex3f(2.161793f, -3.476651f, -1.343896f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.965726f, -0.233071f, -0.114244f);
    glVertex3f(-0.697739f, -4.837726f, -1.483621f);
    glNormal3f(0.937176f, -0.239160f, 0.253976f);
    glVertex3f(-0.819839f, -5.485936f, -1.483621f);
    glNormal3f(0.881454f, -0.245186f, 0.403636f);
    glVertex3f(-0.704663f, -4.919529f, -1.375258f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.858099f, -0.381881f, 0.343268f);
    glVertex3f(-0.903720f, -5.733859f, -1.483621f);
    glNormal3f(0.585883f, -0.698927f, 0.410173f);
    glVertex3f(-1.098989f, -6.067812f, -1.367007f);
    glNormal3f(0.881454f, -0.245186f, 0.403636f);
    glVertex3f(-0.704663f, -4.919529f, -1.375258f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.937176f, -0.239160f, 0.253976f);
    glVertex3f(-0.819839f, -5.485936f, -1.483621f);
    glNormal3f(0.858099f, -0.381881f, 0.343268f);
    glVertex3f(-0.903720f, -5.733859f, -1.483621f);
    glNormal3f(0.881454f, -0.245186f, 0.403636f);
    glVertex3f(-0.704663f, -4.919529f, -1.375258f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.881454f, -0.245186f, 0.403636f);
    glVertex3f(-0.704663f, -4.919529f, -1.375258f);
    glNormal3f(0.585883f, -0.698927f, 0.410173f);
    glVertex3f(-1.098989f, -6.067812f, -1.367007f);
    glNormal3f(0.406495f, -0.260941f, 0.875598f);
    glVertex3f(-0.995160f, -4.966409f, -1.077400f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.973279f, 0.092730f, 0.210068f);
    glVertex3f(-2.162100f, -3.814569f, -1.452824f);
    glNormal3f(-0.958210f, 0.083463f, -0.273619f);
    glVertex3f(-2.149805f, -3.774377f, -1.483621f);
    glNormal3f(-0.952661f, 0.120974f, 0.278931f);
    glVertex3f(-2.141615f, -3.582242f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.973279f, 0.092730f, 0.210068f);
    glVertex3f(-2.162100f, -3.814569f, -1.452824f);
    glNormal3f(-0.989698f, 0.032620f, -0.139404f);
    glVertex3f(-2.158677f, -3.842327f, -1.483621f);
    glNormal3f(-0.958210f, 0.083463f, -0.273619f);
    glVertex3f(-2.149805f, -3.774377f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.585883f, -0.698927f, 0.410173f);
    glVertex3f(-1.098989f, -6.067812f, -1.367007f);
    glNormal3f(0.858099f, -0.381881f, 0.343268f);
    glVertex3f(-0.903720f, -5.733859f, -1.483621f);
    glNormal3f(0.588261f, -0.808284f, 0.025017f);
    glVertex3f(-1.143066f, -6.103500f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.006668f, -0.982124f, 0.188114f);
    glVertex3f(-1.795489f, -6.238288f, -1.298942f);
    glNormal3f(-0.027457f, -0.999523f, 0.014120f);
    glVertex3f(-1.690319f, -6.243786f, -1.483621f);
    glNormal3f(-0.288850f, -0.947625f, -0.136281f);
    glVertex3f(-1.871193f, -6.188653f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.047770f, -0.580271f, -0.813021f);
    glVertex3f(-1.798483f, -6.361632f, -1.473377f);
    glNormal3f(-0.047770f, -0.580271f, -0.813021f);
    glVertex3f(-1.807655f, -6.346524f, -1.483621f);
    glNormal3f(-0.047770f, -0.580271f, -0.813021f);
    glVertex3f(-1.886089f, -6.340067f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.219515f, -0.145643f, -0.964677f);
    glVertex3f(-2.449321f, -6.199059f, -1.459527f);
    glNormal3f(-0.287473f, -0.044944f, -0.956734f);
    glVertex3f(-2.378641f, -6.138251f, -1.483621f);
    glNormal3f(-0.287469f, -0.044944f, -0.956735f);
    glVertex3f(-2.429290f, -5.814285f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.324784f, -0.147143f, -0.934272f);
    glVertex3f(-2.439833f, -5.803646f, -1.480953f);
    glNormal3f(-0.219515f, -0.145643f, -0.964677f);
    glVertex3f(-2.449321f, -6.199059f, -1.459527f);
    glNormal3f(-0.287469f, -0.044944f, -0.956735f);
    glVertex3f(-2.429290f, -5.814285f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.080839f, -0.140359f, -0.986795f);
    glVertex3f(-1.798483f, -6.361631f, -1.473377f);
    glNormal3f(0.080838f, -0.140357f, -0.986795f);
    glVertex3f(-1.886089f, -6.340066f, -1.483621f);
    glNormal3f(0.002496f, -0.185391f, -0.982662f);
    glVertex3f(-1.969206f, -6.387937f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.080839f, -0.140360f, -0.986795f);
    glVertex3f(-1.895099f, -6.514648f, -1.459527f);
    glNormal3f(0.080839f, -0.140359f, -0.986795f);
    glVertex3f(-1.798483f, -6.361631f, -1.473377f);
    glNormal3f(0.002496f, -0.185391f, -0.982662f);
    glVertex3f(-1.969206f, -6.387937f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.973279f, 0.092730f, 0.210068f);
    glVertex3f(-2.162100f, -3.814569f, -1.452824f);
    glNormal3f(-0.938718f, -0.070249f, 0.337453f);
    glVertex3f(-2.100077f, -4.791301f, -1.483621f);
    glNormal3f(-0.989698f, 0.032620f, -0.139404f);
    glVertex3f(-2.158677f, -3.842327f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.634811f, 0.717199f, 0.287474f);
    glVertex3f(-1.594233f, -2.059410f, -1.329791f);
    glNormal3f(-0.762824f, 0.563225f, 0.317610f);
    glVertex3f(-1.828816f, -2.290380f, -1.483621f);
    glNormal3f(-0.459048f, 0.859863f, -0.223407f);
    glVertex3f(-1.322273f, -1.890212f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.888797f, -0.386732f, 0.245925f);
    glVertex3f(-0.548764f, -4.287696f, -1.474137f);
    glNormal3f(0.794601f, -0.587710f, 0.152335f);
    glVertex3f(-0.540273f, -4.276410f, -1.483621f);
    glNormal3f(0.940141f, -0.325100f, 0.102197f);
    glVertex3f(-0.558227f, -4.318043f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.888797f, -0.386732f, 0.245925f);
    glVertex3f(-0.548764f, -4.287696f, -1.474137f);
    glNormal3f(0.940141f, -0.325100f, 0.102197f);
    glVertex3f(-0.558227f, -4.318043f, -1.483621f);
    glNormal3f(0.965726f, -0.233071f, -0.114244f);
    glVertex3f(-0.697739f, -4.837726f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.881454f, -0.245186f, 0.403636f);
    glVertex3f(-0.704663f, -4.919529f, -1.375258f);
    glNormal3f(0.888797f, -0.386732f, 0.245925f);
    glVertex3f(-0.548764f, -4.287696f, -1.474137f);
    glNormal3f(0.965726f, -0.233071f, -0.114244f);
    glVertex3f(-0.697739f, -4.837726f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.324784f, -0.147143f, -0.934272f);
    glVertex3f(-2.439833f, -5.803646f, -1.480953f);
    glNormal3f(-0.433554f, -0.316038f, -0.843890f);
    glVertex3f(-2.429546f, -5.810634f, -1.483621f);
    glNormal3f(-0.433554f, -0.316038f, -0.843890f);
    glVertex3f(-2.433822f, -5.804768f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.219515f, -0.145643f, -0.964677f);
    glVertex3f(-2.449321f, -6.199059f, -1.459527f);
    glNormal3f(-0.150284f, -0.253136f, -0.955687f);
    glVertex3f(-2.183403f, -6.265966f, -1.483621f);
    glNormal3f(-0.142188f, -0.217364f, -0.965679f);
    glVertex3f(-2.378641f, -6.138252f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.386036f, -0.734678f, 0.557875f);
    glVertex3f(0.128832f, -3.497013f, -0.839684f);
    glNormal3f(0.169679f, -0.920068f, 0.353106f);
    glVertex3f(0.380276f, -3.655559f, -1.373626f);
    glNormal3f(0.479138f, -0.831240f, 0.281898f);
    glVertex3f(-0.064916f, -3.827070f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.537192f, 0.812568f, -0.226179f);
    glVertex3f(-2.348411f, -5.693838f, -1.412472f);
    glNormal3f(-0.537192f, 0.812569f, -0.226178f);
    glVertex3f(-2.239653f, -5.641742f, -1.483621f);
    glNormal3f(-0.744244f, 0.660742f, -0.097571f);
    glVertex3f(-2.118082f, -5.561371f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.862434f, 0.485401f, 0.143502f);
    glVertex3f(-2.085863f, -5.508141f, -1.368911f);
    glNormal3f(-0.537192f, 0.812568f, -0.226179f);
    glVertex3f(-2.348411f, -5.693838f, -1.412472f);
    glNormal3f(-0.744244f, 0.660742f, -0.097571f);
    glVertex3f(-2.118082f, -5.561371f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.585883f, -0.698927f, 0.410173f);
    glVertex3f(-1.098989f, -6.067812f, -1.367007f);
    glNormal3f(0.588261f, -0.808284f, 0.025017f);
    glVertex3f(-1.143066f, -6.103500f, -1.483621f);
    glNormal3f(0.246291f, -0.951458f, 0.184576f);
    glVertex3f(-1.430155f, -6.179546f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.077139f, -0.887144f, 0.455000f);
    glVertex3f(-1.795489f, -6.238288f, -1.298942f);
    glNormal3f(0.585883f, -0.698927f, 0.410173f);
    glVertex3f(-1.098989f, -6.067812f, -1.367007f);
    glNormal3f(0.246291f, -0.951458f, 0.184576f);
    glVertex3f(-1.430155f, -6.179546f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.254672f, 0.916706f, 0.307883f);
    glVertex3f(0.121416f, -1.763513f, -0.906619f);
    glNormal3f(-0.030546f, 0.996522f, -0.077531f);
    glVertex3f(0.117264f, -1.808532f, -1.483621f);
    glNormal3f(0.090377f, 0.966750f, 0.239220f);
    glVertex3f(0.721584f, -1.676842f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.186848f, 0.880657f, 0.435351f);
    glVertex3f(0.121416f, -1.763513f, -0.906619f);
    glNormal3f(0.090377f, 0.966750f, 0.239220f);
    glVertex3f(0.721584f, -1.676842f, -1.483621f);
    glNormal3f(0.482135f, 0.648859f, 0.588666f);
    glVertex3f(0.953096f, -1.789080f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.214260f, 0.963185f, -0.162382f);
    glVertex3f(-0.903243f, -1.652638f, -1.230848f);
    glNormal3f(-0.459048f, 0.859863f, -0.223407f);
    glVertex3f(-1.322273f, -1.890212f, -1.483621f);
    glNormal3f(0.020671f, 0.979842f, -0.198702f);
    glVertex3f(-0.562243f, -1.703523f, -1.483621f);
    glEnd();
 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.254672f, 0.916706f, 0.307883f);
    glVertex3f(0.121416f, -1.763513f, -0.906619f);
    glNormal3f(-0.275840f, 0.924635f, 0.262606f);
    glVertex3f(-0.903243f, -1.652638f, -1.230848f);
    glNormal3f(0.020671f, 0.979842f, -0.198702f);
    glVertex3f(-0.562243f, -1.703523f, -1.483621f);
    glEnd();
 
}
void footpos1() {
    glLoadIdentity();
 
    glTranslatef(2.1, -0.45, -24);
    glRotatef(180, 0, 0, 1);
    glScalef(1.4, 1.4, 1.4);
 
    drawfoot();        //bal lab elol
 
    glLoadIdentity();
 
    glTranslatef(-1.8, -0.8, -10.0);
    glRotatef(140, 0, 0, 1);
    glScalef(1.4, 1.4, 1.4);
 
    drawfoot();        //jobb hatul
 
}
 
void footpos2() {
 
    glLoadIdentity();
 
    glTranslatef(1.0, -0.7, -10);
    glRotatef(180, 0, 0, 1);
 
    drawfoot();        //jobb lab elol
 
    glTranslatef(1.9, -0.18, -1.0);
    glRotatef(-40, 0, 0, 1);
 
    drawfoot();        //bal hatul
 
}
 
GLfloat pixels[] = {0.25f, 0.37f, 0.35f,    //elso kocka 
                    0.25, 0.25, 0.1f,    //masodik
                    0.5f, 0.62f, 0.35f,    //...
                    0.37f, 0.5f, 0.1f
};
 
GLuint loadTexture(GLfloat* image)
{
    GLuint textureId;
 
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,2, 2,0,GL_RGB,GL_FLOAT,image);
 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);                //bilinear texture filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);                
 
    return textureId;
}
 
 
 
void Render() {
    g_textureId = loadTexture(pixels);
 
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    gluLookAt(0.0, -20.0, 40.0,            //szempozicio (eye)
        0, 0.0, 1.0,                    //nezeti referencia pont (lookat)
        0.0, -1.0, 0.0);                //felfele irany (updir)
 
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,g_textureId);
 
    //Terep kirajzolo fv.
    float j = 0.0f;
    float startx = 500.0f;
    float startz = 80.0f;
 
    glBegin(GL_QUADS);
    for(;j<1000;j+=4) {
        float i = 0.0f;
        for(;i<500;i+=4) {
 
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(startx-j, 1.0f, startz-i);
 
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(startx-j, 1.0f, startz-i-4.0f);
 
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(startx-j-4.0f, 1.0f, startz-i-4.0f);
 
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(startx-j-4.0f, 1.0f, startz-i);
 
        }
    }
    glEnd();
 
    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1,&g_textureId);
    glDisable(GL_COLOR_MATERIAL);
 
 
    //----------Material defs
    const float ChickenADS[] = {0.9, 0.9, 0.0, 1.0};                    //test, diffuz sarga
    const float ChickenSpecularSurface[] = {0.8, 0.0, 0.0, 1.0};        //csor, lab spekularis piros
    const float ChickenShineSurface[] = { 80.0 };                            //csor, lab csillano tulajdonsag
    const float Zero[] = {0.0, 0.0, 0.0, 0.0};
    const float ZeroShine[] = {0.0};                                
    const float RoadDiffuseSurface[] = {0.3, 0.3, 0.3, 1.0};
 
    //-----------UT: Szurke diffuz teglalap: y=0 sikon van
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RoadDiffuseSurface);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Zero);
    glMaterialfv(GL_FRONT, GL_SHININESS, ZeroShine);
 
    glBegin(GL_QUADS);
 
    glNormal3f(0.1, 0.1, 0.1);
    glVertex3f(50.0f, 0.0f, 20.0f);
    glNormal3f(0.1, 0.1, 0.1);
    glVertex3f(-50.0f, 0.0f, 20.0f);
    glNormal3f(0.1, 0.1, 0.1);
    glVertex3f(-100.0f, 0.0f, -10.0f);
    glNormal3f(0.1, 0.1, 0.1);
    glVertex3f(100.0f, 0.0f, -10.0f);
 
    glEnd();
 
    //-----------Csirke test
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ChickenADS);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Zero);
    glMaterialfv(GL_FRONT, GL_SHININESS, ZeroShine);
 
    glTranslatef(0, 10, 0);
    glScalef(5.0f, 5.0f, 5.0f);
 
    drawchicken();
 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ChickenSpecularSurface);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ChickenSpecularSurface);
    glMaterialfv(GL_FRONT, GL_SHININESS, ChickenShineSurface);
 
    //-----------Csirke csor
 
    glScalef(0.2f, 0.2f, 0.2f);
    glTranslatef(-12, -29.0, -6);
    glRotatef(-90, 0, 1, 0);
 
    GLUquadricObj* chicken_lip = gluNewQuadric();
    gluCylinder(chicken_lip, 0.4, 0.01, 3.3, 40, 40);
 
}
 
void onInitialization( ) { 
 
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    float LightAmbient[] = {0.4, 0.4, 0.4, 1.0};
    float LightDiffuse[] = {0.8, 0.8, 0.8, 1.0};
    float LightSpecular[] = {0.8, 0.8, 0.8, 1.0};
    float LightPosition[] = {0, -120, 300, 0.0};            //4. koord 0 -> iranyfenyforras
    float Shininess[] = { 70.0 };
    float Emission[] = { 70.0 };
 
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_SHININESS, Shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLightfv(GL_LIGHT0, GL_EMISSION, Emission);
    glEnable(GL_LIGHT0);
 
    glViewport(0, 0, w_width, w_height);                        //kepernyo transzf
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 
    float aspect = (w_height == 0) ? 1.0 : w_width / w_height;
    gluPerspective(80, aspect, 1, 800);                            //perspektiv transzf
 
}
 
// Rajzolas, minden frame megjelenitesehez ez a fuggveny hivodik meg
void onDisplay( ) {
    glClearColor(0.05f, 0.58f, 0.74f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    // ...
    Render();
    footpos1();
    // Buffercsere: rajzolas vege
    glFinish();
    glutSwapBuffers();
}
 
// Billentyuzet esemenyeket lekezelo fuggveny
void onKeyboard(unsigned char key, int x, int y) {
    if(key == 32) {
        glClearColor(0.05f, 0.58f, 0.74f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glFinish();
        glutSwapBuffers();
 
        if(isPressed) {
            isPressed = 0;    
            Render();
            footpos1();
            glFinish();
            glutSwapBuffers();
 
        }
        else {
            isPressed = 1;        
            Render();
            footpos2();
            glFinish();
            glutSwapBuffers();
        }
    }
}
 
// Eger esemenyeket lekezelo fuggveny
void onMouse(int button, int state, int x, int y) {
    // A GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON
    // ill. a GLUT_DOWN / GLUT_UP makrokat hasznald.
}
 
// `Idle' esemenykezelo, ha nem tortenik rajzolas vagy esemenykezeles 
// ez a fuggveny hivodik meg amennyiszer lehetseges
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