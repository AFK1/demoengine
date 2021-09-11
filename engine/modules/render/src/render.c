#include <render.h>
#include <stdio.h>
#include <stdlib.h>

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
unsigned int shaderProgram;

const char* vertexShaderSource =
"#version 300 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexcord;\n"
"out vec2 Texcord;\n"
"void main()\n"
"{\n"
"   Texcord = aTexcord;\n"
"   gl_Position = vec4(aPos.xyz,1.0f);\n"
"}\0";
const char* fragmentShaderSource =
"#version 300 core\n"
"in vec2 Texcord;\n"
"uniform vec4 Color; \n"
"uniform sampler2D texture;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = Color;\n" // texture(texture, Texcord);\n"
						  // //vec4(Texcord.xy, Color.zw);\n"//
"}\n\0";

GLfloat verticesst[] = {
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Upper corner
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Upper corner
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f // Lower right corner
};
GLuint verticesidst[] =
{
  0,1,2,
  1,2,3
};


struct arr_buf* create_obj_st() {
	return create_obj(verticesst, verticesidst);
}

struct arr_buf* create_obj(const void* vertices, const void* verticesid) {

	GLuint VAO, VBO, IBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(verticesid),
		verticesid,
		GL_STATIC_DRAW);

	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(float),
		(void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,
		2,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(float),
		(void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	struct arr_buf* arr = (struct arr_buf*)malloc(sizeof(struct arr_buf));

	arr->vao = VAO;
	arr->vbo = VBO;
	arr->ibo = IBO;

	return arr;
}

void draw(float x, float y, struct arr_buf *arr) {
	glBindVertexArray(arr->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arr->ibo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void shaders_load_st() {
	shaders_load(vertexShaderSource, fragmentShaderSource);
}

void shaders_load(const char* vertexShaderSource, const char* fragmentShaderSource) {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int error = 0;
	if (glGetError() != 0)
	{
		printf("Can't load shader");
	};

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(shaderProgram);
}

void swap_buf(GLFWwindow* window) {
	glfwSwapBuffers(window);
}
void clear_win() {
	glClear(GL_COLOR_BUFFER_BIT);
}

GLFWwindow* render_init(int _SCREEN_WIDTH, int _SCREEN_HEIGHT) {
	SCREEN_WIDTH = _SCREEN_WIDTH;
	SCREEN_HEIGHT = _SCREEN_HEIGHT;
	glfwInit();
	glfwSetTime(0.0f);
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "a?", NULL, NULL);//What_make_me_a_good_demoman
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	//glEnable(GL_TEXTURE_2D);
	//glMatrixMode(GL_PROJECTION);  glLoadIdentity();
	glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);
	//glMatrixMode(GL_MODELVIEW);  glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);//GL_ONE_MINUS_CONSTANT_COLOR
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
	shaderProgram = glCreateProgram();
	return window;
};

void close_win(GLFWwindow* window) {
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
}
