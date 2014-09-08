#ifndef GL_HELPER_H
#define GL_HELPER_H

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include "SOIL.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

class gl_helper 
{
	
private:

	/****************************************************************
	
								public
	
	****************************************************************/
	
	
public:
	
	gl_helper()
	{
	}

	~gl_helper()
	{
	}


	// Draws a texture onto a simple square by using 2 triangles.
	// Inputs:
	//	texture: Given texture.
	//	tx: Translation in x.
	//	ty: Translation in y.
	//	x: 
	//	y: 
	//	xw: 
	//	yh: 
	static void draw_texture(GLuint texture, double tx, double ty, int x, int y, int xw, int yh)
	{
		glPushMatrix();

		glTranslatef(tx,ty,0.f);

	    glBindTexture(GL_TEXTURE_2D,texture);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	
		glBegin(GL_TRIANGLES); 	
		glTexCoord2f(0.0f, 0.0f);	glVertex2i(x,y);
		glTexCoord2f(1.0f, 0.0f);	glVertex2i(xw,y);
		glTexCoord2f(1.0f, 1.0f);	glVertex2i(xw,yh);
		glTexCoord2f(0.0f, 0.0f);	glVertex2i(x,y);
		glTexCoord2f(0.0f, 1.0f);	glVertex2i(x,yh);
		glTexCoord2f(1.0f, 1.0f);	glVertex2i(xw,yh);
		glEnd();
	
		glPopMatrix();
	}


	// Draws a quad.
	// Inputs:
	//	tx: Translation in x.
	//	ty: Translation in y.
	//	x:
	//	y:
	//	xw:
	//	yh:
	//	color: Static array of 3 specifying the color.
	static void draw_quad(double tx, double ty, int x, int y, int xw, int yh, float color[3])
	{
		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D,0);

		glTranslatef(tx,ty,0.f);
	
		glLineWidth(1.f);
		glColor3f(color[0],color[1],color[2]);

	    glBegin(GL_QUADS);
	    glVertex2i(xw,yh);
	    glVertex2i(xw,y);
	    glVertex2i(x,y);
	    glVertex2i(x,yh);
		glEnd();

		glPopMatrix();
	}
	
	
};

#endif /* GL_HELPER_H */