//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm.h"
#include <FreeImage.h> //*** Para Textura: Incluir librería
#include "Texture_table.h"
#include "Texture_Floor.h"
#include "Texture_P1.h"
#include "own_object.h"
//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   cwc::glShader* floor_shader; //Para Textura: variable para abrir los shader de textura
   cwc::glShader* table_shader;
   cwc::glShader* P1_shader;
   cwc::glShader* obj_shader;
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   GLMmodel* objmodel_ptr;
   GLMmodel* Table;
   GLMmodel* Floor; //*** Para Textura: variable para objeto texturizado
   GLMmodel* P1;
   GLMmodel* Obj;
   Texturetable * tt;
   Texture_Floor* tf;
   Texture_P1* tp1;
   own_object* cobj;
public:
	
	myWindow(){}

	
	

	

	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      timer010 = 0.09; //for screenshot!

      glPushMatrix();
	  glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);

     
//----------------------------------------------------------------------------------------------------------------------------|||||||
	  if (table_shader) table_shader->begin();
	  tt->draw_table(Table,0.0,0.25,0.0,0.8,1.0,0.8);
	  if (table_shader) table_shader->end();
//---------------------------------------------------------------------------------------------------------------------------||||||||	
	  //*** Para Textura: llamado al shader para objetos texturizados
	  if (floor_shader) floor_shader->begin();
		tf->draw_floor(Floor, 0.0, 0.0, 0.0, 1.5, 1.5, 1.5);
	  if (floor_shader) floor_shader->end();
	  
	  
//---------------------------------------------------------------------------------------------------------------------------||||||||	
//*** Para Textura: llamado al shader para objetos texturizados
	  if (P1_shader) P1_shader->begin();
		tp1->draw_P1(P1, 0.0, 1.0, -1.2, 0.5, 0.5, 0.5);
	  if (P1_shader) P1_shader->end();
 //---------------------------------------------------------------------------------------------------------------------------||||||||	

	  if (obj_shader) obj_shader->begin();
	  cobj->draw(Obj, 0.0, 0.0, -4.72, 0.11, 0.11, 0.11);
	  if (obj_shader) obj_shader->end();
      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		tt = new Texturetable();
		tf = new Texture_Floor();
		tp1 = new Texture_P1();
		cobj = new own_object();
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

	 //*** Para Textura: abre los shaders para texturas
		floor_shader = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (floor_shader == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = floor_shader->GetProgramObject();
		}
//------------------------------------------------------------------------------------------------------------
		table_shader = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); 
		if (table_shader == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = table_shader->GetProgramObject();
		}
//------------------------------------------------------------------------------------------------------------
		P1_shader = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt");
		if (P1_shader == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = P1_shader->GetProgramObject();
		}
//------------------------------------------------------------------------------------------------------------
		obj_shader = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt");
		if (obj_shader == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = obj_shader->GetProgramObject();
		}
      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

	  //Abrir mallas
	  Table = NULL;

	  if (!Table)
	  {
		  Table = glmReadOBJ("./Mallas/Table.obj");
		  if (!Table)
			  exit(0);

		  glmUnitize(Table);
		  glmFacetNormals(Table);
		  glmVertexNormals(Table, 90.0);
	  }
	  tt->initialize_texture_table();
	  DemoLight();
	  //*** Para Textura: abrir malla de objeto a texturizar
	  Floor = NULL;

	  if (!Floor)
	  {
		  Floor = glmReadOBJ("./Mallas/Carpet.obj");
		  if (!Floor)
			  exit(0);

		  glmUnitize(Floor);
		  glmFacetNormals(Floor);
		  glmVertexNormals(Floor, 90.0);
	  }
	  tf->initialize_texture_floor();
	  
	  DemoLight();
	  P1 = NULL;

	  if (!P1)
	  {
		  P1 = glmReadOBJ("./Mallas/P1.obj");
		  if (!P1)
			  exit(0);

		  glmUnitize(P1);
		  glmFacetNormals(P1);
		  glmVertexNormals(P1, 90.0);
	  }
	  tp1->initialize_texture_P1();

	  DemoLight();
	  Obj = NULL;

	  if (!Obj)
	  {
		  Obj = glmReadOBJ("./Mallas/Time_Machine.obj");
		  if (!Obj)
			  exit(0);

		  glmUnitize(Obj);
		  glmFacetNormals(Obj);
		  glmVertexNormals(Obj, 90.0);
	  }
	  cobj->initialize_texture_obj();

	  
	
	}


	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     // Light model parameters:
     // -------------------------------------------
     
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

