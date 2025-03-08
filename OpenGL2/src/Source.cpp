#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 Position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(Position, 1.0);"
"}\n";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.2f, 0.2f, 0.7f, 1.0f);"
"}\n";

const char* vertexShaderSource2 =
"#version 330 core\n"
"layout (location = 0) in vec3 Position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(Position, 1.0);"
"}\n";

const char* fragmentShaderSource2 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.2f, 0.1f, 1.0f);"
"}\n";


int main()
{


	if (!glfwInit()) {
		return -1;
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Test", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD Initialisation Failed";
		return -1;
	}

	float vertices[] = {
		-0.5, 0.7, 0.0,
		0.5, -0.7, 0.0,
		-0.5, -0.7, 0.0
	};
	float vertices2[] = {
		0.5, -0.7, 0.0,
		-0.5, 0.7, 0.0,
		0.5, 0.7, 0.0
	};

	unsigned int VBO, VAO;
	unsigned int  VBO2, VAO2;
	unsigned int vertexShader, fragmentShader;
	unsigned int vertexShader2, fragmentShader2;
	
	
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glad_glEnableVertexAttribArray(0);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glCompileShader(vertexShader2);
	glCompileShader(fragmentShader2);


	unsigned int shaderProgram = glCreateProgram();
	unsigned int shaderProgram2 = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glAttachShader(shaderProgram2, vertexShader2);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);



	int successvert;
	int successfrag;
	int successProg;

	char infolog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successvert);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successfrag);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successProg);

		if (window == NULL) {
			std::cout << "GLFW Window Creation Failed";
			glfwTerminate();
			return -1;
		}


	if (!successvert) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "Vertex Shader compilation Failed" << infolog;
	}
	else if (!successfrag) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "Fragment Shader Compilation Failed" << infolog;
	}
	else if (!successProg) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << "Shader Program Failed" << infolog;
	}






	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.5f, 0.3f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		//render here
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		



		glfwSwapBuffers(window);
		glfwPollEvents();


	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glfwTerminate();
	return 0;
}