#include "Sphere.h"
Sphere::Sphere()
{

}

void Sphere::dibujarSphere( float Sx, float Sy,float Sz, float radius,float x, float y, float z) {
    glPushMatrix();
    
    glScalef(Sx,Sy,Sz);
    glTranslatef(x, y, z);
    glutSolidSphere(0.9, 100, 100);
    glRotatef(90, 0, 1, 1);
    glPopMatrix();
}