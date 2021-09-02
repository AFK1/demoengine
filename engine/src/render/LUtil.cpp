/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/
//Version: 006

#include <LUtil.hpp>
#include <IL/il.h>
#include <IL/ilu.h>
#include <LTexture.hpp>

//File loaded texture
LTexture gLoadedTexture;

bool initGL()
{
    //Set the viewport

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.07f, 1.f );

    //Enable texturing

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %d\n", error );
        return false;
    }

    return true;
}

bool loadMedia(const char path)
{
    if( !gLoadedTexture.loadTextureFromFile( path ) )
    {
        printf( "Unable to load file texture!\n" );
        return false;
    }

    return true;
}

void update()
{

}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    //Calculate centered offsets
    GLfloat x = ( SCREEN_WIDTH - gLoadedTexture.textureWidth() ) / 2.f;
    GLfloat y = ( SCREEN_HEIGHT - gLoadedTexture.textureHeight() ) / 2.f;

    //Render texture
    gLoadedTexture.render( x, y );

    //Update screen
    glfwSwapBuffers();
}
