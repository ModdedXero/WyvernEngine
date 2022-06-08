##VERTEX##
#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 vTexCoords;

void main()
{
	vTexCoords = aTexCoords;
	gl_Position = vec4(aPos, 0.0, 1.0);
}

##FRAGMENT##
#version 460 core

out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D screenTexture;

void main()
{
	vec3 col = texture(screenTexture, vTexCoords).rgb;
	FragColor = vec4(col, 1.0);
}