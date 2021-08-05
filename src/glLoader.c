#include <glLoader.h>

void
glLoadExt()
{
  glUseProgram                  = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glUseProgram");
  glDeleteProgram               = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glDeleteProgram");
  glDeleteBuffers               = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glDeleteBuffers");
  glDeleteVertexArrays          = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glDeleteVertexArrays");
  glUniform1f                   = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glUniform1f");
  glUniform1i                   = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glUniform1i");
  glUniform2f                   = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glUniform2f");
  glUniform4f                   = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glUniform4f");
  glEnableVertexAttribArray     = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glEnableVertexAttribArray");
  glVertexAttribPointer         = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glVertexAttribPointer");
  glBufferData                  = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glBufferData");
  glBindBuffer                  = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glBindBuffer");
  glBindVertexArrays            = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glBindVertexArrays");
  glGenBuffers                  = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glGenBuffers");
  glCreateShader                = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glCreateShader");

}
