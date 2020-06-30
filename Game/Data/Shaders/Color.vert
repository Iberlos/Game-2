#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;
attribute vec3 a_Normal;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform vec4 u_Color;

uniform mat4 u_RotationMatrix;

varying vec2 v_UV;
varying vec4 v_Color;
varying vec4 v_SurfacePos;
varying vec3 v_ObjectSpaceSurfacePos;
varying vec3 v_Normal;

void main()
{
	vec4 objectPos = vec4( a_Position, 1.0 );
	v_ObjectSpaceSurfacePos = (u_RotationMatrix * objectPos).xyz;
	vec4 worldPos = u_WorldMatrix * objectPos;
	v_SurfacePos = worldPos;
	vec4 viewPos = u_ViewMatrix * worldPos;
	vec4 clipPos = u_ProjectionMatrix * viewPos;

    gl_Position = clipPos;

	v_Color = a_Color;
	v_Normal = (u_RotationMatrix * vec4(a_Normal,0.0)).xyz;
}
