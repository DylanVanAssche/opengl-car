/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/

#include "car.h"

// Initialize the OpenGL background, lights, ...
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);  // Window background color
	glEnable(GL_DEPTH_TEST); // Enable depth checks
}

// OpenGL callback when a keyboard key has been pressed
void toets(unsigned char key, int x, int y) {
	switch(key) {
		case 'q':
			printf("Exiting now...\n");
			exit(0);
			break;
		case '1':
			projectionMode = 'o';
			break;
		case '2':
			projectionMode = 's';
			break;
		case '3':
			projectionMode = 'g';
			break;
		case 'a':
			axes=!axes;
			printf("Axes toggled\n");
			break;
		default:
			printf("Keyboard shortcut isn't supported!\n");
			break;
	}

	// Enforce redraw
	glutPostRedisplay();
}

// OpenGL callback when the window is rescaled or moved.
void raam(GLint newWidth, GLint newHeight)
{
	/*GLdouble border;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch(projectionMode)
	{
		// Orthogonal perspective
		case 'o':
				glOrtho(xmin, xmax,  ymin, ymax, near, far);
				break;
		// Symmetric perspective
		case 's':
				border = near*tan(M_PI*(angle/2.0)/180.0);
				glFrustum(-border, border, -border, border, near, far);
				break;
		// Default: General perspective
		default:
		case 'g':
				gluPerspective(angle, 1.0,  near, far);
				break;
	}
	glViewport(0, 0, newWidth, newHeight);
	printf("New window: %d x %d\n", newWidth, newHeight);*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xmin, xmax, ymin, ymax);
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
	printf("nieuw schaal %dx%d\n", newWidth, newHeight);
}

// OpenGL callback when a redraw is needed
void wedstrijd(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	//drawAxes();
	// assen
	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0); // rood
	glBegin(GL_LINES);
		// X-AXIS
		glVertex2s(0, 0);
		glVertex2s(xmax, 0);

		// Y-AXIS
		glVertex2s(0, 0);
		glVertex2s(0, ymax);
	glEnd();
	glFlush();
}

// main loop
int main (int argc,char* argv[])
{
	printf("Futuristic soapbox car in OpenGL\n");
	printf("(c) Dylan Van Assche - 3 ABA EI (2017 - 2018)\n");
	printf("Released under the GPLv3 License (https://www.github.com/dylanvanassche/opengl-car)\n");
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Futuristic soapbox car");
	init();
	glutDisplayFunc(wedstrijd);
	glutReshapeFunc(raam);
	glutKeyboardFunc(toets);
	glutMainLoop();
	return 0;
}
