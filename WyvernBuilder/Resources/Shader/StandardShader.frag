#version 460 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out int EntityColor;

layout (location = 0) in vec4 vColor;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in flat float vTexIndex;
layout (location = 3) in flat int vEntityID;

layout (binding = 0) uniform sampler2D uTextures[32];

void main()
{
	int index = int(vTexIndex);
	
	FragColor = texture(uTextures[index], vTexCoord) * vColor;
	EntityColor = vEntityID;
}