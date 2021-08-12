#include <swt.hpp>
#include <stb_image.h>
#include <log.hpp>


//=======================Global init==========================
GLFWwindow* window;
GLuint VAO, VBO, IBO;

GLfloat vertices[] =
{
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // Upper corner
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Lower left corner
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // Upper corner
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f // Lower right corner
};
GLuint verticesid[] =
{
	0,1,2,
	1,2,3
};

GLuint shaderProgram;
unsigned char* image;
int width, height, numColCh;
GLuint texture;
//=============================================================


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexcord;\n"
"uniform vec4 rot; \n"
"uniform float rot2; \n"
"out vec2 Texcord;\n"
"void main()\n"
"{\n"
"   float x = aPos.x*rot.x/2+aPos.x;\n"
"   float y = aPos.y*rot.y/2+aPos.y;\n"
"   float z = aPos.z*rot.z/2+aPos.z;\n"
"   float cs = cos(rot2/57.6),sn = sin(rot2/57.6);\n"  
"   Texcord = aTexcord;\n"
"   if (rot2 <= 360){\n"
"   gl_Position = vec4(x*cs+z*sn, "
"					   y, "
"					   z*-1*sn+z*cs, "
"	1.0);\n"
"	}else{\n"
"   if (rot2 <= 720){\n"
"   gl_Position = vec4(x*cs+y*-1*sn, "
"					   x*sn+y*cs, "
"					   z, "
"	1.0);\n"
"	}\n"
"   else {\n"
"   gl_Position = vec4(x, "
"					   y*cs+z*-1*sn, "
"					   y*sn+z*cs, "
"	1.0);\n"
"	}}\n"
//"	gl_Position = vec4(gl_Position.x + sin(gl_Position.y*400) ,gl_Position.yzw);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"in vec2 Texcord;\n"
"uniform vec4 Color; \n"
"uniform sampler2D texture;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = Color;\n"//texture(texture, Texcord);\n" //vec4(Texcord.xy, Color.zw);\n"//
"}\n\0";

void read_shader_file(const char* vertexPath, const char* fragmentPath) {
	const char* vertexCode;
	const char* fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);
	std::stringstream vShaderStream, fShaderStream;
	vShaderStream << vShaderFile.rdbuf();                               //To be modified
	fShaderStream << fShaderFile.rdbuf();
	vShaderFile.close();
	fShaderFile.close();
	vertexCode = vShaderStream.str().c_str();
	fragmentCode = fShaderStream.str().c_str();
	const GLchar* vertexShaderSource = vertexCode;
	const GLchar* fragmentShaderSource = fragmentCode;  // TODO: return shaders sources 
}

void window_init() {
	glfwSetTime(0.0f);
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(500, 500, "EBFSWT", NULL, NULL);            //Not to be modified
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glViewport(0, 0, 500, 500);
}

void load_shaders() {
	read_shader_file("shader.vert", "shader.frag");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);                                          //Not to be modified (I hope)
	glDeleteShader(fragmentShader);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verticesid), verticesid, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void load_texture() {
	image = stbi_load("container.jpg", &width, &height, &numColCh, 0);               //Not to be modified
}

void gen_texture() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, numColCh == 3 ? GL_RGB : GL_RGBA, width, height, 0, numColCh == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);                                                      //Not to be modifiedn

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


int entrypoint()
{
	Log * log = Log::getInstance();
	log->set_error_type(LogType::warn);
	window_init();
	load_shaders();
	load_texture();
	gen_texture();
	log->print("Test");

	int vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");
	int Magic = glGetUniformLocation(shaderProgram, "rot");
	int Magic2 = glGetUniformLocation(shaderProgram, "rot2");
	float i = 0, j = 0;
	glUseProgram(shaderProgram);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	//GL_ONE_MINUS_CONSTANT_COLOR
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
	float t = 0;
	while (!glfwWindowShouldClose(window))
	{
		i = (i + (glfwGetTime()-t)*40);j = (j + (glfwGetTime()-t)*80);if (i > 360) { i -= 360; }; if (j > 1080) { j -= 1080; }
		t = glfwGetTime();
		glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);glUniform4f(Magic, sin(i / 57.6), cos(i / 57.6), 1.0f, 1.0f);glUniform1f(Magic2, j);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);i = (i + 240);if (i > 360) { i -= 360; };glUniform4f(Magic, sin(i / 57.6), cos(i / 57.6), 1.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);i = (i + 240);if (i > 360) { i -= 360; };glUniform4f(Magic, sin(i / 57.6), cos(i / 57.6), 1.0f, 1.0f); 

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		i = (i + 240);if (i > 360) { i -= 360; };
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
