/* 
 Object3D Class
 3D Object properties and actions
 Francisco Igor
*/

#define width 0.08


struct coord {
       double x,y,z;       
};

class Object3D {



public:

     double X1,Y1,Z1,X2,Y2,Z2;
     double R,G,B;
     double largo,largo2;

     Object3D();
     void set(double x1,double y1,double z1,double x2,double y2,double z2);
     void set(struct coord a,struct coord b);
     void set(double x2,double y2,double z2);
     void setColor(double r,double g,double b);
     void display(int selected);
      
};
