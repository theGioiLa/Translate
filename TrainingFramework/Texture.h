#pragma once
#include "../Utilities/utilities.h"

class Texture {
	GLuint m_Id;
	GLenum m_TilingMode;
	char* m_Info;
	GLenum m_TextureType;

	void CreateTexture2D(char* fileName);
	void CreateTextureCubeMap(char* fileName);

public:
	Texture() {}
	Texture(GLuint id, GLenum tilingMode, char* info, GLenum textureType = GL_TEXTURE_2D):
		m_Id(id), m_TilingMode(tilingMode), m_Info(info), m_TextureType(textureType) {}

	void Init(char* fileName, GLenum textureType);
	void Draw();
	void CleanUp() {
		glDeleteTextures(1, &m_textureId);
	}

	GLuint m_textureId;
};