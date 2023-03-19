#include "Texture_P1.h"
Texture_P1::Texture_P1() {

}

void Texture_P1::initialize_texture_P1(void) {

	int w, h;
	GLubyte* data = 0;
	glGenTextures(1, &p1);
	glBindTexture(GL_TEXTURE_2D, p1);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	FIBITMAP* bitmap = FreeImage_Load(
		FreeImage_GetFileType("./Mallas/P1.png", 1),
		"./Mallas/P1.png");  //*** Para Textura: esta es la ruta en donde se encuentra la textura
	FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
	FreeImage_Unload(pImage);
	glEnable(GL_TEXTURE_2D);
}
void Texture_P1::draw_P1(GLMmodel* P1, float x, float y, float z, float Sx, float Sy, float Sz) {


	glPushMatrix();
	glScalef(Sx, Sy, Sz);
	glTranslatef(x, y, z);
	glBindTexture(GL_TEXTURE_2D, p1);
	glmDraw(P1, GLM_TEXTURE | GLM_MATERIAL | GLM_SMOOTH);

	glPopMatrix();

}
