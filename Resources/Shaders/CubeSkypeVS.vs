attribute vec3 a_pos;
uniform mat4 mvp_matrix;
varying vec3 v_pos;
void main()
{
	gl_Position = mvp_matrix * vec4(a_pos, 1.0);
	v_pos = a_pos;
}