#pragma once
#include<GL/glut.h>
class Cube
{
private:
	GLfloat edgeLength;
public:
	Cube(GLfloat edgeLength) {
		this->edgeLength = edgeLength;
	}

	void draw() {
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
};

