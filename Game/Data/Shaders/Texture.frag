#version 120
#extension GL_EXT_gpu_shader4 : enable

//MUST BE THE SAME AS IN THE GAME
const int NUM_LIGHTS = 4;

uniform sampler2D u_Texture;
uniform vec3 u_CameraPos;
uniform vec3 u_LightColor[NUM_LIGHTS];
uniform vec3 u_LightPos[NUM_LIGHTS];
uniform float u_LightRange[NUM_LIGHTS];
uniform int u_ActiveLights;

varying vec2 v_UV;
varying vec4 v_Color;
varying vec4 v_SurfacePos;
varying vec3 v_Normal;

//Light Functions
vec3 CalculateDiffuseLight(vec3 lightPos, vec3 lightColor, float lightRange)
{
	vec3 dirLight = lightPos - v_SurfacePos.xyz;
	float falloffPercent = 1-length(dirLight)/max(0,lightRange);
	falloffPercent = min(max(0,falloffPercent), 1);
	falloffPercent = pow(falloffPercent,2);
	float diffusePercent = dot(normalize(dirLight), v_Normal);
	diffusePercent = max(0, diffusePercent);

	return lightColor * diffusePercent * falloffPercent;
}

vec3 CalculateSpecularLight(vec3 lightPos, vec3 lightColor, float lightRange)
{

	vec3 dirLight = lightPos - v_SurfacePos.xyz;
	float falloffPercent = 1-length(dirLight)/max(0,lightRange);
	falloffPercent = min(max(0,falloffPercent), 1);
	falloffPercent = pow(falloffPercent,2);
	//Half-vector specular light approach
//	vec3 dirCamera = u_CameraPos - v_SurfacePos.xyz;
//	vec3 halfDir = dirLight + dirCamera;
//	halfDir = normalize(halfDir);
//	float specularPercent = dot(halfDir, v_Normal);
//	specularPercent = max(0,specularPercent);
//	specularPercent = pow(specularPercent, 40);

	//Reflect method
	vec3 dirFromCamera = normalize(u_CameraPos - v_SurfacePos.xyz);
	//inverse of dirLight as we want from teh light to th surface
	vec3 reflectVec = reflect(-dirLight, v_Normal);
	reflectVec = normalize(reflectVec);
	float specularPercent = dot(reflectVec, dirFromCamera);
	specularPercent = max(0,specularPercent);
	specularPercent = pow(specularPercent, 40);

	return lightColor * specularPercent * falloffPercent;
}


void main()
{
//	vec3 lightColor = vec3(1.0, 0.0, 0.0);
//	vec3 lightPos = vec3(0.0, 2.0, -5.0);
//	float lightRange = 5;
//
//	vec3 dirLight = lightPos - v_SurfacePos.xyz;
//	dirLight = normalize(dirLight);
//	float diffusePercent = dot(dirLight, v_Normal);
//
//	vec3 dirCamera = u_CameraPos - v_SurfacePos.xyz;
//	vec3 halfDir = dirLight + dirCamera;
//	halfDir = normalize(halfDir);
//	float specularPercent = pow(dot(halfDir, v_Normal),20);
//	float falloffPercent = pow(1-length(dirLight)/lightRange,2);
//
//	vec3 finalColor = textureColor.xyz * lightColor * diffusePercent * falloffPercent + specularPercent;
//	finalColor.x = max(0,finalColor.x);
//	finalColor.x = max(0,finalColor.x);
//	finalColor.x = max(0,finalColor.x);
//
//
//	gl_FragColor = vec4(finalColor, textureColor.w);

	vec3 totalDiffuse = vec3(0,0,0);
	vec3 totalSpecular = vec3(0,0,0);
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		int activeBit = int(1 * exp2(i));
		if (bool(activeBit & u_ActiveLights))
		{
			totalDiffuse += CalculateDiffuseLight(u_LightPos[i], u_LightColor[i],u_LightRange[i]);
			totalSpecular += CalculateSpecularLight(u_LightPos[i], u_LightColor[i],u_LightRange[i]);
		}
	}

	vec4 textureColor = texture2D( u_Texture, v_UV );
	vec3 finalColor = textureColor.xyz * totalDiffuse + totalSpecular;

	gl_FragColor = vec4(finalColor, textureColor.a);
}
