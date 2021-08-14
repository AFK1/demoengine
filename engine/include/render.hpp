#include <swt.hpp>

class Draw
{
public:
	int create_obj(const void* vertices, const void* verticesid);
	int clear();
	int rect(float x, float y, GLuint VAO, GLuint IBO);

	Draw(GLuint _shaderProgram);
private:
	GLuint shaderProgram;
	int smeshenie;
	int vertexColorLocation;
};

class Shaders
{
public:
	int error;
	int load(const char * vertexShaderSource, const char * fragmentShaderSource);
	Shaders(GLuint _shaderProgram);
private:
	GLuint shaderProgram;
	Log* logger;
};

class Textures
{
public:
	int error;
	unsigned char* load(const char* str, int& width, int& height, int& nmc);
	int del(const GLuint* textureind);
	int active(GLuint texture);
	int generate(unsigned char* image, int width, int height, int nmc);
	Textures(GLuint _shaderProgram);
private:
	GLuint shaderProgram;
	Log* logger;
};
