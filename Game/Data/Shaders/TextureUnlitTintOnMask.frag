#version 120
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform vec4 u_ColorMask;
uniform float u_Percent;

varying vec2 v_UV;
varying vec3 v_Position;

void main()
{
	vec4 textureColor = texture2D( u_Texture, v_UV );
	vec3 finalColor = textureColor.xyz;
	
	if(finalColor.xyz == u_ColorMask.xyz && (v_UV.y*1.15-0.1) <= u_Percent)
	{
		finalColor *= u_Color.xyz;
	}

	gl_FragColor = vec4(finalColor, textureColor.a);
}
