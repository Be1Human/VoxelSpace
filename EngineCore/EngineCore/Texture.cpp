#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Module/stb_image.h"
#include <iostream>

Texture::Texture():
	mWidth(0),
	mHeight(0),
	mTextureID(0)
{

}

Texture::~Texture()
{

}

bool Texture::Load(const string& fileName)
{
	//Read Picture
	int channels = 0;
	unsigned char* image = stbi_load(fileName.c_str(), &mWidth, &mHeight, &channels, 0);

	
	int format = GL_RGB;	
	if (channels == 4) {
		format = GL_RGBA;
	}

	//Create Texture Object
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	//Copy Data to this Object to Spawn Texture
	if (image) {
		glTexImage2D(
			GL_TEXTURE_2D,        //Texture target
			0,                   //Level of detail
			format,             //Color Format Opengl should use
			mWidth,
			mHeight,
			0,                  //Border(must be "0")
			format,
			GL_UNSIGNED_BYTE,  // Bit Depth of input data ,Using byte specifies 8-bit channels
			image              // Pointer to image data
		);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::Fail to Load Texture!" << endl;
	}
	stbi_image_free(image);  //Release data

	//Enable Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//Enable bilinear filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::Unload()
{
	glDeleteBuffers(1, &mTextureID);
}

void Texture::SetActive()
{
	//Activate Texture Object
	glBindTexture(GL_TEXTURE_2D,mTextureID);

}
