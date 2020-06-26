//============================================================================
// Name        : Exercise 02
// Professor   : Herminio Paucar
// Description : Drawing more than 1 point, using multidimensional arrays
// Student	   : Melinna Rojas
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

// Vertex Array Objects
GLuint VAO;
// Vertex Buffer Object
GLuint VBO;

int dimVertices;
int numberOfVertices;

void init(){
	// Create vertices
	dimVertices = 3;
	numberOfVertices = 13;

	GLfloat m_Vertices[numberOfVertices][dimVertices] =
	{
			//1ER CUADRANTE
			{0.25f,0.75f,0.0f},
			{0.75f,0.75f,0.0f},
			{0.5f,0.5f,0.0f},
			{0.25f,0.25f,0.0f},
			{0.75f,0.25f,0.0f},

			//2DO CUADRANTE
			{-0.75f,0.25f,0.0f},
			{-0.25f,0.25f,0.0f},
			{-0.75f,0.75f,0.0f},
			{0.0f,0.0f,0.0f},

			//3ER CUADRANTE
			{-0.5f,-0.5f,0.0f},

			//4TO CUANDRANTE
			{0.7f,-0.5f,0.0f},
			{0.6f,-0.6f,0.0f},
			{0.5f,-0.7f,0.0f}
	};


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(
			GL_ARRAY_BUFFER,
			numberOfVertices*dimVertices*sizeof(GLfloat),
			m_Vertices,
			GL_STATIC_DRAW
		);
}

void display(double currentTime) {
	// Clear the screen
	float m;
		if((int) currentTime % 3 == 0) {
			m = 0.0f;
		} else if ((int) currentTime % 3 == 1) {
			m =  1.0f;
		} else {
			m =  0.5f;
		}

	glClearColor(0.7f, m, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(
			0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
			dimVertices,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*) 0            // array buffer offset
	);

	glPointSize(20.0f);

	// Draw the primitive GL_POINTS
	glDrawArrays(GL_POINTS, 0, numberOfVertices); // 3 indices starting at 0 -> number of Vertex

	glDisableVertexAttribArray(0);

}

int main( void ){
	// Initialise GLFW
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(600, 600, "Rojas Camargo, Melinna", NULL, NULL);

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}

	// Ensure we can capture the escape key being pressed below
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	init();
	// Check if the window was closed
	while (!glfwWindowShouldClose(window)) {
		display(glfwGetTime());
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// Cleanup VBO
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

