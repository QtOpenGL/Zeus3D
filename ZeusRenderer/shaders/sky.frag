#version 330 core
#extension GL_NV_shadow_samplers_cube : enable
uniform samplerCube textureSky;

in vec3 texCoord;

layout (location = 0) out vec3 FragPos;
layout (location = 1) out vec4 FragTex;
layout (location = 2) out vec3 FragNormal;
layout (location = 3) out vec3 FragSpec;

void main() {
	FragTex = textureCube(textureSky, texCoord);
	FragPos = vec3(10000.0);
	FragSpec = vec3(0.0f,0.0f,0.0f);
	FragNormal = vec3(1.0);
}