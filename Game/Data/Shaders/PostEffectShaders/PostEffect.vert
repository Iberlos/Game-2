#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;
attribute vec3 a_Normal;

uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;

varying vec2 v_UV;

void main()
{
	vec4 objectPos = vec4( 2 * a_Position, 1.0 );
    gl_Position = objectPos;
	v_UV = a_UV * u_UVScale + u_UVOffset;
}
