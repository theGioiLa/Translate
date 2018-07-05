#include "stdafx.h"
#include "Object.h"
extern Matrix viewMatrix;
extern Matrix projectionMatrix;

void Object::Init(char* fileTGA, char* fileNFG, GLenum textureType) {
	m_Skin.Init(fileTGA, textureType);

	m_Model.Init(fileNFG);
	m_Model.BindData();
}

void Object::Draw(ObjShaders& shaders) {
	glUseProgram(shaders.program);

	glBindTexture(GL_TEXTURE_2D, m_Skin.m_textureId);
	glBindBuffer(GL_ARRAY_BUFFER, m_Model.m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Model.m_iboId);
	
	if (shaders.mvpUniform != -1) {
		glUniform1i(shaders.mvpUniform, 1);
		glUniformMatrix4fv(shaders.mvpUniform, 1, GL_FALSE, &m_transformMtx.m[0][0]);
	}

	if (shaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(shaders.positionAttribute);
		glVertexAttribPointer(shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shaders.texcoordAttribute != -1)
	{
		glUniform1i(shaders.texcoordUniform, 0);
		glEnableVertexAttribArray(shaders.texcoordAttribute);
		glVertexAttribPointer(shaders.texcoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	glDrawElements(GL_TRIANGLES, m_Model.m_nIndices, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(shaders.positionAttribute);
	glDisableVertexAttribArray(shaders.texcoordAttribute);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Object::CleanUp() {
	m_Model.CleanUp();
	m_Skin.CleanUp();
}

void Object::CalculateTransformMatrix() {
	Matrix T = Matrix().SetTranslation(m_Position);

	Matrix Rz = Matrix().SetRotationZ(m_RotationalAngle.z);
	Matrix Rx = Matrix().SetRotationX(m_RotationalAngle.x);
	Matrix Ry = Matrix().SetRotationY(m_RotationalAngle.y);
	Matrix R = Rz * Rx * Ry;

	Matrix S = Matrix().SetScale(m_Scale);

	m_transformMtx = S * R * T * viewMatrix * projectionMatrix;
}