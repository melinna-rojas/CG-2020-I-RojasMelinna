//============================================================================
// Name        : EX01- Exercise Programming
// Professor   : Herminio Paucar
// Version     : 1.0
// Student     : Melinna Rojas
// Description : An application that shows a window with my fav color
//============================================================================

// Include standard headers
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

using namespace std;

int dimVertices;
int numberOfVertices;

void display(double currentTime) {
	// Clear the screen
	// Bright green background! - fav color
	glClearColor(0.4f, 1.0f, 0.0f, 0.0f);
	glClear( GL_COLOR_BUFFER_BIT);
}

int main( void ){
	// Initialise GLFW
	if (!glfwInit()) { exit(EXIT_FAILURE);}

	//Stablishing version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(800, 800, "Rojas Camargo, Melinna", NULL, NULL);

	//Make it my current window
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {exit(EXIT_FAILURE);	}

	// Check if the window was closed
	while (!glfwWindowShouldClose(window)) {
		display(glfwGetTime());
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

