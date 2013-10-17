#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include "episodes.h"
#include "defs.h"


episodes episodes;


void display(void)
{
    
	episodes.glutDisplayFunc();
	
	if(episodes.hasFinished())
	{
		exit(1);
	}
}


void reshape(int w, int h)
{
	
	episodes.glutReshapeFunc(w,h);
}


void idle (void)
{
	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
	uint32_t mouse_status = 0;
	
    int b;
    switch(button)
	{
    	case GLUT_LEFT_BUTTON:   b=MB_LEFT;   break;
    	case GLUT_MIDDLE_BUTTON: b=MB_MIDDLE; break;
    	case GLUT_RIGHT_BUTTON:  b=MB_RIGHT;  break;
    }

    if(mouse_status & MB_PRESSED(mouse_status,b) && GLUT_UP == state)
	{
        mouse_status |= MB_CLICKED(mouse_status,b);
    }
    
	if( !(mouse_status & MB_PRESSED(b,mouse_status)) && GLUT_DOWN == state)
	{
        mouse_status = (mouse_status & ~(0L | MB_CLICKED(mouse_status,b))) | MB_PRESSED(mouse_status,b);
    }
	
	// notify observers
	observable_data data;
	data.msg_type = MSG_MOUSE;
	data.a = mouse_status;
	data.b = x;
	data.c = y;
	messaging::getInstance().notify(data);
}


void keyPressed(unsigned char key, int x, int y)
{
	observable_data data;
	data.msg_type = MSG_KEYBOARD;
	data.a = key;
	messaging::getInstance().notify(data);
}


void keySpecial(int key, int x, int y)
{
	observable_data data;
	data.msg_type = MSG_KEYBOARD_S;
	data.a = key;
	messaging::getInstance().notify(data);
}


int main (int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Kitchen wars");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(keySpecial);
	
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	episodes.start();
	
    glutMainLoop();
	
	return 0;
}

