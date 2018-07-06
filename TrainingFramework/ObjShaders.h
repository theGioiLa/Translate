#pragma once
#include "Shaders.h"

class ObjShaders : public Shaders {
public:
	GLint positionAttribute, texcoordAttribute;
	GLint texcoordUniform, mvpUniform;

	void FindLocationUA() {
		positionAttribute = glGetAttribLocation(program, "a_posL");
		mvpUniform = glGetUniformLocation(program, "mvp_matrix");
		texcoordAttribute = glGetAttribLocation(program, "a_uv");
		texcoordUniform = glGetUniformLocation(program, "u_texture");
	}
};
