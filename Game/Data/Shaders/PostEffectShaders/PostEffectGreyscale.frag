#version 120
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2D u_Texture;
uniform vec2 u_WindowSize;
uniform vec2 u_TextureSize;

varying vec2 v_UV;

void main()
{
	vec2 windowRatio = u_WindowSize / u_TextureSize;
	vec4 textureColor = texture2D( u_Texture, v_UV * windowRatio);
		
	float biggest = max(textureColor.r,textureColor.g);
	biggest = max(biggest, textureColor.b);

	textureColor.r = biggest;
	textureColor.g = biggest;
	textureColor.b = biggest;

	gl_FragColor = textureColor;
}
