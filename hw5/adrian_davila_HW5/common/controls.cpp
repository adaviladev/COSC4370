#include <iostream>
// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

						   // Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::mat4 ModelMatrix = glm::mat4(1.0);

glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}
glm::mat4 getModelMatrix() {
	return ModelMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3(0, 0, 5);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;



void computeMatricesFromInputs(GLFWwindow* window, int key, int scancode, int action, int mods) {
	cout << key << endl;
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_1) {
			ProjectionMatrix = ortho(-24.0f, 24.0f, -18.0f, 18.0f, 1.0f, 500.0f);
			ViewMatrix = lookAt(
				vec3(10, 500, 100), // Camera is at (0, 0, 10), in World Space
				vec3(0, 0, 0), // and looks at the origin
				vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
		}
		else if (key == GLFW_KEY_2) {
			ProjectionMatrix = perspective(radians(50.0f), 4.0f / 3.0f, 1.0f, 50.0f);
			ViewMatrix = lookAt(
				vec3(3, 3, 3), // Camera is at (0, 10, 0), in World Space
				vec3(0, 0, 0), // and looks at the origin
				vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
		}
		else if (key == GLFW_KEY_3) {
			ProjectionMatrix = ortho(-2.4f, 2.4f, -1.8f, 1.8f, 1.0f, 50.0f);
			ViewMatrix = lookAt(
				vec3(10, 10, 10), // Camera is at (0, 0, 10), in World Space
				vec3(0, 0, 0), // and looks at the origin
				vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
		}
		else if (key == GLFW_KEY_4) {
			ProjectionMatrix = perspective(radians(50.0f), 4.0f / 3.0f, 1.0f, 50.0f);
			ViewMatrix = lookAt(
				vec3(3, 3, 3), // Camera is at (0, 10, 0), in World Space
				vec3(0, 0, 0), // and looks at the origin
				vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
		}
	}
}