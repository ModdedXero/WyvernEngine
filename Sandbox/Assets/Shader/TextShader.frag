#version 460 core

out vec4 FragColor;

in vec4 vColor;
in vec2 vTexCoord;
in float vTexIndex;

uniform sampler2D uTextures[32];

void main()
{
	int index = int(vTexIndex);
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(uTextures[index], vTexCoord).r);
	FragColor = sampled * vColor;
}