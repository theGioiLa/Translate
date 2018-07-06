#include "stdafx.h"
#include "Model.h"

Model::Model(unsigned int nVertices, unsigned int nIndices) {
	m_nVertices = nVertices;
	m_nIndices = nIndices;

	m_pIndex = new int[nIndices];
	for (int i = 0; i < nIndices; i++) {
		m_pIndex[i] = i;
	}
}

void Model::Init(char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "rb") != 0) return;

	fscanf_s(file, "NrVertices: %d\n", &m_nVertices);

	m_pVertices = new Vertex[m_nVertices];
	for (int i = 0; i < m_nVertices; i++) {
		fscanf_s(file, "%*d. pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];\n",
			&m_pVertices[i].pos.x, &m_pVertices[i].pos.y, &m_pVertices[i].pos.z, &m_pVertices[i].texcoord.x, &m_pVertices[i].texcoord.y);
	}

	fscanf_s(file, "NrIndices: %d\n", &m_nIndices);

	m_pIndex = new int[m_nIndices];
	for (int i = 0; i < m_nIndices; i += 3) {
		fscanf_s(file, "%*d.    %d, %d, %d\n", &m_pIndex[i], &m_pIndex[i + 1], &m_pIndex[i + 2]);
	}

}

void Model::BindData() {
	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_nVertices, m_pVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*m_nIndices, m_pIndex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::CleanUp() {
	delete[] m_pVertices;
	delete[] m_pIndex;
	glDeleteBuffers(1, &m_vboId);
	glDeleteBuffers(1, &m_iboId);
}
