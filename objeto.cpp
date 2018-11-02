#include <stdio.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <windows.h>
#  include <GL/gl.h>
#  include <GL/glu.h>
#endif

#include <math.h>
#include "objeto.h"




Object3D::Object3D(){

 X1=0;
 X2=0;
 Y1=0;
 Y2=0;
 Z1=0;
 Z2=0;
 R=G=B=1.0;
       
};

// calcula el angulo asociado a una coordenada cartesiana
double angulo(double x,double y){
       double ang;
       if (x==0) x=0.00001;       
       ang=atan(y/x);
       if (x<0) ang=M_PI+ang;
       ang=ang*180/M_PI;  
       return ang;
}


void Object3D::set(double x1,double y1,double z1,double x2,double y2,double z2){

 X1=x1;
 X2=x2;
 Y1=y1;
 Y2=y2;
 Z1=z1;
 Z2=z2;
 largo=sqrt((X2-X1)*(X2-X1)+(Y2-Y1)*(Y2-Y1)+(Z2-Z1)*(Z2-Z1));
 largo2=largo/2.0;
};

void Object3D::set(double x2,double y2,double z2){

 X2=x2;
 Y2=y2;
 Z2=z2;
 largo=sqrt((X2-X1)*(X2-X1)+(Y2-Y1)*(Y2-Y1)+(Z2-Z1)*(Z2-Z1));
 largo2=largo/2.0;
};

     
void Object3D::set(struct coord a,struct coord b){

     set(a.x,a.y,a.z,b.x,b.y,b.z);       
};


void Object3D::display(int selected){
double anguloxy=angulo(X2-X1,Y2-Y1);
double dx,dy,dz,xx,yy,zz;
double RES=20;
int c;

glPushMatrix();
glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glColor4f(R,G,B,0.9);
if (selected) glColor4f(0,0,0.5,0.9);
dx=(X2-X1)/RES;
dy=(Y2-Y1)/RES;
dz=(Z2-Z1)/RES;

glPushMatrix();
glTranslated(X1,Y1,Z1);
glutSolidSphere(width*2,10,10);
glPopMatrix();

xx=X1;yy=Y1;zz=Z1;
for (c=1; c<=RES; c++){
glPushMatrix();
if (c<3 && selected)
	 glColor4f(0,0,1,0.9);
	 else
	 if (selected) 
     glColor4f(0,0,0.5,0.9);
	 else
	 	 glColor4f(R,G,B,0.9);
glTranslated(xx+=dx,yy+=dy,zz+=dz);
glutSolidSphere(width*2,10,10);
glPopMatrix();		
		}


glPushMatrix();
glTranslated(X2,Y2,Z2);
glutSolidSphere(width*2,10,10);
glPopMatrix();

//printf("(%1.2f,%1.2f) (%1.2f,%1.2f) %1.2f %1.2f : %1.2f\n",X1,Y1,X2,Y2,X2-X1,Y2-Y1,anguloxy);

glPopMatrix();
//printf("%f %f %f -  %f %f %f \n",X1,Y1,Z1,X2,Y2,Z2);
                
                    
}


void Object3D::setColor(double r,double g,double b){
     R=r;
     G=g;
     B=b;
}
