precision mediump float;

varying vec3 v_pos;
uniform samplerCube u_samplerCube;

void main() 
{
    gl_FragColor = textureCube(u_samplerCube, v_pos);
    //gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}