// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include "Utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

const float toRadians = 3.14159265f / 180.0f;

GLuint renderingProgram;

GLfloat* m_Vertices;
GLuint n_Vertices;
GLuint m_VBO;
GLuint m_VAO;
//Para crear mis circulos
GLint numberOfSides = 1000;
GLint numberOfVertices = numberOfSides + 2;

float curAngle = 0.0f;

void drawCircles(GLfloat x,GLfloat y,GLfloat z,GLfloat r,GLfloat g,GLfloat b, GLfloat radius, GLfloat matriz[]){

	GLfloat twicePi = 2.0f * M_PI;

	GLfloat verticesX[numberOfVertices];
	GLfloat verticesY[numberOfVertices];
	GLfloat verticesZ[numberOfVertices];

	verticesX[0] = x;
	verticesY[0] = y;
	verticesZ[0] = z;

	//Creo los puntos
	for (int i = 1; i < numberOfVertices; i++) {
			verticesX[i] = x + (radius * cos(i * twicePi / numberOfSides));
			verticesY[i] = y + (radius * sin(i * twicePi / numberOfSides));
			verticesZ[i] = z;
    }


	//Acá relleno la matriz con los puntos creados en la otra funcion
	for (int i = 0; i < numberOfVertices; i++) {
			matriz[i * 6] = verticesX[i];
			matriz[i * 6 + 1] = verticesY[i];
			matriz[i * 6 + 2] = verticesZ[i];
			matriz[i * 6 + 3] = r;
			matriz[i * 6 + 4] = g;
			matriz[i * 6 + 5] = b;
		}

}

void init (GLFWwindow* window) {

	renderingProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	GLint dimVertices = numberOfVertices*6;

	//Dibujando circulo negro de fondo
	GLfloat circle0[dimVertices];
	drawCircles(0.0,0.0,0.0,0.0,0.0,0.0,0.81,circle0);

    //Circulo blanco(ojo, usaré solo la mitad)
	GLfloat circlea[dimVertices];
	drawCircles(0.0,0.0,0.0,1.0,1.0,1.0,0.8,circlea);

	//Dibujando circulo blanco, radio 0.4
	GLfloat circle1[dimVertices];
	drawCircles(0.4,0.0,0.0,1.0,1.0,1.0,0.4,circle1);

	//Dibujando circulo negro, radio 0.4
	GLfloat circle2[dimVertices];
	drawCircles(-0.4,0.0,0.0,0.0,0.0,0.0,0.4,circle2);

	//Dibujando circulo blanco pequeño
	GLfloat circle3[dimVertices];
	drawCircles(-0.4,0.0,0.0,1.0,1.0,1.0,0.1,circle3);

	//Dibujando circulo negro pequeño
	GLfloat circle4[dimVertices];
	drawCircles(0.4,0.0,0.0,0.0,0.0,0.0,0.1,circle4);

    // Vertex and color of Triangles
    n_Vertices = numberOfVertices*6*6;
	m_Vertices = new GLfloat[n_Vertices];

	//Acá uno todo en el arreglo que va al VAO
	for (int i = 0; i < numberOfVertices*6; i++) {
		m_Vertices[i] = circle0[i];
		m_Vertices[i + numberOfVertices*6] = circlea[i];
		m_Vertices[i + numberOfVertices*6*2] = circle1[i];
		m_Vertices[i + numberOfVertices*6*3] = circle2[i];
		m_Vertices[i + numberOfVertices*6*4] = circle3[i];
		m_Vertices[i + numberOfVertices*6*5] = circle4[i];
	}


	glGenBuffers(1, &m_VBO);

	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER,n_Vertices * sizeof(GLfloat),m_Vertices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,	GL_FALSE,6 * sizeof(GLfloat),(GLvoid*) 0);
	glEnableVertexAttribArray(0);

	//VAO para los colores
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat),(GLvoid*) (3 * sizeof(GLfloat))	);

	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void display(GLFWwindow* window, double currentTime) {

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	GLuint uniformModel = glGetUniformLocation(renderingProgram, "model");

	curAngle += 1.0f;
	if (curAngle >= 360)
	{
		curAngle -= 360;
	}

	// Matriz con elementos de valor 1
	glm::mat4 model(1.0f);
	//Giro Antihorario
	model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

	//Usando UniformMatrix
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));


	glBindVertexArray(m_VAO);

	 glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	 glDrawArrays(GL_TRIANGLE_FAN, numberOfVertices + 1, numberOfVertices/2); //Solo quiero medio circulo blanco unu
	 glDrawArrays(GL_TRIANGLE_FAN, numberOfVertices*2 + 1, numberOfVertices);
	 glDrawArrays(GL_TRIANGLE_FAN, numberOfVertices*3 + 1, numberOfVertices);
	 glDrawArrays(GL_TRIANGLE_FAN, numberOfVertices*4 + 1, numberOfVertices);
	 glDrawArrays(GL_TRIANGLE_FAN, numberOfVertices*5 + 1, numberOfVertices);

	glBindVertexArray(0);
	glUseProgram(0);
}

int main(void) {
    if (!glfwInit()) {
    	exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            //
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.

    GLFWwindow* window = glfwCreateWindow(600, 600, "Rojas Camargo, Melinna", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
    	exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
