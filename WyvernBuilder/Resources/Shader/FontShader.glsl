##VERTEX##
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
	gl_Position = projection * vec4(aPos, 1.0);
	vColor = aColor;
	vTexCoord = aTexCoords;
	vTexIndex = aTexID;
}

##FRAGMENT##
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
	FragColor = sampled;
}