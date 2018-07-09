#include "stdafx.h"
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
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

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	return 0;
}

Shaders::~Shaders()
{
	delete[] fileVS; fileVS = nullptr;
	delete[] fileFS; fileFS = nullptr;
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}