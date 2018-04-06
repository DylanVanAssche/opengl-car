/*
#################################################################################
#	OpenGL futuristic soapbox car						#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)				#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)	#
#################################################################################
*/

#include <GL/glut.h>
#include "car.h"

// Window size 1920 x 1080
GLint winWidth = 1920, winHeight = 1080;

// Viewport coordinates
GLdouble xmin = 0.0, xmax = 50.0, ymin = 0.0, ymax = 2000.0;

// Enabled features
int assen = 1;

// Initialize the OpenGL background, lights, ...
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);  /* window color white */
}

// OpenGL callback when a keyboard key has been pressed
void toets(unsigned char key, int x, int y) {
	switch(key) {
		case 'q': exit(0); break;
		case 'a': assen=!assen; break;
		case 'v': verbinden=!verbinden; break;
	}
	
	glutPostRedisplay();
}

// OpenGL callback when the window is rescaled or moved.
void raam(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	randX = (xmax-xmin)*X_RAND;
	randY = (ymax-ymin)*Y_RAND;
	gluOrtho2D(xmin-randX, xmax+randX, ymin-randY, ymax+randY);
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
	printf("nieuw schaal %dx%d\n", newWidth, newHeight);
}

// OpenGL callback when a redraw is needed
void wedstrijd(void)
{
	
}	

// main loop
int main (int argc,char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);  
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Futuristic soapbox car");
	init();
	glutDisplayFunc(displayFcn);	
	glutReshapeFunc(winReshapeFcn);
	glutKeyboardFunc(keyWatcherFcn);
	glutMouseFunc(mouseWatcherFcn);
	glutMainLoop();
	return 0;
}
