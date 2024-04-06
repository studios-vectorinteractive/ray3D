#version 460 core

layout(location = 0) in vec3 In_Position;
layout(location = 1) in vec3 In_Color;

out vec3 Color;

void main()
{
	gl_Position = vec4(In_Position, 1.0f);
	Color = In_Color;
}