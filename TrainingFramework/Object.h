#pragma once 

#include "Model.h"
#include "Texture.h"
#include "ObjShaders.h"

class Object {
protected:
	Model m_Model;
	Texture m_Skin;

	Vector3 m_vScale;
	Vector3 m_vRotationAngle;
	Vector3 m_vTranslation;
	
	Matrix m_transformMtx;

public:
	Object(): m_vScale(Vector3(1, 1, 1)), m_vRotationAngle(Vector3(0, 0, 0)), m_vTranslation(Vector3(0, 0, 0)) {
		m_Model = Model();
		m_Skin = Texture(); 
	}

	void Init(char* fileTGA, char* fileNFG, GLenum textureType = GL_TEXTURE_2D);
	void Draw(ObjShaders& shaders);
	void CleanUp();

	void SetScale(Vector3 vScale) { m_vScale = vScale; }

	void SetRotationAngle(Vector3 vRotation) {
		m_vRotationAngle = vRotation;
	}

	void SetTranslation(Vector3 translation) { m_vTranslation = translation; }

	void CalculateTransformMatrix();
};
