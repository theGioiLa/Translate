#include "stdafx.h"
#include "Texture.h"

void Texture::Init(char* fileName, GLenum textureType) {
	if (textureType == GL_TEXTURE_2D) CreateTexture2D(fileName);
	else CreateTextureCubeMap(fileName);
}

void Texture::CreateTexture2D(char* fileName) {
	glGenTextures(1, &m_textureId);

	glBindTexture(GL_TEXTURE_2D, m_textureId);

	int width, height, bpp;
	char *imageData = LoadTGA(fileName, &width, &height, &bpp);

	if (bpp == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}

	if (bpp == 32) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	delete[] imageData;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::CreateTextureCubeMap(char* fileName) {
	int width, height, bpp;
	char rightP[80], leftP[80], topP[80], botP[80], farP[80], nearP[80];
	strcpy(rightP, fileName);
	strcat(rightP, "right.TGA");

	strcpy(leftP, fileName);
	strcat(leftP, "left.TGA");

	strcpy(topP, fileName);
	strcat(topP, "top.TGA");
	
	strcpy(botP, fileName);
	strcat(botP, "bottom.TGA");

	strcpy(farP, fileName);
	strcat(farP, "back.TGA");

	strcpy(nearP, fileName);
	strcat(nearP, "front.TGA");

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);

	char **cubePixels= new char*[6];
	cubePixels[0] = LoadTGA(rightP, &width, &height, &bpp);
	cubePixels[1] = LoadTGA(leftP, &width, &height, &bpp);
	cubePixels[2] = LoadTGA(topP, &width, &height, &bpp);
	cubePixels[3] = LoadTGA(botP, &width, &height, &bpp);
	cubePixels[4] = LoadTGA(farP, &width, &height, &bpp);
	cubePixels[5] = LoadTGA(nearP, &width, &height, &bpp);
	
	for (int i = 0; i < 6; i++) {
		if (bpp == 24) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels[i]);
		}

		if (bpp == 32) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubePixels[i]);
		}

		delete cubePixels[i];
	}

	delete[] cubePixels;

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDisable(GL_TEXTURE_CUBE_MAP);
}

