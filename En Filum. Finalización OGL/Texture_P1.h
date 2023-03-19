#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm.h"
#include <FreeImage.h> 
class Texture_P1
{
public:
	GLuint p1; //*** Para Textura: variable que almacena el identificador de textura
	Texture_P1();
	void initialize_texture_P1(void);
	void draw_P1(GLMmodel* Table, float x, float y, float z, float Sx, float Sy, float Sz);
};

