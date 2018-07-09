#include "stdafx.h"
#include "Map.h"

void Map::Init(char* fileTGA, char* fileNFG, GLenum textureType) {
	m_Skin.Init(fileTGA, textureType);

	m_Model.Init(fileNFG);
	m_Model.BindData();
}

void Map::Draw(EnvShaders& shaders) {
	glUseProgram(shaders.program);
	glUniform1i(shaders.mvp_matrix, 1);

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Skin.m_textureId);
	glBindBuffer(GL_ARRAY_BUFFER, m_Model.m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Model.m_iboId);

	if (shaders.mvp_matrix != -1) {
		glUniformMatrix4fv(shaders.mvp_matrix, 1, GL_FALSE, &m_TransformMtx.m[0][0]);
	}

	if (shaders.positionAttribute != -1) {
		glEnableVertexAttribArray(shaders.positionAttribute);
		glVertexAttribPointer(shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	glDrawElements(GL_TRIANGLES, m_Model.m_nIndices, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(shaders.positionAttribute);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}