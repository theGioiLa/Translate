#include "stdafx.h"
#include "Camera.h"

void Camera::CalculateRotation() {
	Vector3 zaxis = (m_Position - m_Target).Normalize();
	Vector3 xaxis = (m_vUp.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();
	
	m_RotationMatrix.m[0][0] = xaxis.x;
	m_RotationMatrix.m[0][1] = xaxis.y;
	m_RotationMatrix.m[0][2] = xaxis.z;
	m_RotationMatrix.m[0][3] = 0;

	m_RotationMatrix.m[1][0] = yaxis.x;
	m_RotationMatrix.m[1][1] = yaxis.y;
	m_RotationMatrix.m[1][2] = yaxis.z;
	m_RotationMatrix.m[1][3] = 0;

	m_RotationMatrix.m[2][0] = zaxis.x;
	m_RotationMatrix.m[2][1] = zaxis.y;
	m_RotationMatrix.m[2][2] = zaxis.z;
	m_RotationMatrix.m[2][3] = 0;

	m_RotationMatrix.m[3][0] = 0;
	m_RotationMatrix.m[3][1] = 0;
	m_RotationMatrix.m[3][2] = 0;
	m_RotationMatrix.m[3][3] = 1;
	
}

void Camera::CalculateTranslation() {
	m_TranslationMatrix.SetTranslation(m_Position);
}

Matrix Camera::CalculateWorldMatrix() {
	if (isChanged) {
		if (!isRotation) {
			CalculateTranslation();
			isRotation = true;
		}

		CalculateRotation();
		isChanged = false;
	}

	m_WorldMatrix = m_RotationMatrix * m_TranslationMatrix;
	return m_WorldMatrix;
}

Matrix Camera::CalculateViewMatrix() {
	if (isChanged) {
		if (!isRotation) {
			CalculateTranslation();
			isRotation = true;
		}

		CalculateRotation();
		isChanged = false;
	}

	Matrix T_flip = m_TranslationMatrix;
	T_flip.m[3][0] = -m_Position.x;
	T_flip.m[3][1] = -m_Position.y;
	T_flip.m[3][2] = -m_Position.z;

	Matrix R_flip = m_RotationMatrix.Transpose();
		
	m_ViewMatrix = T_flip * R_flip;
	return m_ViewMatrix;
}

void Camera::MoveForward(GLfloat distance) {
	isChanged = true;
	Vector3 deltaMove = -(m_Position - m_Target).Normalize() * distance;
	m_Position += deltaMove;
	m_Target += deltaMove;
}

void Camera::MoveBackward(GLfloat distance) {
	isChanged = true;
	Vector3 deltaMove = (m_Position - m_Target).Normalize() * distance;
	m_Position += deltaMove;
	m_Target += deltaMove;
}

void Camera::MoveLeft(GLfloat distance) {
	isChanged = true;
	Vector3 deltaMove = -Vector3(distance, 0, 0);
	m_Position += deltaMove;
	m_Target += deltaMove;
}

void Camera::MoveRight(GLfloat distance) {
	isChanged = true;
	Vector3 deltaMove = Vector3(distance, 0, 0);
	m_Position += deltaMove;
	m_Target += deltaMove;
}

void Camera::MoveUp(GLfloat distance) {
	isChanged = true;
	Vector3 deltaMove = Vector3(0, distance, 0);
	m_Position += deltaMove;
	m_Target += deltaMove;
}

void Camera::MoveDown(GLfloat distance) {
	isChanged = true;
	Vector3 deltaMove = -Vector3(0, distance, 0);
	m_Position += deltaMove;
	m_Target += deltaMove;
}

void Camera::RotateLeft(GLfloat phi) {
	isChanged = true;
	isRotation = true;
	Vector4 newUp = Vector4(m_vUp, 0) * m_ViewMatrix;
	m_vUp = Vector3(newUp.x, newUp.y, newUp.z);
	CalculateWorldMatrix();

	Vector4 localTarget = Vector4(0, 0, -(m_Position - m_Target).Length(), 1);
	Vector4 newLocalTarget = localTarget * Matrix().SetRotationY(phi);
	Vector4 newWorldTarget = newLocalTarget * m_WorldMatrix;
	m_Target = Vector3(newWorldTarget.x, newWorldTarget.y, newWorldTarget.z);
}

void Camera::RotateRight(GLfloat phi) {
	isChanged = true;
	isRotation = true;
	Vector4 newUp = Vector4(m_vUp, 0) * m_ViewMatrix;
	m_vUp = Vector3(newUp.x, newUp.y, newUp.z);
	CalculateWorldMatrix();

	Vector4 localTarget = Vector4(0, 0, -(m_Position - m_Target).Length(), 1);
	Vector4 newLocalTarget = localTarget * Matrix().SetRotationY(-phi);
	Vector4 newWorldTarget = newLocalTarget * m_WorldMatrix;
	m_Target = Vector3(newWorldTarget.x, newWorldTarget.y, newWorldTarget.z);
}