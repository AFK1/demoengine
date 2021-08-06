#ifndef __GL_LOADER_H_
#define __GL_LOADER_H_

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glext.h>

static PFNGLUSEPROGRAMPROC glUseProgram;
static PFNGLDELETEPROGRAMPROC glDeleteProgram;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers;
static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
static PFNGLUNIFORM1FPROC glUniform1f;
static PFNGLUNIFORM1IPROC glUniform1i;
static PFNGLUNIFORM2FPROC glUniform2f;
static PFNGLUNIFORM4FPROC glUniform4f;
static PFNGLENABLEVERTEXATTRIBARRAYPROC
	  glEnableVertexAttribArray;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
static PFNGLBUFFERDATAPROC glBufferData;
static PFNGLBINDBUFFERPROC glBindBuffer;
static PFNGLGENBUFFERSPROC glGenBuffers;
static PFNGLCREATESHADERPROC glCreateShader;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
static PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
static PFNGLDELETESHADERPROC glDeleteShader;
static PFNGLLINKPROGRAMPROC glLinkProgram;
static PFNGLATTACHSHADERPROC glAttachShader;
static PFNGLCREATEPROGRAMPROC glCreateProgram;
static PFNGLCOMPILESHADERPROC glCompileShader;
static PFNGLSHADERSOURCEPROC glShaderSource;

void
glLoadExt();


#endif // __GL_LOADER_H_
