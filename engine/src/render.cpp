#include <demoengine.hpp>
#include <stb_image.h>
#include <logSystem.hpp>
#include <render.hpp>


GLfloat vertices[] = {
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Upper corner
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Upper corner
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f // Lower right corner
};
GLuint verticesid[] =
{
  0,1,2,
  1,2,3
};

int SCREEN_HEIGHT = 500;
int SCREEN_WIDTH = 500;
GLuint shaderProgram;
int vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");

struct arr_buf {
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
};


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
void clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}
void swap(GLFWwindow* window) {
	glfwSwapBuffers(window);
}
void draw(float x, float y, GLuint VAO, GLuint IBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void color(float r, float g, float b, float a) {
	glUniform4f(vertexColorLocation,r,g,b,a);
}
void draw_init(GLuint _shaderProgram) {
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
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
	if ((error = glGetError()) != 0)
	{
		print(LogType::error, "Can't load shader");
	};

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if ((error = glGetError()) != 0)
	{
		print(LogType::warn, "Can't delete unused shaders");
	};
}
void Shaders_init(GLuint _shaderProgram) {
	shaderProgram = _shaderProgram;
}

unsigned char* Textures_load(const char* str, int& width, int& height, int& nmc) {
	unsigned char* image;
	image = stbi_load(str, &width, &height, &nmc, 0);
	return image;
}
int Textures_del(const GLuint* textureind) {
	glDeleteTextures(1, textureind);
	return glGetError();
}
int Textures_active(GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	return glGetError();
}
int Textures_generate(unsigned char* image, int width, int height, int nmc) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, nmc == 3 ? GL_RGB : GL_RGBA, width, height, 0, nmc == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

int render_init()//int argc, char* args[] )
{
    glfwInit();
    glfwSetTime(0.0f);
    GLFWwindow* window = glfwCreateWindow(500, 500, "What_make_me_a_good_demoman?", NULL, NULL);;
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	//GL_ONE_MINUS_CONSTANT_COLOR
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
	return glGetError();
}
void close_win(GLFWwindow* window) {
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
}