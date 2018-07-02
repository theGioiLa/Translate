#pragma once

#include "Object.h"
#include "EnvShader.h"

class Map: public Object {
	public:

	void Init(char* fileTGA, char* fileNPG, GLenum textureType = GL_TEXTURE_CUBE_MAP);
	void Draw(EnvShaders& shaders);
};