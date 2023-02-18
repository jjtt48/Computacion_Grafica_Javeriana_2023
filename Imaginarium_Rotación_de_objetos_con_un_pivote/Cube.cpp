#include "Cube.h"
Cube::Cube()
{

}

void Cube::dibujarCube(float x, float y, float z)
{
    glPushMatrix();
    //glRotatef(45, 0, 0, 1);
    glScalef(2,5,7);
    glTranslatef(x,y,z);
    glutSolidCube(0.5);

    glPopMatrix();
}
void Cube::dibujarCube45Grados(float x, float y, float z)
{
    glPushMatrix();
    
        glTranslatef(x, y, z);
        glRotatef(45, 0, 0, 1);
        glutSolidCube(0.5);
    glPopMatrix();
}