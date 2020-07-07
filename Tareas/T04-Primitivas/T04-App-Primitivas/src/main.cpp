//Learning how to use EBO
//Melinna Rojas Camargo

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLM
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Include GLEW
#define GLEW_STATIC
#include <GL\glew.h>

// Include GLFW
#include <GLFW\glfw3.h>

using namespace std;

GLuint renderingProgram;

GLuint m_VBO;
GLuint m_VAO;
GLuint m_EBO;

using namespace std;

GLuint createShaderProgram() {
    // declares two shaders as character strings
    // Vertex Shader code
    static const char *vshaderSource =

    		"#version 330  \n"
    		"layout (location = 1) in vec3 vColor; \n"
            "layout (location = 0) in vec4 vPosition; \n"
			"out vec4 vertexColor; \n"
    		"void main() { \n"
    		"gl_Position = vPosition;\n "
    		"vertexColor = vec4(vColor,1.0);	\n"
    		"}";

    // Fragment Shader
    static const char *fshaderSource =
    		"#version 330  \n"
    		 "in vec4 vertexColor; \n"
    		"out vec4 fColor; \n"
    		"void main(){ \n"
    	    " fColor = vertexColor; \n"
    	    "}";

    
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    
    glCompileShader(vShader);
    glCompileShader(fShader);
    
   GLuint vfProgram = glCreateProgram();
    
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    
    glLinkProgram(vfProgram);
    
    return vfProgram;
}

void init (GLFWwindow* window) {
    renderingProgram = createShaderProgram();
    //Puntos base
    GLfloat vertices[] = {

    		//PUNTOS					//COLORES
    			0.4f, 0.8f, 0.0f,  1.0f, 0.75f, 0.0f,
    			0.3f, 0.2f, 0.0f,  1.0f, 0.75f, 0.0f,
    			0.8f, 0.2f, 0.0f,  1.0f, 0.75f, 0.0f,

    			-0.8f,0.8f,0.0f, 1.0f, 0.01f, 0.24f,
    			-0.8f,0.2f,0.0f,  1.0f, 0.01f, 0.24f,
    			-0.2f,0.2f,0.0f, 1.0f, 0.01f, 0.24f,


    			-0.5f,-0.2f,0.0f, 0.6f, 0.4f, 0.8f,
    			-0.2f,-0.8f,0.0f, 0.6f, 0.4f, 0.8f,
    			-0.8f,-0.8f,0.0f, 0.6f, 0.4f, 0.8f,

    			0.2f,-0.2f,0.0f, 0.0f, 1.1f, 1.1f,
    			0.8f,-0.2f,0.0f, 0.0f, 1.1f, 1.1f,
    			0.2f,-0.5f,0.0f, 0.0f, 1.1f, 1.1f,
    			//0.8f,-0.2f,0.0f, 0.6f, 0.5f, 0.1f,
    			//0.2f,-0.5f,0.0f, 0.6f, 0.5f, 0.1f,
    			0.8f,-0.5f,0.0f ,0.0f, 1.1f, 1.1f
        };

    GLuint indices[] = {
            0, 1, 2,   // first triangle
            3, 4, 5,    // second triangle
			6, 7, 8,    // third triangle
			9, 10, 11,    // first triangle 4 the rectangle
			10, 11, 12    // second triangle 4 the rectangle
        };

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	  //Creo un EBO para reutilizar mis puntos
	glGenBuffers(1,&m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat),0);
	glEnableVertexAttribArray(0);
	//Colores

	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat),(GLvoid*) (3 * sizeof(GLfloat))	);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_VAO);
}

void display(GLFWwindow* window, double currentTime) {
	  glUseProgram(renderingProgram);

		glBindVertexArray(m_VAO);
	    //glDrawArrays(GL_TRIANGLES, 0, 5*3);
		glDrawElements(GL_TRIANGLES, 15 //Numero de vertices a dibuujar
						, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
}

int main(void) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
