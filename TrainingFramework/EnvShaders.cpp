#include "stdafx.h"
#include "EnvShaders.h"

void EnvShaders::FindLocationUA() {
	positionAttribute = glGetAttribLocation(program, "a_pos");
	mvp_matrix = glGetUniformLocation(program, "mvp_matrix");
}