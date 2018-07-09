#pragma once 

#include <vector>
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"

class ResourceManager {
	char*					 m_SourceData;
	std::vector<Model*>	 	 m_LModels;
	std::vector<Texture*>	 m_LTextures;
	std::vector<Texture*>	 m_LCubeTexs;
	std::vector<Shaders*>	 m_LShaders;

	ResourceManager() {}
	static ResourceManager*  m_Instance;
	int CreateModelsAndTextures();
	int InitShaders();

public:
	static ResourceManager* GetInstance() {
		if (m_Instance == nullptr) m_Instance = new ResourceManager;
		return m_Instance;
	}
	
	int Init(char* dataSource);
	Model* GetModel(GLuint id) { return m_LModels.at(id); }
	Texture* GetTexture(GLuint id) { return m_LTextures.at(id); }
	Texture* GetCubeTex(GLuint id) { return m_LCubeTexs.at(id); }
	Shaders* GetShader(GLuint id) { return m_LShaders.at(id); }

	void CleanUp();

	~ResourceManager() {}
};