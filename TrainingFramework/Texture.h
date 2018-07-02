#pragma once
#include "../Utilities/utilities.h"

class Texture {
	GLuint m_texUnit;

	void CreateTexture2D(char* fileName);
	void CreateTextureCubeMap(char* fileName);

public:
	void Init(char* fileName, GLenum textureType);
	void Draw();
	void CleanUp() {
		glDeleteTextures(1, &m_textureId);
	}

	GLuint m_textureId;
};