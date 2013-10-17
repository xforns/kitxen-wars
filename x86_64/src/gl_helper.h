#ifndef GL_HELPER_H
#define GL_HELPER_H

#include "SOIL.h"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class gl_helper 
{
	
public:
	
	
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
	
	
	// novembre: dissabte 9
	// novembre: dia 1 començaria el periode de prova
	// desembre: dia 7
	// acabaria el periode de prova el 8
	// diumenge novembre 24: deep jungle comença
	static void draw_texture(GLuint texture, double tx, double ty, int x, int y, int xw, int yh)
	{
		glPushMatrix();
	
		glTranslatef(tx,ty,0.f);
	
	    glBindTexture(GL_TEXTURE_2D,texture);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	
	    glBegin(GL_QUADS);
	    glTexCoord2i(1,1); glVertex2i(xw,yh);
	    glTexCoord2i(1,0); glVertex2i(xw,y);
	    glTexCoord2i(0,0); glVertex2i(x,y);
	    glTexCoord2i(0,1); glVertex2i(x,yh);
		glEnd();
	
		glPopMatrix();
	}
	
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
	
	
	/****************************************************************
	
								private

	****************************************************************/
	
private:
	
};

#endif /* GL_HELPER_H */