#pragma once
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
class own_object
{
public:
	GLuint obj; //*** Para Textura: variable que almacena el identificador de textura
	own_object();
	void initialize_texture_obj(void);
	void draw(GLMmodel* Table, float x, float y, float z, float Sx, float Sy, float Sz);
};

