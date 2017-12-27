#version 330
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec4 in_Color;
layout(location = 2) in vec3 VertexNormal;
 
out Data
{
	vec3 Position;
	vec3 Normal;
	vec4 ex_Color;
} data;
 
uniform mat4 ModelViewMatrix;
uniform mat4 NormalMatrix;
uniform mat4 MVP;
 

void main()
{
	data.Normal = normalize(vec3( NormalMatrix * vec4(VertexNormal,0) ) );
	data.Position = vec3( ModelViewMatrix * vec4( VertexPosition, 1 ) );
	data.ex_Color = in_Color;
 
	gl_Position = MVP * vec4( VertexPosition, 1 );
}