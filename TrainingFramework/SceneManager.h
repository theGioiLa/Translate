#pragma once 
#include "Object.h"
#include "Camera.h"
#include "Light.h"

class SceneManager {
	SceneManager() {};
	static SceneManager* m_Instance;

	char*				 m_SourceData;
	std::vector<Object*> m_LObjs;
	Camera				 camera;

	int CreateObjectsAndCamera();
public:
	static SceneManager* GetInstance() {
		if (m_Instance == nullptr) m_Instance = new SceneManager;
		return m_Instance;
	}

	int Init(char* dataSource);
	int LoadObjects();
	void LoadObject(GLuint objId);
	void SetCamera(float fov, float nearP, float farP, float speed);
	void Update(unsigned char key, float deltaTime);
	void UpdateCamera(unsigned char key, float deltaTime);
	void Draw();
	void CleanUp();

	~SceneManager() {}
};