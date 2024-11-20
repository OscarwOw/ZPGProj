#pragma once
#include <SOIL.h>
#include <GL/glew.h>

#include <GLFW/glfw3.h>  

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Texture {
public:
	Texture() {
		_textureId = SOIL_load_OGL_texture("test.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

		//Cube Map (SkyBox)
		//GLuint 
		// textureID = SOIL_load_OGL_cubemap("xpos.jpg","xneg.jpg","ypos.jpg","yneg.jpg","zpos.jpg","zneg.jpg",SOIL_LOAD_RGB,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS    );
	}


	void bind() {
		glBindTexture(GL_TEXTURE_2D, _textureId);
	}

private:
	int _textureId;
};