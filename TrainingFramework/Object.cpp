#include "stdafx.h"
#include "Object.h"

int Object::Init() {
	GLint program = m_pShader->program;
	glEnable(m_pShader->states);

	if (m_LCubTexes.size() == 0) {
		texcoordAttribute = glGetAttribLocation(program, "a_uv");
		texcoordUniform = glGetUniformLocation(program, "u_texture");

		std::vector<Texture*>::iterator itTex2D = m_LTextures.begin();
		for (; itTex2D != m_LTextures.end(); itTex2D++) {
			if ((*itTex2D)->isOn()) {
				(*itTex2D)->Init();
			}
		}

	} else {
		std::vector<Texture*>::iterator itTex2D = m_LTextures.begin();
		for (; itTex2D != m_LTextures.end(); itTex2D++) (*itTex2D)->SetActicve(false);
		
		std::vector<Texture*>::iterator itCubTex = m_LCubTexes.begin();
		for (; itCubTex != m_LCubTexes.end(); itCubTex++) {
			if ((*itCubTex)->isOn()) {
				(*itCubTex)->Init();
			}
		}
	}

	if (m_pModel->Init(program) != 0) return -1;
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
	for (; itTex2D != m_LTextures.end(); itTex2D++) {
		if ((*itTex2D)->isOn()) {
			glBindBuffer(GL_TEXTURE_2D, (*itTex2D)->m_textureId);
			glBindBuffer(GL_ARRAY_BUFFER, m_pModel->m_vboId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->m_iboId);

			if (m_pModel->mvpUniform != -1) {
				glUniform1i(m_pModel->mvpUniform, 1);
				glUniformMatrix4fv(m_pModel->mvpUniform, 1, GL_FALSE, &m_TransformMtx.m[0][0]);
			}

			if (m_pModel->positionAttribute != -1) {
				glEnableVertexAttribArray(m_pModel->positionAttribute);
				glVertexAttribPointer(m_pModel->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			}

			if (texcoordAttribute != -1) {
				glUniform1i(texcoordAttribute, 0);
				glEnableVertexAttribArray(texcoordAttribute);
				glVertexAttribPointer(texcoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
			}

			glDrawElements(GL_TRIANGLES, m_pModel->m_nIndices, GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(m_pModel->positionAttribute);
			glDisableVertexAttribArray(texcoordAttribute);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

}

void Object::DrawEnv() {
	std::vector<Texture*>::iterator itCubeTex = m_LCubTexes.begin();
	for (; itCubeTex != m_LCubTexes.end(); itCubeTex++) {
		if ((*itCubeTex)->isOn()) {
			glBindTexture(GL_TEXTURE_CUBE_MAP, (*itCubeTex)->m_textureId);
			glBindBuffer(GL_ARRAY_BUFFER, m_pModel->m_vboId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->m_iboId);

			if (m_pModel->mvpUniform != -1) {
				glUniform1i(m_pModel->mvpUniform, 1);
				glUniformMatrix4fv(m_pModel->mvpUniform, 1, GL_FALSE, &m_TransformMtx.m[0][0]);
			}

			if (m_pModel->positionAttribute != -1) {
				glEnableVertexAttribArray(m_pModel->positionAttribute);
				glVertexAttribPointer(m_pModel->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			}

			glDrawElements(GL_TRIANGLES, m_pModel->m_nIndices, GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(m_pModel->positionAttribute);

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