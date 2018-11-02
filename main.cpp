/* 
 COMPUTER GRAPHICS
 3D Modeling and transformations
 Francisco Igor
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "object3d.h"

#define PROF -10.0
#define ROT1 3.141592653 / 100

// space definition
GLubyte space[] =
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

GLuint fontOffset;

// Letters mapping
GLubyte letters[][13] = {
	{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
	{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
	{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
	{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
	{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
	{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
	{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
	{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
	{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
	{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
	{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
	{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
	{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
	{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
	{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
	{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
	{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
	{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
	{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
	{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
	{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
	{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
	{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
	{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
	{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
	{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}};

/* Event global variables */
int MOUSEX, MOUSEY, MOUSEINIX, MOUSEINIY, MOUSEDX, MOUSEDY;
int SIZEX, SIZEY;
float SPINX, SPINY, SPINZ;
float MOUSEXf, MOUSEYf, MOUSEXf2, MOUSEYf2;
char KEY;
float SCALE1 = 1, SCALE2 = 1;
float COLOR2 = 1, COLOR1 = 1;
int VIEWMODE = 1, TYPE = 1;
float LASTROTX1 = 0, LASTROTY1 = 0;
float LASTROTX2 = 0, LASTROTY2 = 0;

int SELECTED = 0;
int NUMPOINTS = 0;
int NUMSEGMENTS = 0;
int NUMDEPS = 0;

struct coord puntos[200];
Object3D o[100];
int dependency[100][2];

/* init GLUT function */
void init(void);
/* resize window function */
void resize(int w, int h);
/* Mouse Click function */
void click(int button, int state, int posX, int posY);
/* Mouse motion function */
void motion(int x, int y);
/* Keyboard press function */
void keyboard(unsigned char key, int posX, int posY);
/* Prints a string */
void printString(char *s);
/* Inits the raster font */
void makeRasterFont(void);
/* start application */
void start(void);
/* drawing function */
void display(void);

/* Main Program */
int main(int argc, char *argv[])
{

	printf("Computer Graphics\n\nAnimatron Project\n\n");
	printf("Perspective mode\n KEY [p]\n");
	printf("Rotate articulations \n KEYS [8-2  4-6]\n");
	printf("Perspective mode\n KEY [p]\n");
	printf("To rotate each shape drag the mouse around the scenario\n");
	printf("(rotations are in the vertical and horizontal directions)\n");

	/* Calls to init window */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	SIZEX = 500;
	SIZEY = 500;
	glutInitWindowSize(SIZEX, SIZEY);
	glutInitWindowPosition(100, 30);
	glutCreateWindow("Animatron Project");

	/* Call to local init function */
	init();
	start();

	/* Setup event functions */
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(click);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);

	/* Starts the action! */
	glutMainLoop();

	exit(0);
	return 0;
}

/* init GLUT function */
void init(void)
{
	GLfloat params[2] = {0.0, 0.0};
	GLfloat pos[4] = {0.5, 0.5, 20.0, 20.0};
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable (GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, params);
	//glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	MOUSEX = 0;
	MOUSEY = 0;
	MOUSEDX = 0;
	MOUSEDY = 0;
	MOUSEXf = ((float)MOUSEX - (float)(SIZEX / 2)) / (float)(SIZEX / 2);
	MOUSEYf = ((float)MOUSEY - (float)(SIZEY / 2)) / (float)(SIZEY / 2);
	KEY = 0;
	makeRasterFont();
}

void rotar(double x0, double y0, double *x1, double *y1, double ROT)
{
	*x1 = x0 + (*x1 - x0) * cos(ROT) * 1.001 - (*y1 - y0) * sin(ROT);
	*y1 = y0 + (*x1 - x0) * sin(ROT) * 1.001 + (*y1 - y0) * cos(ROT);
}

void rotateObject(int num, int k, double x0, double y0, double z0)
{

	double x1, y1, z1, x2, y2, z2;
	int i;

	x1 = o[num].X1;
	y1 = o[num].Y1;
	z1 = o[num].Z1;
	x2 = o[num].X2;
	y2 = o[num].Y2;
	z2 = o[num].Z2;

	if (k == '8')
	{
		rotar(y0, z0, &y1, &z1, ROT1);
		rotar(y0, z0, &y2, &z2, ROT1);
	}
	if (k == '2')
	{
		rotar(y0, z0, &y1, &z1, -ROT1);
		rotar(y0, z0, &y2, &z2, -ROT1);
	}

	if (k == '6')
	{
		rotar(x0, y0, &x1, &y1, ROT1);
		rotar(x0, y0, &x2, &y2, ROT1);
	}
	if (k == '4')
	{
		rotar(x0, y0, &x1, &y1, -ROT1);
		rotar(x0, y0, &x2, &y2, -ROT1);
	}

	o[num].set(x1, y1, z1, x2, y2, z2);

	for (i = 0; i < NUMDEPS; i++)
	{
		if (dependency[i][0] == num)
			rotateObject(dependency[i][1], k, x0, y0, z0);
	}

	//printf("%f;%f;%f;%f;%f;%f;%f\n" ,o[num].X1,o[num].Y1,o[num].Z1,o[num].X2,o[num].Y2,o[num].Z2,o[num].largo);
}

/* start function */
void start(void)
{
	FILE *pt;
	int px, py, pz, cont = 0, num;
	pt = fopen("puntos.dat", "r");
	if (!pt)
	{
		printf("Failed to open puntos.dat\n");
		exit(0);
	};

	while (!feof(pt))
	{
		num = fscanf(pt, "%d,%d,%d", &px, &py, &pz);
		if (num == 3)
		{
			puntos[cont].x = px;
			puntos[cont].y = py;
			puntos[cont].z = pz;
			cont++;
		}
	}
	fclose(pt);
	NUMPOINTS = cont;

	pt = fopen("segment.dat", "r");
	if (!pt)
	{
		printf("No se pudo abrir el archivo segment.dat\n");
		exit(0);
	};
	cont = 0;
	while (!feof(pt))
	{
		num = fscanf(pt, "%d,%d", &px, &py);
		if (num == 2)
		{
			o[cont].set(puntos[px], puntos[py]);
			o[cont].setColor(0.5, 0.5, 0.5);
			printf("%d-%d (%f,%f - %f,%f)\n", px, py, puntos[px].x, puntos[px].y, puntos[py].x, puntos[py].y);
			cont++;
		}
	}

	NUMSEGMENTS = cont;

	pt = fopen("depend.dat", "r");
	if (!pt)
	{
		printf("No se pudo abrir el archivo depend.dat\n");
		exit(0);
	};
	cont = 0;
	while (!feof(pt))
	{
		num = fscanf(pt, "%d,%d", &dependency[cont][0], &dependency[cont][1]);
		if (num == 2)
			cont++;
	}

	NUMDEPS = cont;
}

/* drawing function */
void display(void)
{
	int i;
	char titulo[100];
	float rotX = 0, rotY = 0;
	float w1 = 0, w2 = 0;

	MOUSEXf = ((float)MOUSEX - (float)(SIZEX / 2)) / (float)(SIZEX / 2);
	MOUSEYf = -((float)MOUSEY - (float)(SIZEY / 2)) / (float)(SIZEY / 2);

	rotX = (float)MOUSEDX / (float)(SIZEX / 2);
	rotY = -(float)MOUSEDY / (float)(SIZEY / 2);

	sprintf(titulo, "Animatron - Points %d / Segments %d", NUMPOINTS, NUMSEGMENTS);

	glutSetWindowTitle(titulo);

	if (KEY == 'x')
		SCALE1 -= 0.2;
	if (KEY == 'm')
		SCALE2 -= 0.2;
	if (SCALE1 < 0.4)
		SCALE1 = 1.4;
	if (SCALE2 < 0.4)
		SCALE2 = 1.4;

	if (KEY == 'z')
		COLOR1 -= 0.2;
	if (KEY == 'n')
		COLOR2 -= 0.2;
	if (COLOR1 < 0.4)
		COLOR1 = 1.0;
	if (COLOR2 < 0.4)
		COLOR2 = 1.0;

	if (KEY == 'p')
		VIEWMODE *= -1;
	if (KEY == 't')
		TYPE *= -1;

	if (KEY == 9)
		SELECTED++;
	if (SELECTED >= NUMSEGMENTS)
		SELECTED = 0;

	// rotaciones
	rotateObject(SELECTED, KEY, o[SELECTED].X1, o[SELECTED].Y1, o[SELECTED].Z1);

	//clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// proyection selection
	if (VIEWMODE == 1)
		glOrtho(-10.0, 11.0, -10.0, 11.0, 5.0, 20.0);
	else
		glFrustum(-1.0, 1.2, -1.0, 1.2, 1.2, 20.0);
	glMatrixMode(GL_MODELVIEW);

	// setting up the camera point of view
	glLoadIdentity();
	//gluLookAt (0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// draw help text
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos3f(-3.9, 3.6, -0.4);
	printString("TEST");

	glPushMatrix();

	// alejar
	glTranslated(0, 0, PROF);

	glRotatef(-rotX * 360, 0.0f, 1.0f, 0.0f);
	glRotatef(-rotY * 360, 1.0f, 0.0f, 0.0f);

	//printf("%1.2f %1.2f\n",rotX,rotY);

	// cabeza
	glColor4f(1, 1, 0, 0.7);
	glPushMatrix();
	glTranslated(o[NUMSEGMENTS - 1].X2, o[NUMSEGMENTS - 1].Y2, o[NUMSEGMENTS - 1].Z2);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();

	// piso
	glColor4f(0, 0, 0.5, 0.4);
	glBegin(GL_QUADS);
	glVertex3f(6, -7 - width * 2, 6);
	glVertex3f(6, -7 - width * 2, -6);
	glVertex3f(-6, -7 - width * 2, -6);
	glVertex3f(-6, -7 - width * 2, 6);
	glEnd();

	// dibujar segmentos
	for (i = 0; i < NUMSEGMENTS; i++)
		if (SELECTED == i)
			o[i].display(1);
		else
			o[i].display(0);

	glPopMatrix();

	KEY = 0;

	glutSwapBuffers();
}

/* resize window function */
void resize(int w, int h)
{
	SIZEX = w;
	SIZEY = h;

	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}

/* Mouse Click function */
void click(int button, int state, int posX, int posY)
{
	if (state == GLUT_DOWN)
	{
		MOUSEX = posX;
		MOUSEY = posY;
		MOUSEINIX = posX;
		MOUSEINIY = posY;
	}

	glutPostRedisplay();
}

/* Mouse motion function */
void motion(int x, int y)
{
	MOUSEDX = x - MOUSEINIX;
	MOUSEDY = MOUSEINIY - y;

	SPINX += (float)(x - MOUSEX) * 0.1f;
	SPINZ += (float)(y - MOUSEY) * 0.1f;
	MOUSEX = x;
	MOUSEY = y;

	glutPostRedisplay();
}

/* Keyboard press function */
void keyboard(unsigned char key, int posX, int posY)
{
	KEY = key;
	glutPostRedisplay();
}

/* Set up the raster font used to display text */
void makeRasterFont(void)
{
	GLuint i, j;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	fontOffset = glGenLists(128);
	for (i = 0, j = 'A'; i < 26; i++, j++)
	{
		glNewList(fontOffset + j, GL_COMPILE);
		glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
		glEndList();
	}
	glNewList(fontOffset + ' ', GL_COMPILE);
	glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
	glEndList();
}

/* Prints the string s on the screen (only Uppercase letters) */
void printString(char *s)
{
	glPushAttrib(GL_LIST_BIT);
	glListBase(fontOffset);
	glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *)s);
	glPopAttrib();
}
