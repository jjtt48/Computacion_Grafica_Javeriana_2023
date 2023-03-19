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
class Texturetable
{
public:
	GLuint table; //*** Para Textura: variable que almacena el identificador de textura
	Texturetable();
	void initialize_texture_table(void);
	void draw_table(GLMmodel* Table, float x, float y, float z, float Sx, float Sy, float Sz);
	
};

