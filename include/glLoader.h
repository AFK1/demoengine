#ifndef __GL_LOADER_H_
#define __GL_LOADER_H_

#include <GL/glext.h>
#include <GL/gl.h>

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
static PFNGLBindVertexArraysPROC glBindVertexArrays;
static PFNGLGENBUFFERSPROC glGenBuffers;
static PFNGLCREATESHADERPROC glCreateShader;

void
glLoadExt();


#endif // __GL_LOADER_H_
