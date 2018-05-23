/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

// Definitions
GLfloat RED[] = {1.0, 0.0, 0.0, 1.0};
GLfloat GREEN[] = {0.0, 1.0, 0.0, 1.0};
GLfloat BLUE[] = {0.0, 0.0, 1.0, 1.0};
GLfloat GREEN_BLUE[] = {0.0, 0.75, 0.75, 1.0};
GLfloat YELLOW[] = {1.0, 1.0, 0.0, 1.0};
GLfloat WHITE[] = {1.0, 1.0, 1.0, 1.0};
GLfloat BLACK[] = {0.0, 0.0, 0.0, 1.0};
GLfloat BLUE_GRAY[] = {0.44, 0.5, 0.56, 1.0};

GLfloat AMBIENT_GRAY[] = {0.22, 0.22, 0.22, 1.0};
GLfloat DIFFUSE_GRAY[] = {0.33, 0.33, 0.33, 1.0};
GLfloat SPECULAR_GRAY[] = {0.11, 0.11, 0.11, 1.0};
GLfloat AMBIENT_BLACK[] = {0.11, 0.11, 0.11, 1.0};
GLfloat DIFFUSE_BLACK[] = {0.055, 0.055, 0.055, 1.0};
GLfloat SPECULAR_BLACK[] = {0.0275, 0.0275, 0.0275, 1.0};
GLfloat AMBIENT_WHITE[] = {0.66, 0.66, 0.66, 1.0};
GLfloat DIFFUSE_WHITE[] = {0.77, 0.77, 0.77, 1.0};
GLfloat SPECULAR_WHITE[] = {0.55, 0.55, 0.55, 1.0};
GLfloat AMBIENT_CHROME[] = {0.46, 0.58, 0.35, 1.0};
GLfloat DIFFUSE_CHROME[] = {0.23, 0.29, 0.17, 1.0};
GLfloat SPECULAR_CHROME[] = {0.69, 0.87, 0.52, 1.0};
GLfloat AMBIENT_BRONZE[] = {0.21, 0.13, 0.10, 1.0};
GLfloat DIFFUSE_BRONZE[] = {0.39, 0.27, 0.17, 1.0};
GLfloat SPECULAR_BRONZE[] = {0.71, 0.43, 0.18, 1.0};
GLfloat AMBIENT_YELLOW[] = {0.65, 0.55, 0.15, 1.0};
GLfloat DIFFUSE_YELLOW[] = {0.75, 0.45, 0.15, 1.0};
GLfloat SPECULAR_YELLOW[] = {0.85, 0.35, 0.15, 1.0};
GLfloat AMBIENT_LILA[] = {0.45, 0.15, 0.75, 1.0};
GLfloat DIFFUSE_LILA[] = {0.55, 0.15, 0.65, 1.0};
GLfloat SPECULAR_LILA[] = {0.35, 0.15, 0.85, 1.0};

GLfloat finishCheckpoints[FINISH_BSPLINE_ORDER][FINISH_BSPLINE_ORDER][FINISH_BSPLINE_DIMENSION] = {
    {
        // Half circle in XZ
        {0.0, 0.0, -1.0+3.0},
        {1.41, 0.0, -0.707+3.0},
        {1.41, 0.0, 0.707+3.0},
        {0.0, 0.0, 1.0+3.0}
    },
    {
        // Half circle 30 degrees
        {0.0, 1.5-0.5, -0.5+2.59},
        {1.41, 1.5-0.10, -0.61+2.59},
        {1.41, 1.5+0.10, 0.61+2.59},
        {0.0, 1.5+0.5, 0.5+2.59}
    },
    {
        // Half circle 60 degrees
        {0.0, 2.59-0.5, -0.5+1.5},
        {1.41, 2.59-0.61, -0.10+1.5},
        {1.41, 2.59+0.61, 0.10+1.5},
        {0.0, 2.59+0.5, 0.5+1.5}
    },
    {
        // Half circle in XY
        {0.0, 3.0-1.0, 0.0},
        {1.41, 3.0-0.707, 0.0},
        {1.41, 3.0+0.707, 0.0},
        {0.0, 3.0+1.0, 0.0}
    }
};
GLfloat knots[2*FINISH_BSPLINE_ORDER] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};

GLfloat coachworkCheckpoints[COACHWORK_BEZIER_WIDTH][COACHWORK_BEZIER_LENGTH][COACHWORK_BEZIER_DIMENSIONS] = {
    // 2 points extra for the length of the coachwork to provide a cutout for the seat
   {
       {0.5, 0.0, 0.33},
       {1.0, 0.0, 0.66},
       {1.5, 0.0, 0.66},
       {1.7, 0.0, 0.66},
       {1.9, 0.0, 0.66},
       {2.0, 0.0, 0.66}
   },
   {
       {0.0, 0.25, 0.33},
       {0.5, 0.25, 0.66},
       {1.5, 0.25, 0.66},
       {1.7, 0.25, 0.66},
       {1.9, 0.25, 0.66},
       {2.0, 0.25, 0.66}
   },
   {
       {0.0, 0.375, 0.33},
       {0.5, 0.375, 0.66},
       {1.5, 0.375, 0.66},
       {1.7, 0.375, 0.66},
       {1.9, 0.375, 0.66},
       {2.0, 0.375, 0.66}
   },
   {
       {0.0, 0.4, 0.125},
       {0.5, 0.4, 0.125},
       {1.5, 0.4, 0.125},
       {1.8, 0.4, 0.125},
       {1.9, 0.4, 0.45},
       {2.5, 0.4, 0.5}
   }
};

GLfloat posLight0[] = {3.0, 3.0, 3.0, 1.0};
GLfloat posLight1[] = {3.0, 3.0, -3.0, 1.0};
GLfloat posLight2[] = {3.0, 3.0, 3.0, 1.0};
GLfloat posLight3[] = {5.0, SPOT_HEIGHT_DEFAULT, 1.0, 1.0};
GLfloat spotDirection[] = {-1.0, -1.0, 0.0};

// Textures and complex surfaces
const char nameTexture[NUMBER_OF_TEXTURES][TEXTURE_NAME_LENGTH] = {"./images/tire.jpg", "./images/rim.jpg", "./images/finish.jpg"};
GLuint textureAddressing[NUMBER_OF_TEXTURES];

// Enabled features
GLint axes = 1;
GLint lightsPosition = 1;
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
/*
 * GLint id: select menu ID
 */
void menu(GLint id)
{
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

/*
 * GLint id: select menu ID
 */
void coachworkMenu(GLint id)
{
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

/*
 * GLint id: select menu ID
 */
void suspensionMenu(GLint id)
{
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

/*
 * GLint id: select menu ID
 */
void finishMenu(GLint id)
{
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
	glClearDepth(1.0); // Clear depth buffer completely
	glEnable(GL_DEPTH_TEST); // Allow evaluating of the depth when drawing objects

	// Light sources override default values
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

	// Attach menu to the mouse it's RIGHT BUTTON
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Load textures from JPG files
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // byte alignment for JPG's in memory
	glGenTextures(NUMBER_OF_TEXTURES, textureAddressing); // texture pointers
	for(GLint i=0; i < NUMBER_OF_TEXTURES; i++) {
		tImageJPG *textureJPG;
	    textureJPG = LoadJPG(nameTexture[i]); // load jpg
		glBindTexture(GL_TEXTURE_2D, textureAddressing[i]); // bind pointer to texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureJPG->sizeX, textureJPG->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureJPG->data); // apply JPG on texture
		printf("Loaded %s: %dx%d\n", nameTexture[i], textureJPG->sizeX, textureJPG->sizeY);
	}
}

// OpenGL callback: timer animation
/*
 * GLint value: unused but required for glutTimerFunc
 */
void animation(GLint value)
{
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
		if(animationCarTranslation <= -PROJECTION_FAR) {
			animationCarTranslation = PROJECTION_FAR;
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
/*
 * unsigned char key: ASCII code of the key
 * int x: mouse X
 * int y: mouse Y
 */
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
		case 'i': xLens = yLens = zLens = VIEW_RESET_POS; printf("View lens reset OK\n"); break;

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
        case 'p': lightsPosition = 0; printf("Lights position OFF\n"); break;
		case 'P': lightsPosition = 1; printf("Lights position ON\n"); break;
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
	// Clear color and depth buffers (avoid old data)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Modelview matrix used for translation, scaling and rotating
	// (GP_PROJECTION is used only for the projection of the objects)
	glMatrixMode(GL_MODELVIEW);
	// Replace the current matrix in GL_MODELVIEW with an identity matrix
	glLoadIdentity();
	// Shading mode
	glShadeModel(flat? GL_FLAT: GL_SMOOTH);
	// Material property: shininess of the objects
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

	// Configure fog
	configureFog(fog, fogMode, PROJECTION_FAR);

	// Lights stay at the same place when configured before gluLookAt
	if(lightsLocked) {
		printf("Lights locked\n");
		configureLights(ambientLight, diffuseLight, specularLight, spotLight, spotAngle, spotExponent, spotHeight, lightsPosition);
	}
	/*
	Set the position of the observer
		- xLens, yLens, zLens: position of the eye point
		- xRef, yRef, zRef: position of the reference point
		- xVW, yVW, zVW: direction of the up vector (points to the upper side of the view)
		  see https://stackoverflow.com/questions/10635947/what-exactly-is-the-up-vector-in-opengls-lookat-function
	*/
	gluLookAt(xLens, yLens, zLens, xRef, yRef, zRef, xVW, yVW, zVW);
	if(!lightsLocked) {
		printf("Lights unlocked\n");
		configureLights(ambientLight, diffuseLight, specularLight, spotLight, spotAngle, spotExponent, spotHeight, lightsPosition);
	}

	// Draw all static parts first (saves 1x glPushMatrix and glPopMatrix to increase performance)
	// Draw axes in the view
	drawAxes(axes);

	// Elements where the lights will affect their appearence
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
		// Draw solid finish before blending functions are activated
		drawFinish(wireFrame, finishAmbient, finishDiffuse, finishSpecular, textureAddressing, texture, checkpoints);

		// Make sure the cars are in the center of the finish
		competition? glTranslatef(animationCarTranslation, 0.0, -1.125): glTranslatef(animationCarTranslation, 0.0, -0.125);

		// soapbox car 1
		drawSuspension(wireFrame, suspensionAmbient, suspensionDiffuse, suspensionSpecular);
		drawTires(wireFrame, animationWheelsAngle, textureAddressing, texture);
		drawCoachwork(wireFrame, coachworkAmbient, coachworkDiffuse, coachworkSpecular, clear, checkpoints, textureAddressing, texture);

		// soapbox car 2 (if enabled)
		if(competition) {
			glTranslatef(0.0, 0.0, 2.25); // 1.0 space between the cars
			drawSuspension(wireFrame, suspensionAmbient, suspensionDiffuse, suspensionSpecular);
			drawTires(wireFrame, animationWheelsAngle, textureAddressing, texture);
			drawCoachwork(wireFrame, coachworkAmbient, coachworkDiffuse, coachworkSpecular, clear, checkpoints, textureAddressing, texture);
		}
	glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);

	// Swap the buffers (animation) and flush
	glutSwapBuffers();
	glFlush();
}

// OpenGL callback: reshape function
/*
 * GLint newWidth: new window width
 * GLint newHeight: new window height
 */
void windowFunction(GLint newWidth, GLint newHeight)
{
	GLdouble border;
	glMatrixMode(GL_PROJECTION); // Projection matrix mode, no projection functions in GL_MODELVIEW!
	glLoadIdentity(); // Load identity matrix in GL_PROJECTION matrix

	// Projection mode
	switch(projectionMode)
	{
		// Orthogonal perspective
		case 'o':
				glOrtho(PROJECTION_XMIN, PROJECTION_XMAX, PROJECTION_YMIN, PROJECTION_YMAX, PROJECTION_NEAR, PROJECTION_FAR);
				break;
		// Symmetric perspective
		case 's':
				border = PROJECTION_NEAR*tan(M_PI*(PROJECTION_ANGLE/2.0)/180.0); // Radians!
				glFrustum(-border, border, -border, border, PROJECTION_NEAR, PROJECTION_FAR);
				break;
		// Default: General perspective
		default:
		case 'g':
				// 2nd argument = aspect ratio = width/height
				gluPerspective(PROJECTION_ANGLE, PROJECTION_ASPECT_RATIO, PROJECTION_NEAR, PROJECTION_FAR);
				break;
	}

	// 0,0 the lower left corner of the viewport rectangle in pixels
	glViewport(0, 0, newWidth, newHeight);
}

// Main loop
/*
 * int argc: number of arguments
 * char* argv[]: arguments
 */
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
	glutInitWindowPosition(100, 100); // 100 pixels from the top and from the left
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Soapbox car");
    init();
	glutKeyboardFunc(keyboardWatcher);
	glutReshapeFunc(windowFunction);
	glutDisplayFunc(displayFunction);
	glutTimerFunc(ANIMATION_SPEED, animation, 0);
	glutMainLoop();
}
