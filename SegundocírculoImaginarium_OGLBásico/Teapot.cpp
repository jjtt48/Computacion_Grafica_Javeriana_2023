#include "Teapot.h"
Teapot::Teapot()
{

}

void Teapot::dibujarTeapot(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(180, 0, 1, 0);
    glutSolidTeapot(0.5);
    glPopMatrix();
}