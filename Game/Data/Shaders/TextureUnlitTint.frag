#version 120
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2D u_Texture;
uniform vec4 u_Color;

varying vec2 v_UV;

void main()
{
	vec4 textureColor = texture2D( u_Texture, v_UV );
	vec3 finalColor = textureColor.xyz * u_Color.xyz;

	gl_FragColor = vec4(finalColor, textureColor.a);
}
