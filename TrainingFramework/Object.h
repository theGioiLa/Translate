#pragma once 

#include "Model.h"
#include "Texture.h"
#include "ResourceManager.h"
#include <vector>

class Object {
protected:
	GLuint					m_Id;
	Model*					m_pModel;
	std::vector<Texture*>	m_LTextures;
	std::vector<Texture*>	m_LCubTexes;
	Shaders*				m_pShader;
	ResourceManager*		resourceManager;

	Vector3					m_Scale;
	Vector3					m_RotationalAngle;
	Vector3					m_Position;

	Matrix					m_TransformMtx;

	GLint					texcoordAttribute;
	GLint					texcoordUniform;

	void DrawObj();
	void DrawEnv();

public:
	Object(GLuint id) : m_Id(id), m_Scale(Vector3(1, 1, 1)), m_RotationalAngle(Vector3(0, 0, 0)),
		m_Position(Vector3(0, 0, 0)) {
		resourceManager = ResourceManager::GetInstance();
	}

	Object() : m_Scale(Vector3(1, 1, 1)), m_RotationalAngle(Vector3(0, 0, 0)),
		m_Position(Vector3(0, 0, 0)) {
		resourceManager = ResourceManager::GetInstance();
	}

	int Init();

	void Draw();

	void SetModel(GLuint modelId);
	void SetTextures(std::vector<int> texturesID);
	void SetCubeTex(std::vector<int> cubeTexesId);
	void SetShader(GLuint shaderId);

	void SetScale(Vector3 vScale) { m_Scale = vScale; }

	void SetRotationAngle(Vector3 vRotation) {
		m_RotationalAngle = ToRadian(vRotation);
	}

	Vector3 ToRadian(Vector3 angle) {
		angle *= (3.14 / 180);
		return angle;
	}

	void SetTranslation(Vector3 position) { m_Position = position; }

	void UpdateTransformMatrix(Matrix viewMatrix, Matrix projectionMatrix);
};