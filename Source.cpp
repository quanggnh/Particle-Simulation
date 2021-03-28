#include<GL/glut.h>
#include<map>
#include<glm/glm.hpp>
#include<string>
#include<tuple>
#include"Particle.h"
#include<math.h>
using namespace std;

// Initialize the Eye
map<string, GLfloat> Eye = {
	{"posX", 5.0f}, {"posY", 5.0f}, {"posZ", 5.0f},
	{"lookAtX", 0.0f}, {"lookAtY", 0.0f}, {"lookAtZ", 0.0f},
	{"upX", 0.0f}, {"upY", 1.0f}, {"upZ", 0.0f}
};

// Cube's edge length also boundaries of Eye's positions
GLfloat edgeLength = 10.0f;

// Create a sphere
// Its id is always 1
Particle ps = Particle(make_tuple(2.5f, 2.5f, 2.5f),
						make_tuple(224, 17, 95), 0.1f, 1);

GLfloat lowerBoundary = 0.1f;
GLfloat upperBoundary = edgeLength - lowerBoundary;

void limitEyePosition() {
	// Set lower boundary for x, y, z
	if (Eye["posX"] < lowerBoundary) Eye["posX"] = lowerBoundary;
	if (Eye["posY"] < lowerBoundary) Eye["posY"] = lowerBoundary;
	if (Eye["posZ"] < lowerBoundary) Eye["posZ"] = lowerBoundary;
	
	// Set upper boundary for x, y, z
	if (Eye["posX"] > upperBoundary) Eye["posX"] = upperBoundary;
	if (Eye["posY"] > upperBoundary) Eye["posY"] = upperBoundary;
	if (Eye["posZ"] > upperBoundary) Eye["posZ"] = upperBoundary;
}

float vertical = 0.0f;
float horizontal = 0.0f;
float deltahorizontal =0.0f;
float deltavertical = 0.0f;
float lx = lx = cos(horizontal)*cos(vertical);
float ly = sin(vertical);
float lz = sin(horizontal)*cos(vertical);
void computeHorizontal(float deltaAngle){	
	horizontal += deltaAngle;
	lx = cos(horizontal)*cos(vertical);
	lz = sin(horizontal)*cos(vertical);
}

void computeVertical(float deltaAngle){
	vertical += deltaAngle;
	ly = sin(vertical);
}
void drawWalls() {
	// Color source https://colorswall.com/palette/24609/

	glBegin(GL_QUADS);
	
	// Top face -y
	glColor3ub(119, 136, 153);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(edgeLength, 0.0f, 0.0f);
	glVertex3f(edgeLength, 0.0f, edgeLength);
	glVertex3f(0.0f, 0.0f, edgeLength);

	// South face z
	glColor3ub(133, 148, 163);
	glVertex3f(0.0f, 0.0f, edgeLength);
	glVertex3f(0.0f, edgeLength, edgeLength); 
	glVertex3f(edgeLength, edgeLength, edgeLength);
	glVertex3f(edgeLength, 0.0f, edgeLength);

	// East face x
	glColor3ub(146, 160, 173);
	glVertex3f(edgeLength, 0.0f, edgeLength);
	glVertex3f(edgeLength, edgeLength, edgeLength);
	glVertex3f(edgeLength, edgeLength, 0.0f);
	glVertex3f(edgeLength, 0.0f, 0.0f);

	// North face -z
	glColor3ub(160, 172, 184);
	glVertex3f(edgeLength, 0.0f, 0.0f);
	glVertex3f(edgeLength, edgeLength, 0.0f);
	glVertex3f(0.0f, edgeLength, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// West face -x
	glColor3ub(173, 184, 194);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, edgeLength);
	glVertex3f(0.0f, edgeLength, edgeLength);
	glVertex3f(0.0f, edgeLength, 0.0f);

	// Top face y
	glColor3ub(187, 196, 204);
	glVertex3f(0.0f, edgeLength, 0.0f);
	glVertex3f(edgeLength, edgeLength, 0.0f);
	glVertex3f(edgeLength, edgeLength, edgeLength);
	glVertex3f(0.0f, edgeLength, edgeLength);

	glEnd();
}


void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Put functions to draw and to move objects here
	drawWalls();
	ps.draw();
	ps.move(lowerBoundary, upperBoundary);

	glutSwapBuffers();
	glLoadIdentity();

	limitEyePosition();
	if(deltahorizontal){
		computeHorizontal(deltahorizontal);
	}
	if(deltavertical){
		computeVertical(deltavertical);
	}

	// This will make the eye follow the sphere
	// Eye["lookAtX"] = get<0>(ps.getPosition());
	// Eye["lookAtY"] = get<1>(ps.getPosition());
	// Eye["lookAtZ"] = get<2>(ps.getPosition());

	gluLookAt(Eye["posX"], Eye["posY"], Eye["posZ"],
	    Eye["posX"]+lx, Eye["posY"]+ly, Eye["posZ"]+lz,
		Eye["upX"], Eye["upY"], Eye["upZ"]);

}

void pressKey(int key, int x_mouse_pos, int y_mouse_pos){
	switch (key)
	{
	case GLUT_KEY_UP: // w key
		//code goes here
		deltavertical = 0.01f;
	case GLUT_KEY_DOWN: // a key
		//code goes here
		deltavertical = -0.01;
		break;
	case GLUT_KEY_LEFT: // s key
		//code goes here
		deltahorizontal = -0.01f;
		break;
	case GLUT_KEY_RIGHT: // d key
		//code goes here
		deltahorizontal = 0.01;
		break;
	default:
		break;
	}
}

void releaseKey(int key, int x_mouse_pos, int y_mouse_pos){
	switch (key)
	{
	case GLUT_KEY_UP: // w key
		//code goes here
		deltavertical = 0.0f;
	case GLUT_KEY_DOWN: // a key
		//code goes here
		deltavertical = 0.0f;
		break;
	case GLUT_KEY_LEFT: // s key
		//code goes here
		deltahorizontal = 0.0f;
		break;
	case GLUT_KEY_RIGHT: // d key
		//code goes here
		deltahorizontal	= 0.0f;
		break;
	default:
		break;
	}
}

void reshapeScene(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	gluPerspective(60, 1.0f, 1.0, 100);
	glMatrixMode(GL_MODELVIEW);
}

// This func is a para of glutKeyBoardFunc()
void keyboard(unsigned char key, int x_mouse_pos, int y_mouse_pos) {
	switch (key)
	{
	case 27: // ESC key
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	// Set color mode
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	// Set window width, height
	glutInitWindowSize(640, 640);

	// Set window position
	glutInitWindowPosition(0, 0);

	// Set Set window name
	glutCreateWindow("Particle Simulation");

	// Pass a function to draw
	glutDisplayFunc(renderScene);

	// Keep that function alive
	glutIdleFunc(renderScene);

	// Pass a function to handle the change of window
	glutReshapeFunc(reshapeScene);

	// Pass functions to handle keyboard events
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}