#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::m_Instance = nullptr;

int ResourceManager::Init(char* dataSource) {
	m_SourceData = dataSource;
	if (CreateModelsAndTextures() != 0) return -1;
	return InitShaders();
}

int ResourceManager::InitShaders() {
	std::vector<Shaders*>::iterator it = m_LShaders.begin();
	for (; it != m_LShaders.end(); it++) {
		if ((*it)->Init()) return -1;
	}
	
	return 0;
}

int ResourceManager::CreateModelsAndTextures() {
	FILE* file;
	if (!(file = fopen(m_SourceData, "r"))) return -1;

	int nModels;
	fscanf(file, "#Models: %d\n", &nModels);

	for (int i = 0; i < nModels; i++) {
		Model* model = new Model(i);
		fscanf(file, "ID %*d\nFILE %s\n", model->m_Info);
		m_LModels.push_back(model);
	}

	int nTextures2D;
	fscanf(file, "\n#2D Textures: %d\n", &nTextures2D);

	for (int i = 0; i < nTextures2D; i++) {
		Texture* texture = new Texture(i);

		char tiling[80];
		fscanf(file, "ID %*d\nFILE %s\nTILING %s\n", texture->m_Info, tiling);

		GLenum tilingMode = 0;
		if (strcmp(tiling, "REPEAT") == 0) tilingMode = GL_REPEAT;
		if (strcmp(tiling, "CLAMP") == 0) tilingMode = GL_CLAMP_TO_EDGE;
		if (strcmp(tiling, "MIRROR") == 0) tilingMode = GL_MIRRORED_REPEAT;

		texture->SetTilingMode(tilingMode);

		m_LTextures.push_back(texture);
		texture = nullptr;
	}

	int nCubeTextures;
	fscanf(file, "\n#Cube Textures: %d\n", &nCubeTextures);

	for (int i = 0; i < nCubeTextures; i++) {
		Texture* cubeTex = new Texture(i, GL_TEXTURE_CUBE_MAP);
		char tiling[80];
		fscanf(file, "ID %*d\nFILE %s\nTILING %s\n", cubeTex->m_Info, tiling);

		GLenum tilingMode = 0;
		if (strcmp(tiling, "REPEAT") == 0) tilingMode = GL_REPEAT;
		if (strcmp(tiling, "CLAMP") == 0) tilingMode = GL_CLAMP_TO_EDGE;
		if (strcmp(tiling, "MIRROR") == 0) tilingMode = GL_MIRRORED_REPEAT;

		cubeTex->SetTilingMode(tilingMode);

		m_LCubeTexs.push_back(cubeTex);
		cubeTex = nullptr;
	}

	int nShaders;
	fscanf(file, "\n#Shaders %d\n", &nShaders);
	
	for (int i = 0; i < nShaders; i++) {
		Shaders* shader = new Shaders(i);
		int nState;
		GLenum enable_States = 0;
		fscanf(file, "ID %*d\nVS %s\nFS %s\n STATES %d\n", shader->fileVS, shader->fileFS, &nState);

		for (int j = 0; j < nState; j++) {
			char state[30];
			fscanf(file, "STATE %s\n", state);
			if (strcmp(state, "CULLING") == 0) enable_States |= GL_CULL_FACE;
			if (strcmp(state, "DEPTH_TEST") == 0) enable_States |= GL_DEPTH_TEST;
			if (strcmp(state, "ALPHA_TEST") == 0) enable_States |= GL_BLEND;
		}

		shader->SetEnableState(enable_States);

		m_LShaders.push_back(shader);
		shader = nullptr;
	}

	fclose(file);
	return 0;
}

void ResourceManager::CleanUp() {
	std::vector<Model*>::iterator itModel = m_LModels.begin();
	for (; itModel != m_LModels.end(); itModel++) {
		(*itModel)->CleanUp();
		delete (*itModel);
	}

	std::vector<Texture*>::iterator itTexture = m_LTextures.begin();
	for (; itTexture != m_LTextures.end(); itTexture++) {
		(*itTexture)->CleanUp();
		delete (*itTexture);
	}

	std::vector<Texture*>::iterator itCubeTex = m_LCubeTexs.begin();
	for (; itCubeTex!= m_LCubeTexs.end(); itCubeTex++) {
		(*itCubeTex)->CleanUp();
		delete (*itCubeTex);
	}

	std::vector<Shaders*>::iterator itShader = m_LShaders.begin();
	for (; itShader != m_LShaders.end(); itShader++) {
		delete (*itShader);
	}
}