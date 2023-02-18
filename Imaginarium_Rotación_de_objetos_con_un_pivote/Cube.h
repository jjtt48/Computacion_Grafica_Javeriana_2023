#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
class Cube
{
public:
	Cube();
	void dibujarCube(float x, float y, float z);
	void dibujarCube45Grados(float x, float y, float z);
};


