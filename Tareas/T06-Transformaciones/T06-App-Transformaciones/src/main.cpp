//============================================================================
// Name        : Move color with object
// Professor   : Herminio Paucar
// Version     :
// Description :
//============================================================================

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

float curAngle = 0.0f;
void drawCircles(GLfloat x,GLfloat y,GLfloat z,GLfloat r,GLfloat g,GLfloat b, GLfloat radius, GLfloat matriz[]){
	GLint numberOfSides = 50;
	GLint numberOfVertices = numberOfSides + 2;
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
			//cout<<" P["<<i<<"]"<<": ("<<verticesX[i]<<","<<verticesY[i]<<","<<verticesZ[i]<<") \n";
    }

	//matriz[dimVertices];

	for (int i = 0; i < numberOfVertices; i++) {
			matriz[i * 6] = verticesX[i];
			matriz[i * 6 + 1] = verticesY[i];
			matriz[i * 6 + 2] = verticesZ[i];
			matriz[i * 6 + 3] = r;
			matriz[i * 6 + 4] = g;
			matriz[i * 6 + 5] = b;
			//cout<<" P["<<i<<"]"<<": ("<<matriz[i * 6]<<","<<matriz[i * 6+1]<<","<<matriz[i * 6+2]<<") \n";
		}
	//return matriz;
}

void drawQuarter(GLfloat x,GLfloat y,GLfloat z,GLfloat r,GLfloat g,GLfloat b, GLfloat radius, GLfloat matriz[]){
	GLint numberOfSides = 50;
	GLint numberOfVertices = numberOfSides + 2;
	GLfloat twicePi = 2.0f * M_PI;

	GLfloat verticesX[numberOfVertices];
	GLfloat verticesY[numberOfVertices];
	GLfloat verticesZ[numberOfVertices];

	verticesX[0] = x;
	verticesY[0] = y;
	verticesZ[0] = z;

	//Creo los puntos
	for (int i = 1; i < numberOfVertices/4; i++) {
			verticesX[i] = x + (radius * cos(i * twicePi / numberOfSides));
			verticesY[i] = y + (radius * sin(i * twicePi / numberOfSides));
			verticesZ[i] = z;
			//cout<<" P["<<i<<"]"<<": ("<<verticesX[i]<<","<<verticesY[i]<<","<<verticesZ[i]<<") \n";
    }

	//matriz[dimVertices];

	for (int i = 0; i < numberOfVertices; i++) {
			matriz[i * 6] = verticesX[i];
			matriz[i * 6 + 1] = verticesY[i];
			matriz[i * 6 + 2] = verticesZ[i];
			matriz[i * 6 + 3] = r;
			matriz[i * 6 + 4] = g;
			matriz[i * 6 + 5] = b;
			//cout<<" P["<<i<<"]"<<": ("<<matriz[i * 6]<<","<<matriz[i * 6+1]<<","<<matriz[i * 6+2]<<") \n";
		}
	//return matriz;
}

void init (GLFWwindow* window) {

	// Utils
	renderingProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");

	// Cria um ID na GPU para um array de  buffers
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	GLint dimVertices = 52*6;

	//Dibujando circulo negro de fondo
	GLfloat circle0[dimVertices];
			drawCircles(0.0,0.0,0.0,0.0,0.0,0.0,0.85,circle0);
	GLfloat circlea[dimVertices];
			drawCircles(0.0,0.0,0.0,0.68,0.05,0.0,0.8,circlea);

	//Dibujando circulo central
	GLfloat circle1[dimVertices];
			drawCircles(0.0,0.0,0.0,0.0,0.0,0.0,0.07,circle1);
	//Dibujando circulo de arriba
			GLfloat circle2[dimVertices];

			drawCircles(0.0,0.5,0.0,0.0,0.0,0.0,0.1,circle2);
	//Dibujando circulo de izquierda
			GLfloat circle3[dimVertices];
			drawCircles(-0.4,-0.3,0.0,0.0,0.0,0.0,0.1,circle3);
	//Dibujando circulo de la derecha
			GLfloat circle4[dimVertices];
    		 drawCircles(0.4,-0.3,0.0,0.0,0.0,0.0,0.1,circle4);
    // Vertex and color of Triangles
    n_Vertices = 52*6*6;
	m_Vertices = new GLfloat[n_Vertices];

	for (int i = 0; i < 52*6; i++) {
		m_Vertices[i] = circle0[i];
		m_Vertices[i + 52*6] = circlea[i];
		m_Vertices[i + 52*6*2] = circle1[i];
		m_Vertices[i + 52*6*3] = circle2[i];
		m_Vertices[i + 52*6*4] = circle3[i];
		m_Vertices[i + 52*6*5] = circle4[i];

	}


	/*************************************************************/

	// Cria um ID na GPU para nosso buffer
	glGenBuffers(1, &m_VBO);

	// Cria um ID na GPU para um array de  buffers
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Reserva memoria na GPU para um TARGET receber dados
	// Copia esses dados pra essa área de memoria
	glBufferData(
			GL_ARRAY_BUFFER,	// TARGET associado ao nosso buffer
			n_Vertices * sizeof(GLfloat),	// tamanho do buffer
			m_Vertices,			// Dados a serem copiados pra GPU
			GL_STATIC_DRAW		// Política de acesso aos dados, para otimização
		);

	glVertexAttribPointer(
			0,			// Lembra do (layout = 0 ) no vertex shader ? Esse valor indica qual atributo estamos indicando
			3,			// cada vertice é composto de 3 valores
			GL_FLOAT,	// cada valor do vértice é do tipo GLfloat
			GL_FALSE,	// Quer normalizar os dados e converter tudo pra NDC ? ( no nosso caso, já esta tudo correto, então deixamos como FALSE)
			6 * sizeof(GLfloat),// De quantos em quantos bytes, este atributo é encontrado no buffer ? No nosso caso 3 floats pros vertices + 3 floats pra cor = 6 floats
			(GLvoid*) 0	// Onde está o primeiro valor deste atributo no buffer. Nesse caso, está no início do buffer
		);
	glEnableVertexAttribArray(0);	// Habilita este atributo

	// Faremos a mesma coisa pra cor de cada vértice
	glVertexAttribPointer(
			1,			// Lembra do (layout = 1 ) no vertex shader ? Esse valor indica qual atributo estamos indicando
			3,			// cada vertice é composto de 3 valores
			GL_FLOAT,	// cada valor do vértice é do tipo GLfloat
			GL_FALSE,	// Quer normalizar os dados e converter tudo pra NDC ? ( no nosso caso, já esta tudo correto, então deixamos como FALSE)
			6 * sizeof(GLfloat),// De quantos em quantos bytes, este atributo é encontrado no buffer ? No nosso caso 3 floats pros vertices + 3 floats pra cor = 6 floats
			(GLvoid*) (3 * sizeof(GLfloat))	// Onde está o primeiro valor deste atributo no buffer. Nesse caso, 3 floats após o início do buffer
		);

	glEnableVertexAttribArray(1);		// Habilita este atributo

	glBindVertexArray(0);
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	GLuint uniformModel = glGetUniformLocation(renderingProgram, "model");

	curAngle += 0.5f;
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

	// Use este VAO e suas configurações
	glBindVertexArray(m_VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 12);
	 glDrawArrays(GL_TRIANGLE_FAN, 0, 52);
	 glDrawArrays(GL_TRIANGLE_FAN, 52 + 1, 52);
	 glDrawArrays(GL_TRIANGLE_FAN, 52*2 + 1, 52);
	 glDrawArrays(GL_TRIANGLE_FAN, 52*3 + 1, 52);
	 glDrawArrays(GL_TRIANGLE_FAN, 52*4 + 1, 52);
	 glDrawArrays(GL_TRIANGLE_FAN, 52*5 + 1, 52);
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
