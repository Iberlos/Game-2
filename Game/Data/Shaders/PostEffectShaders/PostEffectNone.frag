#version 120
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2D u_Texture;

varying vec2 v_UV;

void main()
{
	vec4 textureColor = texture2D( u_Texture, v_UV );
	gl_FragColor = textureColor;
}
