#include <glLoader.h>

void
glLoadExt()
{

  glAttachShader				= (PFNGLATTACHSHADERPROC)glfwGetProcAddress("glAttachShader");
  glBindBuffer					= (PFNGLBINDBUFFERPROC)glfwGetProcAddress("glBindBuffer");
  glBindVertexArray				= (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
  glBindVertexArrays			= (PFNGLBINDVERTEXARRAYSPROC)glfwGetProcAddress("glBindVertexArrays");
  glBufferData					= (PFNGLBUFFERDATAPROC)glfwGetProcAddress("glBufferData");
  glCompileShader				= (PFNGLCOMPILESHADERPROC)glfwGetProcAddress("glCompileShader");
  glCreateProgram				= (PFNGLCREATEPROGRAMPROC)glfwGetProcAddress("glCreateProgram");
  glCreateShader				= (PFNGLCREATESHADERPROC)glfwGetProcAddress("glCreateShader");
  glDeleteBuffers				= (PFNGLDELETEBUFFERSPROC)glfwGetProcAddress("glDeleteBuffers");
  glDeleteShader				= (PFNGLDELETESHADERPROC)glfwGetProcAddress("glDeleteShader");
  glDeleteProgram				= (PFNGLDELETEPROGRAMPROC)glfwGetProcAddress("glDeleteProgram");
  glDeleteVertexArrays			= (PFNGLDELETEVERTEXARRAYSPROC)glfwGetProcAddress("glDeleteVertexArrays");
  glEnableVertexAttribArray		= (PFNGLENABLEVERTEXATTRIBARRAYPROC)glfwGetProcAddress("glEnableVertexAttribArray");
  glGenBuffers					= (PFNGLGENBUFFERSPROC)glfwGetProcAddress("glGenBuffers");
  glGenerateMipmap				= (PFNGLGENERATEMIPMAPPROC)glfwGetProcAddress("glGenerateMipmap");
  glGenVertexArrays				= (PFNGLGENVERTEXARRAYSPROC)glfwGetProcAddress("glGenVertexArrays");
  glGetUniformLocation			= (PFNGLGETUNIFORMLOCATIONPROC)glfwGetProcAddress("glGetUniformLocation");
  glLinkProgram					= (PFNGLLINKPROGRAMPROC)glfwGetProcAddress("glLinkProgram");
  glShaderSource			    = (PFNGLSHADERSOURCEPROC)glfwGetProcAddress("glShaderSource");
  glUseProgram                  = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glUseProgram");
  glUniform1f                   = (PFNGLUNIFORM1FPROC)glfwGetProcAddress("glUniform1f");
  glUniform1i                   = (PFNGLUNIFORM1IPROC)glfwGetProcAddress("glUniform1i");
  glUniform2f                   = (PFNGLUNIFORM2FPROC)glfwGetProcAddress("glUniform2f");
  glUniform4f                   = (PFNGLUNIFORM4FPROC)glfwGetProcAddress("glUniform4f");
  glVertexAttribPointer         = (PFNGLVERTEXATTRIBPOINTERPROC)glfwGetProcAddress("glVertexAttribPointer");

}
