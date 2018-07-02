#include "stdafx.h"
#include "ObjShaders.h"

void ObjShaders::FindLocationUA() {
	positionAttribute = glGetAttribLocation(program, "a_posL");
	texcoordAttribute = glGetAttribLocation(program, "a_uv");
	mvpUniform = glGetUniformLocation(program, "mvp_matrix");
	texcoordUniform = glGetUniformLocation(program, "u_texture");
}