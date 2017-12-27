#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Core/Shader_Loader.h"
#include "Core/GameModels.h"

using namespace Core;
using namespace std;

Models::GameModels* gameModels;
GLuint program;

vector<VertexFormat> vertexHolder;

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.39465, 0.39465, 0.50);

	glBindVertexArray(gameModels->GetModel("triangle1"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, vertexHolder.size());
	glutSwapBuffers();
}

void closeCallback()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void init()
{
		glEnable(GL_DEPTH_TEST);

		gameModels = new Models::GameModels();
		gameModels->CreateTriangleModel("triangle1", vertexHolder);

		Core::Shader_Loader shaderLoader;
		program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl", "Shaders\\Fragment_Shader.glsl");

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void readTrisFile() {
	string fileName = "Tris.txt";
	fstream fin(fileName.c_str());
	string txtLine;

	int ctr = 0;
	getline(fin, txtLine);
	int polygonCount = atoi(txtLine.c_str());
	while (getline(fin, txtLine) && ctr < polygonCount) {
		if (txtLine == "") {
			continue;
		}
		float x, y, z, r, g, b, a;
		stringstream ss;
		for (int i = 0; i < 3; i++) {
			ss << txtLine << endl;
			ss >> x;
			ss >> y;
			ss >> z;
			ss >> r;
			ss >> g;
			ss >> b;
			ss >> a;

			glm::mat3x3 matrix = glm::mat3x3({ 0, 0, 10 }, 
											 { 0, 0,  0 }, 
											 { 0, 1,  0 });
			glm::vec3 position = glm::vec3(x, y, z);
			glm::vec3 newPosition = matrix * position;
			vertexHolder.push_back(VertexFormat(newPosition,
												glm::vec4(r, g, b, a)));
		}
		ctr++;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");
	glewInit();
	if (glewIsSupported("GL_VERSION_4_4")) //lower your version if 4.5 is not supported by your video card
	{
		std::cout << " OpenGL Version is 4.4\n ";
	}
	else
	{
		std::cout << "OpenGL 4.4 not supported\n ";
	}

	readTrisFile();

	init();

	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);

	glutMainLoop();

	delete gameModels;
	glDeleteProgram(program);

	return 0;
}