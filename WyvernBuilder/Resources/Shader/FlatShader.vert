#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

layout (location = 0) out vec4 vColor;

uniform mat4 projection;
uniform mat4 viewModel;

void main()
{
	gl_Position = projection * viewModel * vec4(aPos, 1.0);
	vColor = aColor;
}