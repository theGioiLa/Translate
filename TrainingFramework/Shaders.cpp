#include "stdafx.h"
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	return 0;
}

int Shaders::Init() {
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVS);

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFS);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);
	FindUniformsAndAttributesLoc(); 

	return 0;
}

void Shaders::FindUniformsAndAttributesLoc() {
	positionAttribute = glGetAttribLocation(program, "a_pos");
	texcoordAttribute = glGetAttribLocation(program, "a_uv");

	mvpUniform = glGetUniformLocation(program, "mvp_matrix");
	sampler2DLoc = glGetUniformLocation(program, "u_texture");
	samplerCubeLoc = glGetUniformLocation(program, "u_samplerCube");

	baseTexLoc = glGetUniformLocation(program, "baseTex");
	tex1Loc = glGetUniformLocation(program, "texture1");
	tex2Loc = glGetUniformLocation(program, "texture2");
	tex3Loc = glGetUniformLocation(program, "texture3");
}

Shaders::~Shaders()
{
	delete[] fileVS; fileVS = nullptr;
	delete[] fileFS; fileFS = nullptr;
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}