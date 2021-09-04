
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

struct arr_buf;

struct arr_buf* create_obj(const void* vertices, const void* verticesid);
void clear();
void swap(void* window);
void draw(float x, float y, arr_buf* arr);
void color(float r, float g, float b, float a);
void draw_init();
void shaders_load(const char* vertexShaderSource, const char* fragmentShaderSource);
void Shaders_init(unsigned int _shaderProgram);
unsigned char* Textures_load(const char* str, int& width, int& height, int& nmc);
int Textures_del(const unsigned int* textureind);
int Textures_active(unsigned int texture);
int Textures_generate(unsigned char* image, int width, int height, int nmc);
void* render_init();
void close_win(void* window);