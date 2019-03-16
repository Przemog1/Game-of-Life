#include "RGBTexture.h"
#include <glad\glad.h>
#include <iostream>

RGBTexture::RGBTexture(unsigned int width, unsigned int height)
	:width(width), height(height)
{


	imageBuffer = new Pixel*[height];

	imageBuffer[0] = new Pixel[width*height];

	for (unsigned int i = 1; i < height; i++)
		imageBuffer[i] = imageBuffer[i - 1] + width;



	glGenTextures(1,&textureID);

	glActiveTexture(GL_TEXTURE0 + textureCount);
	glBindTexture(GL_TEXTURE_2D, textureID);

	activeTextureID = textureCount;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBuffer[0]);

	textureCount++;
}

RGBTexture::~RGBTexture()
{
	glDeleteTextures(1, &textureID);
	delete imageBuffer;
}

void RGBTexture::update()
{
	glActiveTexture(GL_TEXTURE0 + activeTextureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBuffer[0]);
}

unsigned int RGBTexture::textureCount = 0;