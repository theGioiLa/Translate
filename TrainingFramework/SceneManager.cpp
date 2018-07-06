#include "stdafx.h"
#include <exception>
#include "SceneManager.h"

SceneManager* SceneManager::m_Instance = nullptr;

void SceneManager::Init(char* dataSource) { 
	camera = Camera::GetInstance();
	m_SourceData = dataSource;
	CreateObjects();
}
void SceneManager::CreateObjects() {
	FILE* file;
	if (!(file = fopen(m_SourceData, "r"))) return;

	int nObjs;
	fscanf_s(file, "#Objects: %d\n", &nObjs);

	for (int i = 0; i < nObjs; i++) {
		int modelId, shaderId;
		int nTextures, nCubTextures, nLights;
		std::vector<int> texture2DId, cubeTexId, lightId;
		Vector3 pos, rot, scale;
		//Object* obj = new Object(i);

		fscanf_s(file, "ID %*d\nMODEL %d\nTEXTURES %d\n", &modelId, &nTextures);
		//obj->SetModel(modelId);
		for (int j = 0; j < nTextures; j++) {
			int id;
			fscanf_s(file, "TEXTURE %d\n", &id);
			texture2DId.push_back(id);
		}
		//obj->SetTextures(texture2DId);

		fscanf_s(file, "CUBETEXTURES %d\n", &nCubTextures);
		for (int j = 0; j < nCubTextures; j++) {
			int id;
			fscanf_s(file, "CUBETEX %d\n", &id);
			cubeTexId.push_back(id);
		}
		//obj->SetCubeTex(cubeTexId);

		fscanf_s(file, "SHADER %d\nLIGHTS %d\n", &shaderId, &nLights);
		//obj->SetShader(shaderId);
		for (int j = 0; j < nLights; j++) {
			int id;
			fscanf_s(file, "LIGHT %d\n", &id);
			lightId.push_back(id);
		}

		fscanf_s(file, "POSITION %f, %f, %f\n", &pos.x, &pos.y, &pos.z);
		//obj->SetTranslation(pos);

		fscanf_s(file, "ROTATION %f, %f, %f\n", &rot.x, &rot.y, &rot.z);
		//obj->SetRotationAngle(rot);

		fscanf_s(file, "SCALE %f, %f, %f\n\n", &scale.x, &scale.y, &scale.z);
		//obj->SetScale(scale);

		//m_LObjs.push_back(obj);
	}

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

	float nearP, farP, fov, speed;
	fscanf_s(file, "#CAMERA\n");
	fscanf_s(file, "NEAR %f\n", &nearP);
	fscanf_s(file, "FAR %f\n", &farP);
	fscanf_s(file, "FOV %f\n", &fov);
	fscanf_s(file, "SPEED %f\n", &speed);
	SetCamera(nearP, farP, fov, speed);

	fclose(file);
}

void SceneManager::LoadObject(GLuint objId) {

}

void SceneManager::Draw() {

}

void SceneManager::Update() {

}

void SceneManager::SetCamera(float fov, float nearP, float farP, float speed) {
	camera->SetProjectionMatrix(fov, nearP, farP);
	camera->SetSpeed(speed);
}