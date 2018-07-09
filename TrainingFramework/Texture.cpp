#include "stdafx.h"
#include "Texture.h"

void Texture::Init() {
	if (m_TextureType == GL_TEXTURE_2D) {
		CreateTexture2D();
	}
	else CreateTextureCubeMap();
}

void Texture::CreateTexture2D() {
	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);

	int width, height, bpp;
	char *imageData = LoadTGA(m_Info, &width, &height, &bpp);

	if (bpp == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}

	if (bpp == 32) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	delete[] imageData;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TilingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TilingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}



void Texture::CreateTextureCubeMap() {
	int width, height, bpp;
	char rightP[80], leftP[80], topP[80], botP[80], farP[80], nearP[80];
	strcpy(rightP, m_Info);
	strcat(rightP, "right.TGA");

	strcpy(leftP, m_Info);
	strcat(leftP, "left.TGA");

	strcpy(topP, m_Info);
	strcat(topP, "top.TGA");

	strcpy(botP, m_Info);
	strcat(botP, "bottom.TGA");

	strcpy(farP, m_Info);
	strcat(farP, "back.TGA");

	strcpy(nearP, m_Info);
	strcat(nearP, "front.TGA");

	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureId);

	char **cubePixels = new char*[6];
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

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, m_TilingMode);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, m_TilingMode);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture::CleanUp() {
	delete[] m_Info;
	m_Info = nullptr;
	glDeleteTextures(1, &m_TextureId);
}

Texture::~Texture() {
	
}