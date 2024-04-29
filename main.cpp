#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Vertex Shader Source Code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.8f, 1.0f);\n"
"}\n\0";

int main()
{	//initialize GLFW
	glfwInit();

	//Tell GLFW what version of OPENGL we are using
	//In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW we are using the core profile
	//So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Vertex Coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3))  * 2 / 3, 0.0f,
		-0.5f/ 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f / 2, 0.5f * float(sqrt(3))/6,0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f

	};

	GLuint indices[] =
	{
		0,3,5,
		3,2,4,
		5,4,1
	};

	//Create a GLFW window object of 800 by 800 pixels, naming it OpenGL Practice 1
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Practice 1", NULL, NULL);

	//Error Check if winsow fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Introduce the window into the current context 
	glfwMakeContextCurrent(window); 

	//Load a Glad so it confugures OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGL in this window
	glViewport(0, 0, 800, 800);


	//Create vetex shader object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach vertex shader source code to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compile the vertex shader into machine code
	glCompileShader(vertexShader);


	//Create fragment shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach fragment shader source code to the vertex shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compile the vertex shader into machine code
	glCompileShader(fragmentShader);


	//Create shader program object and get its reference
	GLuint shaderProgram = glCreateProgram();
	//Attach the vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Wrap up/Link all the shaders together in the shader program
	glLinkProgram(shaderProgram);

	//Delete the now useless vetex and fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Create reference containers for teh vertex array object ane the vertex buffer object
	GLuint VAO, VBO, EBO;

	//Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Make the VAO the current vertex array object by binding it
	glBindVertexArray(VAO);

	//Bind the VBO specifying its a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Confgure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	//Bind both the VBO and VAO to 0 so that we dont accidentally modify it
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	



	//Specify the color of the background
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	//Swap the back buffer with the front buffer
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

#
	//MAIN WHILE LOOP
	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//Draw the triangles using the GL_TRIANLES primitve
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);


		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Delete all we"ve created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	 //Delete window before closing the program
	glfwDestroyWindow(window);
	//Terminate the GLFW before closing OpenGL
	glfwTerminate();
	return 0;
}