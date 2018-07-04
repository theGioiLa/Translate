#pragma once 
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Camera {
protected:
	Matrix m_WorldMatrix, m_ViewMatrix, m_RotationMatrix, m_TranslationMatrix;
	Vector3 m_Position, m_Target;
	const GLfloat m_Velocity= 3.5f;
	const GLfloat m_AngularVelocity = 2.0f;
	
	Vector3 m_vUp;
	GLboolean isMoved, isRotation;

	void CalculateRotation();
	void CalculateTranslation();
	void UpdateMatrix();

public:
	Camera(): m_ViewMatrix(Matrix().SetIdentity()), m_Position(Vector3(0.0f, 0.0f, 0.0f)),
		m_Target(Vector3(0.0f, 0.0f, -1.0f)), m_vUp(Vector3(0.0f, 1.0f, 0.0f)), isMoved(false),
		isRotation(false) {
		CalculateRotation();
		CalculateTranslation();
		CalculateWorldMatrix();
	}

	void MoveAlongLocalX(GLfloat deltaTime);
	void MoveAlongLocalY(GLfloat deltaTime);
	void MoveAlongLocalZ(GLfloat deltaTime);

	void RotateAroundLocalX(GLfloat deltaTime);
	void RotateAroundWorldY(GLfloat deltaTime);
	void RotateAroundLocalZ(GLfloat deltaTime);

	Matrix CalculateWorldMatrix();
	Matrix CalculateViewMatrix();
	Matrix GetViewMatrix() { return m_ViewMatrix; }
};