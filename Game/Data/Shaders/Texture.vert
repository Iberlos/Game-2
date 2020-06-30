#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;
attribute vec3 a_Normal;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;

uniform mat4 u_RotationMatrix;

varying vec2 v_UV;
varying vec4 v_SurfacePos;
varying vec3 v_Normal;

void main()
{
	vec4 objectPos = vec4( a_Position, 1.0 );
	vec4 worldPos = u_WorldMatrix * objectPos;
	v_SurfacePos = worldPos;
	vec4 viewPos = u_ViewMatrix * worldPos;
	vec4 clipPos = u_ProjectionMatrix * viewPos;

    gl_Position = clipPos;

	v_Normal = (u_RotationMatrix * vec4(a_Normal,0.0f)).xyz;

	v_UV = a_UV * u_UVScale + u_UVOffset;
}
