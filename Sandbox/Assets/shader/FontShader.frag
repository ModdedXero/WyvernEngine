#version 460 core

out vec4 FragColor;

in vec4 vColor;
in vec2 vTexCoord;
in float vTexIndex;

uniform sampler2D uTextures[32];

void main()
{
	int index = int(vTexIndex);
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uTextures[index], vTexCoord).r);
	FragColor = vColor * sampled;
}