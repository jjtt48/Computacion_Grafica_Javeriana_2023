#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
class Sphere
{
public:
	Sphere();
	void dibujarSphere(float Sx, float Sy, float Sz, float radius, float x, float y, float z);

};

