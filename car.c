/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

// Window size 1920 x 1080
GLint winWidth = 1280, winHeight = 720;

// Viewport coordinates
GLdouble xmin = -2.0, xmax = 4.0, ymin = -2.0, ymax = 3.0, near = 1.0, far = 10.0, angle = 60.0;

// Enabled features
GLint axes = 1;
GLint flat = 1;
GLint checkpoints = 0;
GLint wireFrame = 0;
GLint animateWheels = 0;
GLint animateCar = 0;
GLint animateSpeed = 1;
GLint clear = 0;
GLint fog = 0;
GLint texture = 0;
GLubyte projectionMode = 'g';

// Spot
GLdouble spotHeight = 0.0;
GLdouble spotAngle = 0.0;
GLdouble spotExponent = 20.0;

// Material
GLdouble materialShininess = 10.0;

// Eye
GLdouble xLens = 1.0, yLens = 1.0, zLens = 3.0;
GLdouble xRef = 1.0, yRef = 1.0, zRef = 0.0;
GLdouble xVW = 0.0, yVW = 1.0, zVW = 0.0;

// OpenGL callback: menu calls
void menu(int id) {
	printf("Selected item ID: %d in main menu\n", id);
}

void bodyworkMenu(int id) {
	printf("Selected item ID: %d in bodyworkMenu\n", id);
}

void suspensionMenu(int id) {
	printf("Selected item ID: %d in suspensionMenu\n", id);
}

void finishMenu(int id) {
	printf("Selected item ID: %d in finishMenu\n", id);
}

// Init OpenGL defaults
void init(void)
{
	// Background and depth
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

	// Light sources default values
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, BLACK);
	glLightfv(GL_LIGHT0, GL_AMBIENT, BLACK);
	glLightfv(GL_LIGHT1, GL_AMBIENT, BLACK);
	glLightfv(GL_LIGHT2, GL_AMBIENT, BLACK);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, BLACK);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, BLACK);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, BLACK);
	glLightfv(GL_LIGHT0, GL_SPECULAR, BLACK);
	glLightfv(GL_LIGHT1, GL_SPECULAR, BLACK);
	glLightfv(GL_LIGHT2, GL_SPECULAR, BLACK);

	// Init menu
	// TODO: crashes on my PC due a lack of closed source video drivers
}

// OpenGL callback: timer animation
void beweeg(void) {
	if(animateWheels) {
		print("Wielen bewegen\n")
	}

	if(animateCar) {
		print("Auto bewegen\n")
	}
	glutTimerFunc(animateSpeed, animatie, NULL);
}

// OpenGL callback: keyboard input
void toetsen(unsigned char key, int x, int y)
{
	switch(key)
	{
		// Eye movement
		case 'x': xLens++; break;
		case 'X': xLens--; break;
		case 'y': yLens++; break;
		case 'Y': yLens--; break;
		case 'z': zLens++; break;
		case 'Z': zLens--; break;
		case 'i': xLens = yLens = zLens = 3.0; break;

		// Projection modes
		case '1': projectionMode = 'o'; printf("Projection mode ORTHOGONAL\n"); break;
		case '2': projectionMode = 's'; printf("Projection mode SYMMETRIC\n"); break;
		case '3': projectionMode = 'g'; printf("Projection mode GENERAL\n"); break;

		// Features
		case 's': flat = 0; printf("Shading mode SMOOTH\n"); break;
		case 'S': flat = 1; printf("Shading mode FLAT\n"); break;
		case 'l': wireFrame = 0; printf("Wireframe OFF\n"); break;
		case 'L': wireFrame = 1; printf("Wireframe ON\n"); break;
		case 'j': axes = 0; printf("Axes OFF\n"); break;
		case 'J': axes = 1; printf("Axes ON\n"); break;
		case 'k': checkpoints = 0; printf("Checkpoints surfaces OFF\n"); break;
		case 'K': checkpoints = 1; printf("Checkpoints surfaces ON\n"); break;
		case 'g': animateWheels != animateWheels; printf("Animation wheels TOGGLE\n"); break;
		case 'G': animateCar != animateCar; printf("Animation car TOGGLE\n"); break;
		case 't': texture != texture; printf("Texture TOGGLE\n"); break;
		case 'm': fog != fog; printf("Fog TOGGLE\n"); break;
		case 'f': clear != clear; printf("Transparancy TOGGLE"); break;
		case 'a': animateSpeed++; break;
		case 'A': animateSpeed--; break;

		// Spot
		case 'h': spotHeight++; break;
		case 'H': spotHeight--; break;
		case 'v': spotAngle++; break;
		case 'V': spotAngle--; break;
		case 'w': spotExponent = spotExponent + 5; break;
		case 'W': spotExponent = spotExponent - 5; break;

		// Material
		case 'e': materialShininess = materialShininess + 5; break;
		case 'E': materialShininess = materialShininess - 5; break;

		// Quit
		case 'q':
		case 'Q': exit(0); break;

		// Show error when pressing an unsupported key
		default:
		printf("Unsupported action!\n");
		return; // Nothing happened, don't redraw
	}
	printf("Eye X=%5.1f Y=%5.1f Z=%5.1f\n", xLens, yLens, zLens);
	printf("Spot HEIGHT=%5.1f ANGLE=%5.1f EXPONENT=%5.1f\n", spotHeight, spotAngle, spotExponent);
	printf("Material SHININESS=%5.1f\n", materialShininess);
	glutPostRedisplay();
}

// OpenGL callback: draw function
void wedstrijd(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);
	glShadeModel(flat? GL_FLAT: GL_SMOOTH);
	gluLookAt(xLens, yLens, zLens, xRef, yRef, zRef, xVW, yVW, zVW);
	drawAxes(axes);
	drawSuspension(wireFrame);
	drawTires(wireFrame);
	glFlush();
}

// OpenGL callback: reshape function
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
	glutTimerFunc(animateSpeed, animatie, NULL);
	glutMainLoop();
}
