#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

void setup() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// space
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(-0.75f, 0.75f, 0.75f, -0.75f);
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hello World");

	setup();
	glutDisplayFunc(display);

	glutMainLoop();

	getchar();//pause here to see results or lack there of
	return 0;
}