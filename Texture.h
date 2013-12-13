
#include "GameHandler.h"
#include "glm.h"

class texture
{

	public:
	char * filename;
	int width , height;
	texture (char* filename_ , int width_ , int height_)
	{
		filename = filename_;
		width = width_;
		height = height_;
	}

	GLuint LoadGLTexture()
	{
	     GLuint texture;
	     unsigned char *data;
	     FILE *file;
	     file = fopen(filename,"r");
	     if (file == NULL) return 0;
	 
	     data = (unsigned char*) malloc(width * height * 3); 
	     fread(data, width * height * 3, 1, file);
	     fclose(file);
	  
	      
	    glGenTextures(1, &texture); // allocate a texture name
	    glBindTexture(GL_TEXTURE_2D, texture); // select our current texture
	    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);  
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // when texture area is small, bilinear filter the closest mipmap
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // when texture area is large, bilinear filter the first mipmap
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // texture should tile
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data); // build our texture mipmaps
	    free(data);  
	 
	    return texture;
	}

	void run (){
		GLuint textures = LoadGLTexture();
	    glEnable(GL_TEXTURE_2D);
	    glBindTexture( GL_TEXTURE_2D, textures);   
	    glBegin(GL_QUADS);                
	            glTexCoord2f(0.0f, 0.0f);  glVertex3f(0,0,-30);
	            glTexCoord2f(1.0f, 0.0f);  glVertex3f(WIN_ANCHO,0,-30);
	            glTexCoord2f(1.0f, 1.0f);  glVertex3f(WIN_ANCHO,WIN_ALTO,-30);
	            glTexCoord2f(0.0f, 1.0f);  glVertex3f(0,WIN_ALTO,-30);
	    glEnd();
	    glDisable(GL_TEXTURE_2D); 
	}

};