
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float x = 0;
float y = 0;
int speed = 1;

int movement;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 TexCoord;\n"
"uniform vec4 rot; \n"
"uniform vec2 cmmove; \n"
"uniform float rot2; \n"
"out vec2 texcrd; \n"
"void main()\n"
"{\n"
"   texcrd = TexCoord"
"   float x = aPos.x*rot.x/2+aPos.x;\n"
"   float y = aPos.y*rot.y/2+aPos.y;\n"
"   float z = aPos.z*rot.z/2+aPos.z;\n"
"   if (rot2 < 360){\n"
"   gl_Position = vec4(x*cos(rot2/57.6)+z*sin(rot2/57.6), "
"					   y, "
"					   z*-1*sin(rot2/57.6)+z*cos(rot2/57.6), "
"	1.0);\n"
"	}else{\n"
"   if (rot2 < 720){\n"
"   gl_Position = vec4(x*cos(rot2/57.6)+y*-1*sin(rot2/57.6), "
"					   x*sin(rot2/57.6)+y*cos(rot2/57.6), "
"					   z, "
"	1.0);\n"
"	}\n"
"   else {\n"
"   gl_Position = vec4(x, "
"					   y*cos(rot2/57.6)+z*-1*sin(rot2/57.6), "
"					   y*sin(rot2/57.6)+z*cos(rot2/57.6), "
"	1.0);\n"
"	}}\n"
//"	gl_Position = vec4(gl_Position.x + cmmove.x, gl_Position.y + cmmove.y, gl_Position.z, 1.0f);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"in vec2 texcrd; \n"
"out vec4 FragColor;\n"
"uniform sampler2D textur;\n"
"uniform vec4 Color;\n"
"void main()\n"
"{\n"
"   FragColor = texture(textur, texcrd) * Color;\n"
"}\n\0";

void movexy(float xp, float yp, float way) {
	float tm = glfwGetTime();
	float xl = xp;
	float yl = yp;
	while (abs(xp - xl + yp - yl) < way) {
		xp += 0.1f * speed * (glfwGetTime()-tm);
	}
	glUniform2f(movement, x, y);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		movexy(0.1f, 0.0f, 1);
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		movexy(-0.1f, 0.0f, 1);
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		movexy(0.0f, 0.1f, 1);
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		movexy(0.0f, -0.1f, 1);
	}
}

GLuint VAO, VBO;
int main()
{
	glfwSetTime(0);
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(500, 500, "EBFSWT", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 500, 500);



	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	stbi_set_flip_vertically_on_load(true);
	int texwidth,texheigh,cnt;
	unsigned char *data = stbi_load("asas.PNG", &texwidth, &texheigh, &cnt, 0);

	glActiveTexture(GL_TEXTURE0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwidth, texheigh, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	glUseProgram(shaderProgram);
	// Sets the value of the uniform
	glUniform1i(glGetUniformLocation(shaderProgram, "textur"), 0);


	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // Upper corner
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // Upper corner
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Lower right corner
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Lower left corner
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // Upper corner
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // Upper corner
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Lower right corner
	};

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO


	movement = glGetUniformLocation(shaderProgram, "cmmove");
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	

	glUniform2f(movement, x, y);
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");
	int Magic = glGetUniformLocation(shaderProgram, "rot");
	int Magic2 = glGetUniformLocation(shaderProgram, "rot2");
	float i = 0;
	float j = 0;
	// Main while loop
	glUseProgram(shaderProgram);
	glEnable(GL_BLEND);
	//glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	//GL_ONE_MINUS_CONSTANT_COLOR
	glfwSetKeyCallback(window, key_callback);
	glClearColor(0.0f, 0.06f, 0.12f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		i = (i + 0.1f);
		if (i > 360) i = i - 360;
		j = (j + 0.2f);
		if (j > 1080) j = j - 1080;
		// Specify the color of the background
		//((sin(glfwGetTime() * 10) / 2.0f) + 0.5f)
		glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
		glUniform4f(Magic, sin(i/57.6), cos(i / 57.6), 1.0f, 1.0f);
		glUniform1f(Magic2, j);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 2, 3);
		// Swap the back buffer with the front buffer
		glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
		i = (i + 240);
		if (i > 360) i = i - 360;
		glUniform4f(Magic, sin(i / 57.6), cos(i / 57.6), 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 2, 3);
		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);
		i = (i + 240);
		if (i > 360) i = i - 360;
		glUniform4f(Magic, sin(i / 57.6), cos(i / 57.6), 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 2, 3);
		i = (i + 240);
		if (i > 360) i = i - 360;
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		std::cout << "A" << std::endl;
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}