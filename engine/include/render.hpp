
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

struct arr_buf {
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
};

struct arr_buf* create_obj(const void* vertices, const void* verticesid);
void clear();
void swap(GLFWwindow* window);
void draw(float x, float y, GLuint VAO, GLuint IBO);
void color(float r, float g, float b, float a);
void draw_init(GLuint _shaderProgram);
void shaders_load(const char* vertexShaderSource, const char* fragmentShaderSource);
void Shaders_init(GLuint _shaderProgram);
unsigned char* Textures_load(const char* str, int& width, int& height, int& nmc);
int Textures_del(const GLuint* textureind);
int Textures_active(GLuint texture);
int Textures_generate(unsigned char* image, int width, int height, int nmc);
GLFWwindow* render_init();
void close_win(GLFWwindow* window);