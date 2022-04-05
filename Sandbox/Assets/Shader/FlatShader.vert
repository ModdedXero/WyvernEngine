#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float aTexID;

out vec4 vColor;
out vec2 vTexCoord;
out float vTexIndex;

uniform mat4 projection;
uniform mat4 viewModel;

void main()
{
	gl_Position = projection * viewModel * vec4(aPos, 1.0);
	vColor = aColor;
	vTexCoord = aTexCoords;
	vTexIndex = aTexID;
}