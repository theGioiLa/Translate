#pragma once
#include "../Utilities/utilities.h"

class Texture {
	GLuint		m_Id;
	GLenum		m_TilingMode;
	GLenum		m_TextureType;
	bool		isActive;

	void CreateTexture2D();
	void CreateTextureCubeMap();

public:
	GLuint		m_TextureId, m_TexUnit;
	char*		m_Info;

	Texture() {}

	Texture(int id, GLenum textureType = GL_TEXTURE_2D, bool active = true) :
		m_Id(id), m_TexUnit(id), m_TextureType(textureType), isActive(active) {
		m_Info = new char[80];
	}
	~Texture();

	void Init();
	void Draw();
	void CleanUp();

	void SetTilingMode(GLenum tilingMode) { m_TilingMode = tilingMode; }
	void SetId(GLuint id) { m_Id = id; }
	void SetActicve(bool status) { isActive = status; }
	bool isOn() { return isActive; }
};