#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::m_Instance = nullptr;

void ResourceManager::Init(char* dataSource) {
	m_SourceData = dataSource;
	CreateModelsAndTextures();
}

void ResourceManager::CreateModelsAndTextures() {
	FILE* file;
	if (!(file = fopen(m_SourceData, "r"))) return;

	int nModels;
	fscanf(file, "#Models: %d\n", &nModels);

	for (int i = 0; i < nModels; i++) {
		char filename[80];
		fscanf(file, "ID %*d\nFILE %s\n", filename);
		m_LModels.push_back(new Model(i, filename));
	}

	int nTextures2D;
	fscanf(file, "\n#2D Textures: %d\n", &nTextures2D);

	for (int i = 0; i < nTextures2D; i++) {
		char filename[80];
		char tiling[80];
		fscanf(file, "ID %*d\nFILE %s\nTILING %s\n", filename, tiling);

		GLenum tilingMode = 0;
		if (strcmp(tiling, "REPEAT") == 0) tilingMode = GL_REPEAT;
		if (strcmp(tiling, "CLAMP") == 0) tilingMode = GL_CLAMP_TO_EDGE;
		if (strcmp(tiling, "MIRROR") == 0) tilingMode = GL_MIRRORED_REPEAT;

		m_LTextures.push_back(new Texture(i, tilingMode, filename));
	}

	int nCubeTextures;
	fscanf(file, "\n#Cube Textures: %d\n", &nCubeTextures);

	for (int i = 0; i < nCubeTextures; i++) {
		char source[80];
		char tiling[80];
		fscanf(file, "ID %*d\nFILE %s\nTILING %s\n", source, tiling);

		GLenum tilingMode = 0;
		if (strcmp(tiling, "REPEAT") == 0) tilingMode = GL_REPEAT;
		if (strcmp(tiling, "CLAMP") == 0) tilingMode = GL_CLAMP_TO_EDGE;
		if (strcmp(tiling, "MIRROR") == 0) tilingMode = GL_MIRRORED_REPEAT;

		m_LCubeTexs.push_back(new Texture(i, tilingMode, source, GL_TEXTURE_CUBE_MAP));
	}

	int nShaders;
	fscanf(file, "\n#Shaders %d\n", &nShaders);

	for (int i = 0; i < nShaders; i++) {
		char vsFile[80], fsFile[80];
		int nState;
		GLenum enable_States = 0;
		fscanf(file, "ID %*d\nVS %s\nFS %s\n STATES %d\n", vsFile, fsFile, &nState);

		for (int j = 0; j < nState; j++) {
			char state[30];
			fscanf(file, "STATE %s\n", state);
			if (strcmp(state, "CULLING") == 0) enable_States |= GL_CULL_FACE;
			if (strcmp(state, "DEPTH_TEST") == 0) enable_States |= GL_DEPTH_TEST;
			if (strcmp(state, "ALPHA_TEST") == 0) enable_States |= GL_BLEND;
		}

		m_LShaders.push_back(new Shaders(i, vsFile, fsFile, enable_States));
	}

	fclose(file);
}

void ResourceManager::CleanUp() {
	std::vector<Model*>::iterator itModel = m_LModels.begin();
	while (itModel != m_LModels.end()) {
		(*itModel)->CleanUp();
		itModel++;
	}

	std::vector<Texture*>::iterator itTexture = m_LTextures.begin();
	while (itTexture != m_LTextures.end()) {
		(*itModel)->CleanUp();
		itTexture++;
	}
}