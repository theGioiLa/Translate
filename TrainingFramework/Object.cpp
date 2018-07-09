#include "stdafx.h"
#include "Object.h"

int Object::Init() {
	GLint program = m_pShader->program;
	glEnable(m_pShader->states);

	if (m_LCubTexes.size() == 0) {
		std::vector<Texture*>::iterator itTex2D = m_LTextures.begin();
		for (; itTex2D != m_LTextures.end(); itTex2D++) {
			if ((*itTex2D)->isOn()) {
				(*itTex2D)->Init();
				(*itTex2D)->m_TexUnit++;
			}
		}

	}
	else {
		std::vector<Texture*>::iterator itTex2D = m_LTextures.begin();
		for (; itTex2D != m_LTextures.end(); itTex2D++) (*itTex2D)->SetActicve(false);

		std::vector<Texture*>::iterator itCubTex = m_LCubTexes.begin();
		for (; itCubTex != m_LCubTexes.end(); itCubTex++) {
			if ((*itCubTex)->isOn()) {
				(*itCubTex)->Init();
			}
		}
	}

	if (m_pModel->Init() != 0) return -1;
	m_pModel->BindData();
	return 0;
}

void Object::Draw() {
	glUseProgram(m_pShader->program);
	if (m_LCubTexes.size() == 0) DrawObj();
	else DrawEnv();
}

void Object::DrawObj() {
	std::vector<Texture*>::iterator itTex2D = m_LTextures.begin();
	for (auto& tex : m_LTextures) {
		glActiveTexture(GL_TEXTURE0 + tex->m_TexUnit);
		glBindTexture(GL_TEXTURE_2D, tex->m_TextureId);
		if (m_pShader->sampler2DLoc != -1) {
					glUniform1i(m_pShader->sampler2DLoc, tex->m_TexUnit);
		}
	}
	/*for (int i = 0; i < m_LTextures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_LTextures[i]->m_TextureId);
			
	}*/

	/*for (; itTex2D != m_LTextures.end(); itTex2D++) {
		if ((*itTex2D)->isOn()) {
			glActiveTexture(GL_TEXTURE0 + (*itTex2D)->m_TexUnit);
			glBindTexture(GL_TEXTURE_2D, (*itTex2D)->m_TextureId);
			if (m_pShader->sampler2DLoc != -1) {
				glUniform1i(m_pShader->sampler2DLoc, (*itTex2D)->m_TexUnit);
			}
		}
	}*/

	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->m_iboId);

	int slot = 0;

	if (m_pShader->baseTexLoc != -1) {
		glUniform1i(m_pShader->baseTexLoc, slot++);
	}

	if (m_pShader->tex1Loc != -1) {
		glUniform1i(m_pShader->tex1Loc, slot++);
	}

	if (m_pShader->tex2Loc != -1) {
		glUniform1i(m_pShader->tex2Loc, slot++);
	}

	if (m_pShader->tex3Loc != -1) {
		glUniform1i(m_pShader->tex3Loc, slot);
	}

	if (m_pShader->mvpUniform != -1) {
		glUniformMatrix4fv(m_pShader->mvpUniform, 1, GL_FALSE, &m_TransformMtx.m[0][0]);
	}

	if (m_pShader->positionAttribute != -1) {
		glEnableVertexAttribArray(m_pShader->positionAttribute);
		glVertexAttribPointer(m_pShader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (m_pShader->texcoordAttribute != -1) {
		glEnableVertexAttribArray(m_pShader->texcoordAttribute);
		glVertexAttribPointer(m_pShader->texcoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	glDrawElements(GL_TRIANGLES, m_pModel->m_nIndices, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Object::DrawEnv() {
	std::vector<Texture*>::iterator itCubeTex = m_LCubTexes.begin();
	for (; itCubeTex != m_LCubTexes.end(); itCubeTex++) {
		if ((*itCubeTex)->isOn()) {
			glActiveTexture(GL_TEXTURE0 + (*itCubeTex)->m_TexUnit);
			glBindTexture(GL_TEXTURE_CUBE_MAP, (*itCubeTex)->m_TextureId);
			glBindBuffer(GL_ARRAY_BUFFER, m_pModel->m_vboId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->m_iboId);

			if (m_pShader->samplerCubeLoc != -1) {
				glUniform1i(m_pShader->samplerCubeLoc, (*itCubeTex)->m_TexUnit);
			}

			if (m_pShader->mvpUniform != -1) {
				glUniform1i(m_pShader->mvpUniform, 1);
				glUniformMatrix4fv(m_pShader->mvpUniform, 1, GL_FALSE, &m_TransformMtx.m[0][0]);
			}

			if (m_pShader->positionAttribute != -1) {
				glEnableVertexAttribArray(m_pShader->positionAttribute);
				glVertexAttribPointer(m_pShader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			}

			glDrawElements(GL_TRIANGLES, m_pModel->m_nIndices, GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(m_pShader->positionAttribute);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
	}
}

void Object::SetModel(GLuint modelId) {
	m_pModel = resourceManager->GetModel(modelId);
}

void Object::SetTextures(std::vector<int> texturesID) {
	std::vector<int>::iterator it = texturesID.begin();
	for (; it != texturesID.end(); it++) {
		m_LTextures.push_back(resourceManager->GetTexture(*it));
	}
}

void Object::SetCubeTex(std::vector<int> cubeTexesId) {
	std::vector<int>::iterator it = cubeTexesId.begin();
	for (; it != cubeTexesId.end(); it++) {
		m_LCubTexes.push_back(resourceManager->GetCubeTex(*it));
	}
}

void Object::SetShader(GLuint shaderId) {
	m_pShader = resourceManager->GetShader(shaderId);
}

void Object::UpdateTransformMatrix(Matrix viewMatrix, Matrix projectionMatrix) {
	Matrix T = Matrix().SetTranslation(m_Position);

	Matrix Rz = Matrix().SetRotationZ(m_RotationalAngle.z);
	Matrix Rx = Matrix().SetRotationX(m_RotationalAngle.x);
	Matrix Ry = Matrix().SetRotationY(m_RotationalAngle.y);
	Matrix R = Rz * Rx * Ry;

	Matrix S = Matrix().SetScale(m_Scale);

	m_TransformMtx = S * R * T * viewMatrix * projectionMatrix;
}