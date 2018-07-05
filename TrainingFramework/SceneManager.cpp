#include "stdafx.h"
#include "SceneManager.h"

SceneManager* SceneManager::m_Instance = nullptr;

void SceneManager::Init(char* dataSource) {
	m_SourceData = dataSource;
	CreateObjects();
}

void SceneManager::CreateObjects() {
	FILE* file;
	file = fopen(m_SourceData, "r");

	int nObjs;
	fscanf(file, "#Objects: %d\n", &nObjs);

	for (int i = 0; i < nObjs; i++) {
		int modelId, shaderId;
		int nTextures, nCubTextures, nLights;
		std::vector<int> texture2DId, cubeTexId, lightId;
		Vector3 pos, rot, scale;
		Object* obj = new Object(i);

		fscanf(file, "ID %*d\nMODEL %d\TEXTURES %d\n", &modelId, &nTextures);
		obj->SetModel(modelId);
		for (int j = 0; j < nTextures; j++) {
			int id;
			fscanf(file, "TEXTURE %d\n", &id);
			texture2DId.push_back(id);
		}
		obj->SetTextures(texture2DId);
			
		fscanf(file, "CUBETEXTURES %d\n", &nCubTextures);
		for (int j = 0; j < nCubTextures; j++) {
			int id;
			fscanf(file, "CUBETEX %d\n", &id);
			cubeTexId.push_back(id);
		}
		obj->SetCubeTex(cubeTexId);

		fscanf(file, "SHADER %d\nLIGHTS %d\n", &shaderId, &nLights);
		obj->SetShader(shaderId);
		for (int j = 0; j < nLights; j++) {
			int id;
			fscanf(file, "LIGHT %d\n", &id);
			lightId.push_back(id);
		}

		fscanf(file, "POSITION %f, %f, %f\n", &pos.x, &pos.y, &pos.z);
		obj->SetTranslation(pos);

		fscanf(file, "ROTATION %f, %f, %f\n", &rot.x, &rot.y, &rot.z);
		obj->SetRotationAngle(rot);

		fscanf(file, "SCALE %f, %f, %f\n\n", &scale.x, &scale.y, &scale.z);
		obj->SetScale(scale);

		m_LObjs.push_back(obj);
	}

	fscanf(file, "#LIGHT\n");
	fscanf(file, "AmbientColor %*f, %*f, %*f\n");
	fscanf(file, "AmbientWeight %*f\n");
	
	int nLight;
	fscanf(file, "LightsCount: %d\n\n", &nLight);
	for (int i = 0; i < nLight; i++) {
		fscanf(file, "ID %*d\n");
		fscanf(file, "POS/DIR %*f, %*f, %*f\n");
		fscanf(file, "TYPE %*s\n");
		fscanf(file, "COLOR %*f, %*f, %*f\n");
		fscanf(file, "MOVING %*s\n");
		fscanf(file, "RADIUS %*f\n");
		fscanf(file, "SPEED %*f\n\n");
	}

	float nearP, farP, fov, speed;
	fscanf(file, "#CAMERA\n");
	fscanf(file, "NEAR %f\n", &nearP);
	fscanf(file, "FAR %f\n", &farP);
	fscanf(file, "FOV %f\n", &fov);
	fscanf(file, "SPEED %f\n", &speed);
	SetCamera(nearP, farP, fov, speed);
}

void SceneManager::LoadObject(GLuint objId) {

}

void SceneManager::Draw() {

}

void SceneManager::Update() {

}

