attribute vec3 a_posL;
uniform mat4 mvp_matrix;
attribute vec2 a_uv;
varying vec2 v_uv;
void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = mvp_matrix * posL;
	v_uv = a_uv;
}
   