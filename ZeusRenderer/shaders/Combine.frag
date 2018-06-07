#version 330 core
in vec2 vTexcoord;

uniform sampler2D sceneTexture;
uniform sampler2D bloomTexture;
uniform float exposure;

out vec4 FragColor;

void main()
{             
	vec3 result = texture(sceneTexture,vTexcoord).xyz + texture(bloomTexture,vTexcoord).xyz;
	result = vec3(1.0) - exp(-result * 1.0);
/*	const float gamma = 2.2;
	result = pow(result, vec3(1.0 / gamma));*/
	FragColor = vec4(result, 1.0f);
}	