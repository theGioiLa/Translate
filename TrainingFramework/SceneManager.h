#pragma once 
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include <vector>

class SceneManager {
	SceneManager() {};
	static SceneManager* m_Instance;

	char*				 m_SourceData;
	std::vector<Object*> m_LObjs;
	Camera*				 camera = nullptr;

public:
	static SceneManager* GetInstance() {
		if (m_Instance == nullptr) m_Instance = new SceneManager;
		return m_Instance;
	}

	void Init(char* dataSource);
	void CreateObjects();
	void LoadObject(GLuint objId);
	void SetCamera(float nearP, float farP, float fov, float speed);
	void Update();
	void Draw();
};