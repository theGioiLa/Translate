#pragma once 
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Globals.h"

class Camera {
protected:
	Matrix m_WorldMatrix, m_ViewMatrix, m_RotationMatrix, m_TranslationMatrix, m_ProjectionMatrix;
	Vector3 m_Position, m_Target;
	GLfloat m_Velocity = 3.5f;
	GLfloat m_AngularVelocity = 2.0f;

	Vector3 m_vUp;
	GLboolean isMoved, isRotation;

	void CalculateRotation();
	void CalculateTranslation();

public:
	Camera() : m_Position(Vector3(0.0f, 0.0f, 0.0f)),
		m_Target(Vector3(0.0f, 0.0f, -1.0f)), m_vUp(Vector3(0.0f, 1.0f, 0.0f)), isMoved(false),
		isRotation(false) {
		CalculateRotation();
		CalculateTranslation();
		UpdateWorldMatrix();
		UpdateViewMatrix();
	}

	void MoveAlongLocalX(GLfloat deltaTime);
	void MoveAlongLocalY(GLfloat deltaTime);
	void MoveAlongLocalZ(GLfloat deltaTime);

	void RotateAroundLocalX(GLfloat deltaTime);
	void RotateAroundWorldY(GLfloat deltaTime);
	void RotateAroundLocalZ(GLfloat deltaTime);

	Matrix UpdateWorldMatrix();
	Matrix UpdateViewMatrix();

	Matrix GetViewMatrix() { return m_ViewMatrix; }
	Matrix GetProjectionMatrix() { return m_ProjectionMatrix; }

	void SetProjectionMatrix(float fov, float nearP, float farP) {
		m_ProjectionMatrix = Matrix().SetPerspective(fov, static_cast<float>(Globals::screenWidth) / Globals::screenHeight, nearP, farP);
	}

	void SetSpeed(float speed) {
		m_Velocity = speed;
		m_AngularVelocity = speed;
	}

	~Camera() {}

};