/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

void init(void)
{
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
}

void toetsen(unsigned char key, int x, int y)
{
	switch(key)
	{
		// Eye movement
		case 'x': xLens++; break;	case 'X': xLens--; break;
		case 'y': yLens++; break;	case 'Y': yLens--; break;
		case 'z': zLens++; break;	case 'Z': zLens--; break;
		case 'i': xLens = yLens = zLens = 3.0; break;

		// Projection modes
		case '1': projectionMode = 'o'; break;
		case '2': projectionMode = 's'; break;
		case '3': projectionMode = 'g'; break;

		// Features
		case 's': flat = 1; break;
		case 'S': flat = 0; break;

		// Quit
		case 'q': exit(0); break;

		// Show error when pressing an unsupported key
		default:
		printf("Unsupported action!\n");
		return; // Nothing happened, don't redraw
	}
	printf("Eye X=%5.1f Y=%5.1f Z=%5.1f", xLens, yLens, zLens);
	glutPostRedisplay();
}

void wedstrijd(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(flat? GL_FLAT: GL_SMOOTH );
	gluLookAt(xLens, yLens, zLens, xRef, yRef, zRef, xVW, yVW, zVW);
	drawAxes();
	drawSuspension();
	glFlush();
}

void raam(GLint newWidth, GLint newHeight)
{
	GLdouble border;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Projection mode
	switch(projectionMode)
	{
		// Orthogonal perspective
		case 'o':
				glOrtho(xmin, xmax,  ymin, ymax, near, far);
				printf("Orthogonal perspective\n");
				break;
		// Symmetric perspective
		case 's':
				border = near*tan(M_PI*(angle/2.0)/180.0);
				glFrustum(-border, border, -border, border, near, far);
				printf("Symmetric perspective\n");
				break;
		// Default: General perspective
		default:
		case 'g':
				gluPerspective(angle, 1.0,  near, far);
				printf("General perspective\n");
				break;
	}

	// Keep ratio
	if(newWidth < newHeight) {
		glViewport(0, 0, newWidth, newWidth);
	}
	else {
		glViewport(0, 0, newHeight, newHeight);
	}
}

// Main loop
int main( int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Soapbox car");
    init();
	glutKeyboardFunc(toetsen);
	glutReshapeFunc(raam);
	glutDisplayFunc(wedstrijd);
	glutMainLoop();
}
