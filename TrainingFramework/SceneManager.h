#pragma once 
#include "Object.h"
#include "Camera.h"
#include "Light.h"

class SceneManager {
	SceneManager() {};
	static SceneManager* m_Instance;

	char*				 m_SourceData;
	std::vector<Object*> m_LObjs;
	Camera				 m_Camera;

public:
	static SceneManager* GetInstance() {
		if (m_Instance == nullptr) m_Instance = new SceneManager;
		return m_Instance;
	}

	void Init(char* dataSource);
	void LoadObject(GLuint objId);
	void CreateObjects();
	void SetCamera(float near, float far, float fov, float speed);
	void Update();
	void Draw();
};