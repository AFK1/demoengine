#ifndef __GL_LOADER_H_
#define __GL_LOADER_H_

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glext.h>

static PFNGLATTACHSHADERPROC glAttachShader;
static PFNGLBINDBUFFERPROC glBindBuffer;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
static PFNGLBUFFERDATAPROC glBufferData;
static PFNGLCOMPILESHADERPROC glCompileShader;
static PFNGLCREATEPROGRAMPROC glCreateProgram;
static PFNGLCREATESHADERPROC glCreateShader;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers;
static PFNGLDELETESHADERPROC glDeleteShader;
static PFNGLDELETEPROGRAMPROC glDeleteProgram;
static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
static PFNGLGENBUFFERSPROC glGenBuffers;
static PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
static PFNGLLINKPROGRAMPROC glLinkProgram;
static PFNGLSHADERSOURCEPROC glShaderSource;
static PFNGLUNIFORM1FPROC glUniform1f;
static PFNGLUNIFORM1IPROC glUniform1i;
static PFNGLUNIFORM2FPROC glUniform2f;
static PFNGLUNIFORM4FPROC glUniform4f;
static PFNGLUSEPROGRAMPROC glUseProgram;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

void
glLoadExt();


#endif // __GL_LOADER_H_
