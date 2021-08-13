#include <swt.hpp>
#include <stb_image.h>
#include <log.hpp>
#include <farbfeld.hpp>

int error = 0;
Log * logger;

//=======================Global init==========================
GLFWwindow* window;
GLuint VAO, VBO, IBO;

GLfloat vertices[] =
{
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

GLuint shaderProgram;
unsigned char* image;
int width, height, numColCh;
GLuint texture;
//=============================================================


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexcord;\n"
"uniform vec2 Pos; \n"
"out vec2 Texcord;\n"
"void main()\n"
"{\n"
"   Texcord = aTexcord;\n"
"   gl_Position = vec4((aPos.x/12)-1.0f+(1.0/12)+(Pos.y/6),"
"                      (aPos.y/12)-1.0f+(1.0/12)+(Pos.x/6),"
"                      0.0f,1.0f);\n"
//"   gl_Position = vec4(aPos.xyz,1.0f);\n"
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
    logger->print(LogType::critical, "Failed to create GLFW window");
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

  glGetError(); // Remove errors

  glDeleteShader(vertexShader);                                          //Not to be modified (I hope)
  glDeleteShader(fragmentShader);
  if ((error = glGetError()) != 0)
  {
    logger->print(LogType::warn, "Can't delete unused shaders");
  };

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
}

void load_texture() {
  image = stbi_load("container.jpg", &width, &height, &numColCh, 0);               //Not to be modified
}

void gen_texture() {
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 
      0, 
      numColCh == 3 ? GL_RGB : GL_RGBA, 
      width, 
      height, 
      0, 
      numColCh == 3 ? GL_RGB : GL_RGBA, 
      GL_UNSIGNED_BYTE, 
      image);

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
  logger = Log::getInstance();
  logger->set_error_type(LogType::info);
  window_init();
  load_shaders();
  load_texture();
  gen_texture();
  logger->print(LogType::info,       "Info test"    );
  logger->print(LogType::log,        "Log test"     );
  logger->print(LogType::warn, 	     "Warn test"    );
  logger->print(LogType::error,      "Error test"   );
  logger->print(LogType::critical,   "Critical test");

  struct Farbfeld* tex = readFarbfeld("test.ff");
  if (tex != nullptr)
    {
      char * buf = (char *) malloc(sizeof(char)*150);
      sprintf(buf, 
          "magic: %s, w: %u, h: %u", 
          tex->magicVal, 
          tex->width, 
          tex->height);
      logger->print(LogType::info, buf);
    } else {
      logger->print(LogType::error, 
	  "Put Farbfeld texture \"test.ff\""
	  " into executing directory(not next to executable)");
    };

  int vertexColorLocation = glGetUniformLocation(shaderProgram, 
      "Color");
  int smeshenie = glGetUniformLocation(shaderProgram,
      "Pos");
  glUseProgram(shaderProgram);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
  //GL_ONE_MINUS_CONSTANT_COLOR
  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

  while (!glfwWindowShouldClose(window))
  {
  glClear(GL_COLOR_BUFFER_BIT);
      for (float i = 0; i < 11; i++) {
          for (float j = 0; j < 11; j++) {
              glUniform2f(smeshenie,i,j);
              glUniform4f(vertexColorLocation,
                  0.0f,
                  1.0f,
                  0.0f,
                  1.0f);

              glBindTexture(GL_TEXTURE_2D, texture);
              glBindVertexArray(VAO);
              glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
              glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
              
          }
      }
    glUniform2f(smeshenie, 0.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
