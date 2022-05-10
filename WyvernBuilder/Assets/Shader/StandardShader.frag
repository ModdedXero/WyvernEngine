#version 460 core

out vec4 FragColor;
out int EntityColor;

in vec4 vColor;
in vec2 vTexCoord;
in float vTexIndex;
in int vEntityID;

uniform sampler2D uTextures[32];

void main()
{
	int index = int(vTexIndex);
	FragColor = texture(uTextures[index], vTexCoord) * vColor;
	EntityColor = vEntityID;
}