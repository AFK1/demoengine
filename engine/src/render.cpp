#include <swt.hpp>
#include <stb_image.h>
#include <log.hpp>

class Draw
{
public:
	int create_obj(const void* vertices, const void* verticesid) {

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
		return VAO, VBO, IBO;
	}
	int clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	int sqrt(float x, float y, GLuint VAO, GLuint IBO) {
		glUniform2f(smeshenie, x, y);
		glUniform4f(vertexColorLocation,
			0.0f,
			1.0f,
			0.0f,
			1.0f);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	Draw(GLuint _shaderProgram) {
		shaderProgram = _shaderProgram;
		smeshenie = glGetUniformLocation(shaderProgram, "Pos");
		vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");
	}
private:
	GLuint shaderProgram;
	int smeshenie;
	int vertexColorLocation;
};

class Shaders
{
public:
	int error = 0;
	int load(const GLchar const*& vertexShaderSource, const GLchar const*& fragmentShaderSource) {
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

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
	Shaders(GLuint _shaderProgram) {
		shaderProgram = _shaderProgram;
	}
private:
	GLuint shaderProgram;
};
	
class Textures
{
public:
	int error = 0;
	unsigned char* load(const char* str, int& width, int& height, int& nmc) {
		unsigned char* image;
		image = stbi_load(str, &width, &height, &nmc, 0);
		return image;
	}
	int del(const GLuint* textureind) {
		glDeleteTextures(1, textureind);
		if (!(error = glGetError())) return 0; else return error;
	}
	int active(GLuint texture) {
		glBindTexture(GL_TEXTURE_2D, texture);
		if (!(error = glGetError())) return 0; else return error;
	}
	int generate(unsigned char* image, int width, int height, int nmc) {
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
	Textures(GLuint _shaderProgram) {
		shaderProgram = _shaderProgram;
	}
private:
	GLuint shaderProgram;
};


int main() {
	GLuint shaderProgram = glCreateProgram();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	//GL_ONE_MINUS_CONSTANT_COLOR
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

	Draw* draw = new Draw(shaderProgram);
	Shaders* shaders = new Shaders(shaderProgram);
	Textures* textures = new Textures(shaderProgram);
}
