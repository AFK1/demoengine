#include <farbfeld.hpp>
#include <render.hpp>

int error = 0;



GLuint shaderProgram;
unsigned char *image;
int width, height, numColCh;
GLuint texture;
//=============================================================

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexcord;\n"
    "uniform vec2 Pos; \n"
    "out vec2 Texcord;\n"
    "void main()\n"
    "{\n"
    "   Texcord = aTexcord;\n"
    "   gl_Position = vec4((aPos.x/12)-1.0f+(1.0/12)+(Pos.x/6),"
    "                      (aPos.y/12)-1.0f+(1.0/12)+(Pos.y/6),"
    "                      0.0f,1.0f);\n"
    //"   gl_Position = vec4(aPos.xyz,1.0f);\n"
    "}\0";
const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec2 Texcord;\n"
    "uniform vec4 Color; \n"
    "uniform sampler2D texture;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = Color;\n" // texture(texture, Texcord);\n"
                              // //vec4(Texcord.xy, Color.zw);\n"//
    "}\n\0";

void read_shader_file(const char *vertexPath, const char *fragmentPath) {
  const char *vertexCode;
  const char *fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  vShaderFile.exceptions(std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::badbit);
  vShaderFile.open(vertexPath);
  fShaderFile.open(fragmentPath);
  std::stringstream vShaderStream, fShaderStream;
  vShaderStream << vShaderFile.rdbuf(); // To be modified
  fShaderStream << fShaderFile.rdbuf();
  vShaderFile.close();
  fShaderFile.close();
  vertexCode = vShaderStream.str().c_str();
  fragmentCode = fShaderStream.str().c_str();
  const GLchar *vertexShaderSource = vertexCode;
  const GLchar *fragmentShaderSource =
      fragmentCode; // TODO: return shaders sources
}

void window_init(GLFWwindow* window) {
  glfwSetTime(0.0f);
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  window =
      glfwCreateWindow(500, 500, "EBFSWT", NULL, NULL); // Not to be modified
  if (window == NULL) {
    print(LogType::critical, "Failed to create GLFW window");
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glViewport(0, 0, 500, 500);
}

int entrypoint()
{
  GLuint shaderProgram = glCreateProgram();
  GLFWwindow* window;
  GLfloat vertices[] ={
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

  Draw* draw = new Draw(shaderProgram);
  Shaders* shaders = new Shaders(shaderProgram);
  Textures* textures = new Textures(shaderProgram);
  logger = Log::getInstance();
  logger->set_error_type(LogType::info);
  window_init(window);
  read_shader_file("shader.vert", "shader.frag");

  shaders->load(vertexShaderSource, fragmentShaderSource);
  GLuint VAO, VBO, IBO = draw->create_obj(vertices, verticesid);

  //stbi_image_free(image);
  logger->print(LogType::info,       "Info test"    );
  logger->print(LogType::log,        "Log test"     );
  logger->print(LogType::warn, 	     "Warn test"    );
  logger->print(LogType::error,      "Error test"   );
  logger->print(LogType::critical,   "Critical test");

  struct Farbfeld *tex = readFarbfeld("test.ff");
  if (tex != nullptr) {
    char *buf = (char *)malloc(sizeof(char) * 150);
    sprintf(buf, "magic: %s, w: %u, h: %u", tex->magicVal, tex->width,
            tex->height);
    print(LogType::info, buf);
  } else {
    print(LogType::error, "Put Farbfeld texture \"test.ff\""
                          " into executing directory(not next to executable)");
  };

  glUseProgram(shaderProgram);

  while (!glfwWindowShouldClose(window)) {
    for (float i = 0; i < 11; i++) {
      for (float j = 0; j < 11; j++) {
        // How should I fix it
        // If I haven't code?
        // render.draw
      }
    }
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
