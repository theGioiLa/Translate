#pragma once 
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Camera {
protected:
	Matrix m_WorldMatrix, m_ViewMatrix, m_RotationMatrix, m_TranslationMatrix;
	Vector3 m_Position, m_Target;
	
	Vector3 m_vUp;
	GLboolean isChanged, isRotation;

	void CalculateRotation();
	void CalculateTranslation();

public:
	Camera(): m_ViewMatrix(Matrix().SetIdentity()), m_Position(Vector3(0.0f, 0.0f, 0.0f)),
		m_Target(Vector3(0.0f, 0.0f, -1.0f)), m_vUp(Vector3(0.0f, 1.0f, 0.0f)), isChanged(false), isRotation(false) {
		CalculateRotation();
		CalculateTranslation();
	}

	void MoveForward(GLfloat distance);
	void MoveBackward(GLfloat distance);
	void MoveLeft(GLfloat distance);
	void MoveRight(GLfloat distance);
	void MoveUp(GLfloat distance);
	void MoveDown(GLfloat distance);

	void RotateLeft(GLfloat phi);
	void RotateRight(GLfloat phi);
	Matrix CalculateWorldMatrix();
	Matrix CalculateViewMatrix();
};