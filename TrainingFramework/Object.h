#pragma once 

#include "Model.h"
#include<vector>
#include "Texture.h"
#include "ResourceManager.h"
#include "ObjShaders.h"
#include "EnvShaders.h"

class Object {
protected:
	GLuint m_Id;
	Model* m_pModel;
	std::vector<Texture*> m_LTextures;
	Shaders* m_pShader;

	ResourceManager* resourceManager;

	Model m_Model;
	Texture m_Skin;

	Vector3 m_Scale;
	Vector3 m_RotationalAngle;
	Vector3 m_Position;
	
	Matrix m_transformMtx;

public:
	Object(GLuint id): m_Id(id), m_Scale(Vector3(1, 1, 1)), m_RotationalAngle(Vector3(0, 0, 0)),
		m_Position(Vector3(0, 0, 0)) {
		m_Model = Model();
		m_Skin = Texture();
	}
	
	Object(): m_Scale(Vector3(1, 1, 1)), m_RotationalAngle(Vector3(0, 0, 0)),
		m_Position(Vector3(0, 0, 0)) {
		m_Model = Model();
		m_Skin = Texture();
	}

	void Init(char* fileTGA, char* fileNFG, GLenum textureType = GL_TEXTURE_2D);
	void Draw(ObjShaders& shaders);
	void CleanUp();

	void SetModel(GLuint modelId) {};
	void SetTextures(std::vector<int> texturesID) {};
	void SetCubeTex(std::vector<int> cubeTexesId) {};
	void SetShader(GLuint shaderId) {};

	void SetScale(Vector3 vScale) { m_Scale = vScale; }

	void SetRotationAngle(Vector3 vRotation) {
		m_RotationalAngle = vRotation;
	}

	void SetTranslation(Vector3 translation) { m_Position = translation; }

	void CalculateTransformMatrix();
};
