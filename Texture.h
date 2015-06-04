/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redestributed without written permission.*/
//Version: 001

#ifndef LTEXTURE_H
#define LTEXTURE_H

//#include "LOpenGL.h"
#include <stdio.h>
#include "GLUT.H"
//#include <gl\GL.h>
#include <gl/GL.h>
#include <gl/GLU.h>



class Texture {
public:
	Texture();    
	~Texture();
	bool loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height );
	void freeTexture();
	void render( GLfloat x, GLfloat y );
	GLuint getTextureID();     
	GLuint textureWidth();
	GLuint textureHeight();

private:
	//Texture name
	GLuint mTextureID;

	//Texture dimensions
	GLuint mTextureWidth;
	GLuint mTextureHeight;
};




bool loadMedia(Texture & texture);
#endif
