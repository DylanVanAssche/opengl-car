/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

// Window
GLint winWidth = 1024, winHeight = 720;

// Viewport coordinates
GLdouble xmin = -50.0, xmax = 50.0, ymin = -50.0, ymax = 50.0, near = 0.1, far = 25.0, angle = 60.0;

// Enabled features
GLint axes = 1;
GLint flat = 1;
GLint checkpoints = 0;
GLint wireFrame = 0;
GLint animateWheels = 0;
GLint animateCar = 0;
GLint clear = 0;
GLint fog = 0;
GLint fogMode = 0;
GLint competition = 0;
GLint texture = 0;
GLubyte projectionMode = 'g';
GLfloat* coachworkAmbient = AMBIENT_GRAY;
GLfloat* coachworkDiffuse = DIFFUSE_GRAY;
GLfloat* coachworkSpecular = SPECULAR_GRAY;
GLfloat* suspensionAmbient = AMBIENT_BRONZE;
GLfloat* suspensionDiffuse = DIFFUSE_BRONZE;
GLfloat* suspensionSpecular = SPECULAR_BRONZE;
GLfloat* finishAmbient = AMBIENT_YELLOW;
GLfloat* finishDiffuse = DIFFUSE_YELLOW;
GLfloat* finishSpecular = SPECULAR_YELLOW;

// Animation
GLfloat animationWheelsAngle = 0.0;
GLfloat animationCarTranslation = 0.0;

// Lights
GLint lightsLocked = 0;
GLint ambientLight = 0;
GLint diffuseLight = 0;
GLint specularLight = 0;
GLint spotLight = 0;
GLdouble spotHeight = SPOT_HEIGHT_DEFAULT;
GLdouble spotAngle = SPOT_ANGLE_DEFAULT;
GLdouble spotExponent = SPOT_EXPONENT_DEFAULT;

// Material
GLdouble materialShininess = 10.0;

// Eye
GLdouble xLens = 1.0, yLens = 1.0, zLens = 3.0;
GLdouble xRef = 1.0, yRef = 1.0, zRef = 0.0;
GLdouble xVW = 0.0, yVW = 1.0, zVW = 0.0;

// OpenGL callback: menu calls
void menu(GLint id) {
	printf("Selected item ID: %d in main menu\n", id);
	switch(id) {
		case MENU_QUIT:
		exit(0);
		break;

		default:
		printf("Unsupported action!\n");
		return; // Avoid redisplay when nothing has been changed
	}
	glutPostRedisplay();
}

void coachworkMenu(GLint id) {
	printf("Selected item ID: %d in coackworkMenu\n", id);
	switch(id) {
		case MENU_COACHWORK_GRAY:
			coachworkAmbient = AMBIENT_GRAY;
			coachworkDiffuse = DIFFUSE_GRAY;
			coachworkSpecular = SPECULAR_GRAY;
		break;

		case MENU_COACHWORK_WHITE:
			coachworkAmbient = AMBIENT_WHITE;
			coachworkDiffuse = DIFFUSE_WHITE;
			coachworkSpecular = SPECULAR_WHITE;
		break;

		default:
		printf("Unsupported action!\n");
		return; // Avoid redisplay when nothing has been changed
	}
	glutPostRedisplay();
}

void suspensionMenu(GLint id) {
	printf("Selected item ID: %d in suspensionMenu\n", id);
	switch(id) {
		case MENU_SUSPENSION_BRONZE:
			suspensionAmbient = AMBIENT_BRONZE;
			suspensionDiffuse = DIFFUSE_BRONZE;
			suspensionSpecular = SPECULAR_BRONZE;
		break;

		case MENU_SUSPENSION_CHROME:
			suspensionAmbient = AMBIENT_CHROME;
			suspensionDiffuse = DIFFUSE_CHROME;
			suspensionSpecular = SPECULAR_CHROME;
		break;

		default:
		printf("Unsupported action!\n");
		return; // Avoid redisplay when nothing has been changed
	}
	glutPostRedisplay();
}

void finishMenu(GLint id) {
	printf("Selected item ID: %d in finishMenu\n", id);
	switch(id) {
		case MENU_FINISH_YELLOW:
			finishAmbient = AMBIENT_YELLOW;
			finishDiffuse = DIFFUSE_YELLOW;
			finishSpecular = SPECULAR_YELLOW;
		break;

		case MENU_FINISH_LILAC:
			finishAmbient = AMBIENT_LILA;
			finishDiffuse = DIFFUSE_LILA;
			finishSpecular = SPECULAR_LILA;
		break;

		default:
		printf("Unsupported action!\n");
		return; // Avoid redisplay when nothing has been changed
	}
	glutPostRedisplay();
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
	glLightfv(GL_LIGHT3, GL_AMBIENT, BLACK);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, BLACK);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, BLACK);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, BLACK);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, BLACK);
	glLightfv(GL_LIGHT0, GL_SPECULAR, BLACK);
	glLightfv(GL_LIGHT1, GL_SPECULAR, BLACK);
	glLightfv(GL_LIGHT2, GL_SPECULAR, BLACK);
	glLightfv(GL_LIGHT3, GL_SPECULAR, BLACK);

	// Init menu
	GLint menuCoachworkID = glutCreateMenu(coachworkMenu);
	glutAddMenuEntry("grey", MENU_COACHWORK_GRAY);
	glutAddMenuEntry("white", MENU_COACHWORK_WHITE);

	GLint menuSuspensionID = glutCreateMenu(suspensionMenu);
	glutAddMenuEntry("chrome", MENU_SUSPENSION_CHROME);
	glutAddMenuEntry("bronze", MENU_SUSPENSION_BRONZE);

	GLint menuFinishID = glutCreateMenu(finishMenu);
	glutAddMenuEntry("yellow", MENU_FINISH_YELLOW);
	glutAddMenuEntry("lilac", MENU_FINISH_LILAC);

	// Main menu
	GLint menuID = glutCreateMenu(menu);
	glutAddSubMenu("Coachwork", menuCoachworkID);
	glutAddSubMenu("Suspension", menuSuspensionID);
	glutAddSubMenu("Finish", menuFinishID);
	glutAddMenuEntry("quit", MENU_QUIT);

	// Attach menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Load textures from JPG files
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(NUMBER_OF_TEXTURES, textureAddressing);
	for(GLint i=0; i < NUMBER_OF_TEXTURES; i++) {
		tImageJPG *textureJPG;
	    textureJPG = LoadJPG(nameTexture[i]);
		glBindTexture(GL_TEXTURE_2D, textureAddressing[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureJPG->sizeX, textureJPG->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureJPG->data);
		printf("Loaded %s: %dx%d\n", nameTexture[i], textureJPG->sizeX, textureJPG->sizeY);
	}
}

// OpenGL callback: timer animation
void animation(GLint value) {
	// Wheels movement
	if(animateWheels) {
		printf("The wheels on the soapbox car go round and round... ANGLE=%f\n", animationWheelsAngle);
		animationWheelsAngle += ANIMATION_WHEEL_STEP;

		// Reset angle after 360 degrees
		if(animationWheelsAngle >= 360.0) {
			animationWheelsAngle = 0.0;
		}
	}

	// Car movement
	if(animateCar) {
		printf("Gas met die zooi! TRANSLATION=%f\n", animationCarTranslation);
		animationCarTranslation += ANIMATION_CAR_STEP;

		// Reset when car is out of sight (far)
		if(animationCarTranslation <= -far) {
			animationCarTranslation = far;
		}
	}

	// Only update when animations are activated
	if(animateWheels || animateCar) {
    	glutPostRedisplay();
	}

	// Restart Timer callback
	glutTimerFunc(ANIMATION_SPEED, animation, 0);
}

// OpenGL callback: keyboard input
void keyboardWatcher(unsigned char key, int x, int y)
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
		case 'i': xLens = yLens = zLens = VIEW_RESET_POS; printf("View lens resetted\n"); break;

		// Projection modes
		case '1': ambientLight = !ambientLight; printf("Ambient light TOGGLE\n"); break;
		case '2': diffuseLight = !diffuseLight; printf("Diffuse light TOGGLE\n"); break;
		case '3': specularLight = !specularLight; printf("Specular light TOGGLE\n"); break;
		case '4': spotLight = !spotLight; printf("Spotlight TOGGLE\n"); break;

		// Features
		case 's': flat = 0; printf("Shading mode SMOOTH\n"); break;
		case 'S': flat = 1; printf("Shading mode FLAT\n"); break;
		case 'l': wireFrame = 0; printf("Wireframe OFF\n"); break;
		case 'L': wireFrame = 1; printf("Wireframe ON\n"); break;
		case 'j': axes = 0; printf("Axes OFF\n"); break;
		case 'J': axes = 1; printf("Axes ON\n"); break;
		case 'k': checkpoints = 0; printf("Checkpoints surfaces OFF\n"); break;
		case 'K': checkpoints = 1; printf("Checkpoints surfaces ON\n"); break;
		case 'g': animateWheels = !animateWheels; printf("Animation wheels TOGGLE\n"); break;
		case 'G': animateCar = !animateCar; printf("Animation car TOGGLE\n"); break;
		case 't': texture = !texture; printf("Texture TOGGLE\n"); break;
		case 'm': fog = !fog; printf("Fog TOGGLE\n"); break;
		case 'M': fogMode = !fogMode; printf("Fog exponent/lineair mode TOGGLE\n"); break;
		case 'n': competition = !competition; printf("Competition TOGGLE\n"); break;
		case 'f': clear = !clear; printf("Transparency TOGGLE\n"); break;

		// Spot
		case 'h': spotHeight++; break;
		case 'H': spotHeight--; break;
		case 'v': spotAngle++; break;
		case 'V': spotAngle--; break;
		case 'w': spotExponent = spotExponent + 5; break;
		case 'W': spotExponent = spotExponent - 5; break;
		case 'b': lightsLocked = !lightsLocked; printf("Lights locked TOGGLE\n"); break;

		// Material
		case 'e': materialShininess < MATERIAL_SHININESS_MAX?
		(materialShininess = materialShininess + MATERIAL_SHININESS_STEP):
		(materialShininess = MATERIAL_SHININESS_MAX);
		break;
		case 'E': materialShininess > MATERIAL_SHININESS_MIN?
		(materialShininess = materialShininess - MATERIAL_SHININESS_STEP):
		(materialShininess = MATERIAL_SHININESS_MIN);
		break;

		// Quit
		case 'q':
		case 'Q': exit(0); break;

		// Show error when pressing an unsupported key
		default:
		printf("Unsupported action!\n");
		return; // Nothing happened, don't redraw
	}
	printf("Eye X=%f Y=%f Z=%f\n", xLens, yLens, zLens);
	printf("Ambient ENABLED=%d\n", ambientLight);
	printf("Diffuse ENABLED=%d\n", diffuseLight);
	printf("Specular ENABLED=%d\n", specularLight);
	printf("Spot ENABLED=%d HEIGHT=%f ANGLE=%f EXPONENT=%f\n", spotLight, spotHeight, spotAngle, spotExponent);
	printf("Material SHININESS=%5.1f\n", materialShininess);
	glutPostRedisplay();
}

// OpenGL callback: draw function
void displayFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(flat? GL_FLAT: GL_SMOOTH);
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

	// Configure fog
	configureFog(fog, fogMode, far);

	// Lights stay at the same place when set before gluLookAt
	if(lightsLocked) {
		printf("Lights locked\n");
		configureLights(ambientLight, diffuseLight, specularLight, spotLight, spotAngle, spotExponent, spotHeight);
	}
	gluLookAt(xLens, yLens, zLens, xRef, yRef, zRef, xVW, yVW, zVW);
	if(!lightsLocked) {
		printf("Lights unlocked\n");
		configureLights(ambientLight, diffuseLight, specularLight, spotLight, spotAngle, spotExponent, spotHeight);
	}

	drawAxes(axes);

	// Elements where the lights will affect their appearence
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

		// Draw solid finish before blending functions are activated
		drawFinish(wireFrame, finishAmbient, finishDiffuse, finishSpecular, competition, textureAddressing, texture, checkpoints);

		// Push matrix to isolate translation animation
		glPushMatrix();
			// Make sure the cars are in the center of the finish
			competition? glTranslatef(animationCarTranslation, 0.0, 0.25): glTranslatef(animationCarTranslation, 0.0, 0.5);

			// soapbox car 1
			drawSuspension(wireFrame, suspensionAmbient, suspensionDiffuse, suspensionSpecular);
			drawTires(wireFrame, animationWheelsAngle, textureAddressing, texture);
			drawCoachwork(wireFrame, coachworkAmbient, coachworkDiffuse, coachworkSpecular, clear, checkpoints);

			// soapbox car 2
			if(competition) {
				glTranslatef(0.0, 0.0, 2.0);
				drawSuspension(wireFrame, suspensionAmbient, suspensionDiffuse, suspensionSpecular);
				drawTires(wireFrame, animationWheelsAngle, textureAddressing, texture);
				drawCoachwork(wireFrame, coachworkAmbient, coachworkDiffuse, coachworkSpecular, clear, checkpoints);
			}
		glPopMatrix();

	glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);

	// Swap the buffers and flush
	glutSwapBuffers();
	glFlush();
}

// OpenGL callback: reshape function
void windowFunction(GLint newWidth, GLint newHeight)
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

	glViewport(0, 0, newWidth, newHeight);
}

// Main loop
int main(int argc, char* argv[])
{
	// Selects projection mode
	// - 'o' ORTHOGONAL perspective
	// - 's' SYMMETRIC perspective
	// - 'g' GENERAL perspective
	if(argc > 1) {
		projectionMode = argv[1][0];
	}
	else {
		printf("Projection mode can be changed using arguments\n");
		projectionMode = 'g';
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Soapbox car");
    init();
	glutKeyboardFunc(keyboardWatcher);
	glutReshapeFunc(windowFunction);
	glutDisplayFunc(displayFunction);
	glutTimerFunc(ANIMATION_SPEED, animation, 0);
	glutMainLoop();
}
