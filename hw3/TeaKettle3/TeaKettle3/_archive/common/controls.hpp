#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs(GLFWwindow* window, int key, int scancode, int action, int mods);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::mat4 getModelMatrix();

#endif