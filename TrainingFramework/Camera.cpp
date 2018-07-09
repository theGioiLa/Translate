#include "stdafx.h"
#include "Camera.h"

void Camera::CalculateRotation() {
	Vector3 axisZ = (m_Position - m_Target).Normalize();
	Vector3 axisX = (m_vUp.Cross(axisZ)).Normalize();
	Vector3	axisY = (axisZ.Cross(axisX)).Normalize();

	m_RotationMatrix.m[0][0] = axisX.x;
	m_RotationMatrix.m[0][1] = axisX.y;
	m_RotationMatrix.m[0][2] = axisX.z;
	m_RotationMatrix.m[0][3] = 0;

	m_RotationMatrix.m[1][0] = axisY.x;
	m_RotationMatrix.m[1][1] = axisY.y;
	m_RotationMatrix.m[1][2] = axisY.z;
	m_RotationMatrix.m[1][3] = 0;

	m_RotationMatrix.m[2][0] = axisZ.x;
	m_RotationMatrix.m[2][1] = axisZ.y;
	m_RotationMatrix.m[2][2] = axisZ.z;
	m_RotationMatrix.m[2][3] = 0;

	m_RotationMatrix.m[3][0] = 0;
	m_RotationMatrix.m[3][1] = 0;
	m_RotationMatrix.m[3][2] = 0;
	m_RotationMatrix.m[3][3] = 1;

}

void Camera::CalculateTranslation() {
	m_TranslationMatrix.SetTranslation(m_Position);
}

Matrix Camera::UpdateWorldMatrix() {
	if (isMoved) {
		if (!isRotation) CalculateTranslation();
		CalculateRotation();
		isMoved = false;
	}

	m_WorldMatrix = m_RotationMatrix * m_TranslationMatrix;
	return m_WorldMatrix;
}

Matrix Camera::UpdateViewMatrix() {
	if (isMoved) {
		if (!isRotation) CalculateTranslation();
		CalculateRotation();
	}

	Matrix T_flip = m_TranslationMatrix;
	T_flip.m[3][0] = -m_Position.x;
	T_flip.m[3][1] = -m_Position.y;
	T_flip.m[3][2] = -m_Position.z;

	Matrix R_flip = m_RotationMatrix.Transpose();

	m_ViewMatrix = T_flip * R_flip;
	return m_ViewMatrix;
}

void Camera::MoveAlongLocalZ(GLfloat deltaTime) {
	isMoved = true;
	Vector3 direction = (m_Position - m_Target).Normalize();
	Vector3 deltaMove = direction * m_Velocity * deltaTime;

	m_Position += deltaMove;
	m_Target += deltaMove;

	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::MoveAlongLocalX(GLfloat deltaTime) {
	isMoved = true;
	Vector3 direction = (m_vUp.Cross(m_Position - m_Target)).Normalize();
	Vector3 deltaMove = direction * m_Velocity * deltaTime;

	m_Position += deltaMove;
	m_Target += deltaMove;

	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::MoveAlongLocalY(GLfloat deltaTime) {
	isMoved = true;
	Vector3 direction = ((m_Position - m_Target).Cross(m_vUp.Cross(m_Position - m_Target))).Normalize();
	Vector3 deltaMove = direction * m_Velocity * deltaTime;

	m_Position += deltaMove;
	m_Target += deltaMove;

	UpdateWorldMatrix();
	UpdateViewMatrix();
}

//Rotate camera around local X 360 degree
void Camera::RotateAroundLocalX(GLfloat deltaTime) {
	isMoved = true;
	isRotation = true;

	Vector4 localTarget = Vector4(0, 0, -(m_Position - m_Target).Length(), 1);
	Vector4 newLocalTarget = localTarget * Matrix().SetRotationX(m_AngularVelocity * deltaTime);
	Vector4 newWorldTarget = newLocalTarget * m_WorldMatrix;
	m_Target.x = newWorldTarget.x; m_Target.y = newWorldTarget.y; m_Target.z = newWorldTarget.z;

	Vector4 localUp = Vector4(m_vUp, 0) * m_ViewMatrix;
	Vector4 newLocalUp = localUp * Matrix().SetRotationX(m_AngularVelocity * deltaTime);
	Vector4 newWorldUp = newLocalUp * m_WorldMatrix;
	m_vUp.x = newWorldUp.x; m_vUp.y = newWorldUp.y; m_vUp.z = newWorldUp.z;

	UpdateWorldMatrix();
	UpdateViewMatrix();

	isRotation = false;
}

void Camera::RotateAroundWorldY(GLfloat deltaTime) {
	isMoved = true;
	isRotation = true;

	Vector4 localTarget = Vector4(0, 0, -(m_Position - m_Target).Length(), 1);
	Vector4 rotationalAxis = Vector4(m_vUp, 0) * m_ViewMatrix;
	Vector4 newLocalTarget = localTarget * Matrix().SetRotationAngleAxis(m_AngularVelocity * deltaTime, rotationalAxis.x, rotationalAxis.y, rotationalAxis.z);
	Vector4 newWorldTarget = newLocalTarget * m_WorldMatrix;

	m_Target.x = newWorldTarget.x;
	m_Target.y = newWorldTarget.y;
	m_Target.z = newWorldTarget.z;

	UpdateWorldMatrix();
	UpdateViewMatrix();
	isRotation = false;
}

void Camera::RotateAroundLocalZ(GLfloat deltaTime) {
	isMoved = true;
	isRotation = true;

	Vector4 localUp = Vector4(m_vUp, 0) * m_ViewMatrix;
	Vector4 newLocalUp = localUp * Matrix().SetRotationZ(m_AngularVelocity * deltaTime);
	Vector4 newWorldUp = newLocalUp * m_WorldMatrix;
	m_vUp.x = newWorldUp.x; m_vUp.y = newWorldUp.y; m_vUp.z = newWorldUp.z;

	UpdateWorldMatrix();
	UpdateViewMatrix();
	isRotation = false;
}