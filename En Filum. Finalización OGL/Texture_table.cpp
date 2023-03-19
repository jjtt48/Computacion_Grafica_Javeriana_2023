#include "Texture_table.h"
Texturetable::Texturetable() {

}

void Texturetable::initialize_texture_table(void) {
	
	int w, h;
	GLubyte* data = 0;
	glGenTextures(1, &table);
	glBindTexture(GL_TEXTURE_2D, table);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	FIBITMAP* bitmap = FreeImage_Load(
		FreeImage_GetFileType("./Mallas/Table.jpg", 1),
		"./Mallas/Table.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura
	FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
	FreeImage_Unload(pImage);
	glEnable(GL_TEXTURE_2D);
}
void Texturetable::draw_table(GLMmodel* Table, float x, float y, float z,float Sx, float Sy, float Sz) {
	

	glPushMatrix();
	glScalef(Sx, Sy, Sz);
	glTranslatef(x, y, z);
	glBindTexture(GL_TEXTURE_2D, table);
	glmDraw(Table, GLM_TEXTURE | GLM_MATERIAL | GLM_SMOOTH);
	
	glPopMatrix();
	
	
}
