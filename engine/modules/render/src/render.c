#include <render.h>
#include <stdio.h>

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

void render_init(int _SCREEN_WIDTH; int _SCREEN_HEIGHT) {
	SCREEN_WIDTH = _SCREEN_WIDTH;
	SCREEN_HEIGHT = _SCREEN_HEIGHT;

};

void close_win(GLFWwindow* window) {
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
}