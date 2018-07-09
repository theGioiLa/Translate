#include "stdafx.h"
#include <exception>
#include "SceneManager.h"

SceneManager* SceneManager::m_Instance = nullptr;

int SceneManager::Init(char* dataSource) {
	m_SourceData = dataSource;

	if (CreateObjectsAndCamera() != 0) return -1;
	return LoadObjects();
}

int SceneManager::CreateObjectsAndCamera() {
	FILE* file;
	if (!(file = fopen(m_SourceData, "r"))) return -1;

	//Set Objects
	int nObjs;
	fscanf_s(file, "#Objects: %d\n", &nObjs);

	for (int i = 0; i < nObjs; i++) {
		int modelId, shaderId;
		int nTextures, nCubTextures, nLights;
		std::vector<int> texture2DId, cubeTexId, lightId;
		Vector3 pos, rot, scale;
		Object* obj = new Object(i);

		fscanf_s(file, "ID %*d\nMODEL %d\nTEXTURES %d\n", &modelId, &nTextures);
		obj->SetModel(modelId);
		for (int j = 0; j < nTextures; j++) {
			int id;
			fscanf_s(file, "TEXTURE %d\n", &id);
			texture2DId.push_back(id);
		}
		obj->SetTextures(texture2DId);

		fscanf_s(file, "CUBETEXTURES %d\n", &nCubTextures);
		if (nCubTextures > 0) {
			for (int j = 0; j < nCubTextures; j++) {
				int id;
				fscanf_s(file, "CUBETEX %d\n", &id);
				cubeTexId.push_back(id);
			}
			obj->SetCubeTex(cubeTexId);
		}

		fscanf_s(file, "SHADER %d\nLIGHTS %d\n", &shaderId, &nLights);
		obj->SetShader(shaderId);
		for (int j = 0; j < nLights; j++) {
			int id;
			fscanf_s(file, "LIGHT %d\n", &id);
			lightId.push_back(id);
		}

		fscanf_s(file, "POSITION %f, %f, %f\n", &pos.x, &pos.y, &pos.z);
		obj->SetTranslation(pos);

		fscanf_s(file, "ROTATION %f, %f, %f\n", &rot.x, &rot.y, &rot.z);
		obj->SetRotationAngle(rot);

		fscanf_s(file, "SCALE %f, %f, %f\n\n", &scale.x, &scale.y, &scale.z);
		obj->SetScale(scale);

		m_LObjs.push_back(obj);

		texture2DId.clear();
		cubeTexId.clear();
		lightId.clear();
		obj = nullptr;
	}

	//Set lights
	fscanf_s(file, "#LIGHTS\n");
	fscanf_s(file, "AmbientColor %*f, %*f, %*f\n");
	fscanf_s(file, "AmbientWeight %*f\n");

	int nLight;
	fscanf_s(file, "LightsCount: %d\n\n", &nLight);
	for (int i = 0; i < nLight; i++) {
		fscanf_s(file, "ID %*d\n");
		fscanf_s(file, "POS/DIR %*f, %*f, %*f\n");
		fscanf_s(file, "TYPE %*s\n");
		fscanf_s(file, "COLOR %*f, %*f, %*f\n");
		fscanf_s(file, "MOVING %*s\n");
		fscanf_s(file, "RADIUS %*f\n");
		fscanf_s(file, "SPEED %*f\n\n");
	}

	// Set Camera
	float nearP, farP, fov, speed;
	fscanf_s(file, "#CAMERA\n");
	fscanf_s(file, "NEAR %f\n", &nearP);
	fscanf_s(file, "FAR %f\n", &farP);
	fscanf_s(file, "FOV %f\n", &fov);
	fscanf_s(file, "SPEED %f\n", &speed);
	SetCamera(fov, nearP, farP, speed);

	fclose(file);
	return 0;
}

void SceneManager::LoadObject(GLuint objId) {

}

int SceneManager::LoadObjects() {
	std::vector<Object*>::iterator it = m_LObjs.begin();
	for (; it != m_LObjs.end(); it++) {
		if ((*it)->Init() != 0) return -1;
		(*it)->UpdateTransformMatrix(camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}

	return 0;
}

void SceneManager::Draw() {
	std::vector<Object*>::iterator it = m_LObjs.begin();
	for (; it != m_LObjs.end(); it++) {
		(*it)->Draw();
	}
}

void SceneManager::Update(unsigned char keyPressed, float deltaTime) {
	UpdateCamera(keyPressed, deltaTime);

	std::vector<Object*>::iterator it = m_LObjs.begin();
	for (; it != m_LObjs.end(); it++) {
		(*it)->UpdateTransformMatrix(camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}
}

void SceneManager::UpdateCamera(unsigned char keyPressed, float deltaTime) {
	if (keyPressed == 'A') camera.MoveAlongLocalX(-deltaTime);
	if (keyPressed == 'D') camera.MoveAlongLocalX(deltaTime);
	if (keyPressed == 'W') camera.MoveAlongLocalY(deltaTime);
	if (keyPressed == 'S') camera.MoveAlongLocalY(-deltaTime);
	if (keyPressed == 'Z') camera.MoveAlongLocalZ(deltaTime);
	if (keyPressed == 'X') camera.MoveAlongLocalZ(-deltaTime);
	if (keyPressed == 'R') camera.RotateAroundWorldY(deltaTime);
	if (keyPressed == 'T') camera.RotateAroundWorldY(-deltaTime);
	if (keyPressed == 'G') camera.RotateAroundLocalX(deltaTime);
	if (keyPressed == 'H') camera.RotateAroundLocalX(-deltaTime);
	if (keyPressed == 'K') camera.RotateAroundLocalZ(deltaTime);
	if (keyPressed == 'J') camera.RotateAroundLocalZ(-deltaTime);
}

void SceneManager::SetCamera(float fov, float nearP, float farP, float speed) {
	camera.SetProjectionMatrix(fov, nearP, farP);
	camera.SetSpeed(speed);
}

void SceneManager::CleanUp() {
	std::vector<Object*>::iterator it = m_LObjs.begin();
	for (; it != m_LObjs.end(); it++) {
		delete (*it);
	}
}