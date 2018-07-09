#include "stdafx.h"
#include "Model.h"

int Model::Init() {
	return BindInfo();
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

int Model::BindInfo() {
	FILE* file;
	if (fopen_s(&file, m_Info, "r") != 0) return -1;

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

	fclose(file);
	return 0;
}

void Model::CleanUp() {
	delete[] m_Info; m_Info = nullptr;
	delete[] m_pVertices; m_pVertices = nullptr;
	delete[] m_pIndex; m_pVertices = nullptr;
	glDeleteBuffers(1, &m_vboId);
	glDeleteBuffers(1, &m_iboId);
}

Model::~Model() {

}