#version 460 core

layout(location = 0) in vec3 Color;

out vec4 FragColor;

void main()
{
	FragColor = vec4(Color, 1.0f);
}