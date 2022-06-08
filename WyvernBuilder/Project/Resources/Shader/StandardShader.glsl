##VERTEX##
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float aTexID;
layout (location = 4) in int aEntityID;

layout (location = 0) out vec4 vColor;
layout (location = 1) out vec2 vTexCoord;
layout (location = 2) out flat float vTexIndex;
layout (location = 3) out flat int vEntityID;

uniform mat4 projection;
uniform mat4 viewModel;

void main()
{
	gl_Position = projection * viewModel * vec4(aPos, 1.0);
	vColor = aColor;
	vTexCoord = aTexCoords;
	vTexIndex = aTexID;
	vEntityID = aEntityID;
}

##FRAGMENT##
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