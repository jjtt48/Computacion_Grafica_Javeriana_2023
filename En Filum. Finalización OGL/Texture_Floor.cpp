#include "Texture_Floor.h"

Texture_Floor::Texture_Floor() {

}

void Texture_Floor::initialize_texture_floor(void) {

	int w, h;
	GLubyte* data = 0;
	glGenTextures(1, &floor);
	glBindTexture(GL_TEXTURE_2D, floor);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	FIBITMAP* bitmap = FreeImage_Load(
		FreeImage_GetFileType("./Mallas/Floor.jpg", 1),
		"./Mallas/Floor.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura
	FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
	FreeImage_Unload(pImage);
	glEnable(GL_TEXTURE_2D);
}
void Texture_Floor::draw_floor(GLMmodel* Floor, float x, float y, float z, float Sx, float Sy, float Sz) {


	glPushMatrix();
	glScalef(Sx, Sy, Sz);
	glTranslatef(x, y, z);
	glBindTexture(GL_TEXTURE_2D, floor);
	glmDraw(Floor, GLM_TEXTURE | GLM_MATERIAL | GLM_SMOOTH);

	glPopMatrix();


}