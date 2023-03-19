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
class Texture_Floor
{
public:
	GLuint floor; //*** Para Textura: variable que almacena el identificador de textura
	Texture_Floor();
	void initialize_texture_floor(void);
	void draw_floor(GLMmodel* Table, float x, float y, float z, float Sx, float Sy, float Sz);
};

