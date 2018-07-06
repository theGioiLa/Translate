#pragma once 

#include "Model.h"
#include "Texture.h"
#include "Map.h"
#include "EnvShaders.h"
#include <vector>

class ResourceManager {
	ResourceManager() {}
	static ResourceManager*  m_Instance;
	void CreateModelsAndTextures();

	char*					 m_SourceData;
	std::vector<Model*>	 	 m_LModels;
	std::vector<Texture*>	 m_LTextures;
	std::vector<Texture*>	 m_LCubeTexs;
	std::vector<Shaders*>	 m_LShaders;

public:
	static ResourceManager* GetInstance() {
		if (m_Instance == nullptr) m_Instance = new ResourceManager;
		return m_Instance;
	}

	void Init(char* dataSource);
	Model* GetModel(GLuint id) { return m_LModels.at(id); }
	Texture* GetTexture(GLuint id) { return m_LTextures.at(id); }

	void CleanUp();
};