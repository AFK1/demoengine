#ifndef __DEMO_M_RENDER_H_
#define __DEMO_M_RENDER_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

struct arr_buf {
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
};

struct arr_buf* create_obj_st();
struct arr_buf* create_obj(const void* vertices, const void* verticesid);
void draw(float x, float y, struct arr_buf* arr);
void shaders_load_st();
void shaders_load(const char* vertexShaderSource, const char* fragmentShaderSource);
void swap_buf(void* window);
void clear_win();
void render_init();
void close_win(void* window);

#endif // __DEMO_M_RENDER_H_


