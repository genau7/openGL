/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redestributed without written permission.*/
//Version: 001

#include "Texture.h"

Texture::Texture() {
    //Initialize texture ID
    mTextureID = 0;

    //Initialize texture dimensions
    mTextureWidth = 0;
    mTextureHeight = 0;
}

Texture::~Texture() {
    //Free texture data if needed
    freeTexture();
}

bool Texture::loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height ) {
    //Free texture if it exists
    freeTexture();

    //Get texture dimensions
    mTextureWidth = width;
    mTextureHeight = height;

    //Generate texture ID
    glGenTextures( 1, &mTextureID );

    //Bind texture ID
    glBindTexture( GL_TEXTURE_2D, mTextureID );

    //Generate texture
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

    //Set texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    //Unbind texture
    glBindTexture( GL_TEXTURE_2D, NULL );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )    {
        printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
        return false;
    }
    return true;
}

void Texture::freeTexture() {
    //Delete texture
    if( mTextureID != 0 )  {
        glDeleteTextures( 1, &mTextureID );
        mTextureID = 0;
    }
    mTextureWidth = 0;
    mTextureHeight = 0;
}

void Texture::render( GLfloat x, GLfloat y ) {
    //If the texture exists
    if( mTextureID != 0 )   {
        //Remove any previous transformations
        glLoadIdentity();

        //Move to rendering point
        glTranslatef( x, y, 0.f );

        //Set texture ID
        glBindTexture( GL_TEXTURE_2D, mTextureID );

        //Render textured quad
        glBegin( GL_QUADS );
            glTexCoord2f( 0.f, 0.f ); glVertex2f(           0.f,            0.f );
            glTexCoord2f( 1.f, 0.f ); glVertex2f( mTextureWidth,            0.f );
            glTexCoord2f( 1.f, 1.f ); glVertex2f( mTextureWidth, mTextureHeight );
            glTexCoord2f( 0.f, 1.f ); glVertex2f(           0.f, mTextureHeight );
        glEnd();
    }
}

GLuint Texture::getTextureID() {
    return mTextureID;
}

GLuint Texture::textureWidth() {
    return mTextureWidth;
}

GLuint Texture::textureHeight() {
    return mTextureHeight;
}



bool loadMedia(Texture & texture) {
	//Checkerboard pixels
	const int CHECKERBOARD_WIDTH = 128;
	const int CHECKERBOARD_HEIGHT = 128;
	const int CHECKERBOARD_PIXEL_COUNT = CHECKERBOARD_WIDTH * CHECKERBOARD_HEIGHT;
	GLuint checkerBoard[CHECKERBOARD_PIXEL_COUNT];

	//Go through pixels
	for (int i = 0; i < CHECKERBOARD_PIXEL_COUNT; ++i) 	{
		//Get the individual color components
		GLubyte* colors = (GLubyte*)&checkerBoard[i];

		//If the 5th bit of the x and y offsets of the pixel do not match
		if (i / 128 & 16 ^ i % 128 & 16)  {
			//Set pixel to white
			colors[0] = 0xFF;
			colors[1] = 0xFF;
			colors[2] = 0xFF;
			colors[3] = 0xFF;
		}
		else {
			//Set pixel to red
			colors[0] = 0xFF;
			colors[1] = 0x00;
			colors[2] = 0x00;
			colors[3] = 0xFF;
		}
	}

	//Load texture
	if (!texture.loadTextureFromPixels32(checkerBoard, CHECKERBOARD_WIDTH, CHECKERBOARD_HEIGHT))	{
		printf("Unable to load checkerboard texture!\n");
		return false;
	}
	return true;
}

