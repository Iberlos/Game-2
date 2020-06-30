#version 120
#extension GL_EXT_gpu_shader4 : enable

varying vec4 v_Color;

void main()
{
	gl_FragColor = v_Color;
}