#include <swt.hpp>
#include <stb_image.h>
#include <log.hpp>
#include <render.hpp>


struct arr_buf * Draw::create_obj(const void* vertices, const void* verticesid){

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
int Draw::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
	return 0;
}
int Draw::rect(float x, float y, GLuint VAO, GLuint IBO) {
	glUniform2f(smeshenie, x, y);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	return 0;
}
int Draw::color(float r, float g, float b, float a) {
	glUniform4f(vertexColorLocation,
			r,
			g,
			b,
			a);
	return 0;
}
Draw::Draw(GLuint _shaderProgram) {
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
	GLuint shaderProgram = _shaderProgram;
	int smeshenie = glGetUniformLocation(shaderProgram, "Pos");
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");
}

int Shaders::load(const char * vertexShaderSource, const char * fragmentShaderSource) {
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
	return 0;
}
Shaders::Shaders(GLuint _shaderProgram) {
	GLuint shaderProgram = _shaderProgram;
	int error = 0;
}

unsigned char* Textures::load(const char* str, int& width, int& height, int& nmc) {
	unsigned char* image;
	image = stbi_load(str, &width, &height, &nmc, 0);
	return image;
}
int Textures::del(const GLuint* textureind) {
	glDeleteTextures(1, textureind);
	if (!(error = glGetError())) return 0; else return error;
}
int Textures::active(GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	if (!(error = glGetError())) return 0; else return error;
}
int Textures::generate(unsigned char* image, int width, int height, int nmc) {
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
Textures::Textures(GLuint _shaderProgram) {
	GLuint shaderProgram = _shaderProgram;
	int error = 0;
}

int init() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	//GL_ONE_MINUS_CONSTANT_COLOR
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
	return 0;
}
