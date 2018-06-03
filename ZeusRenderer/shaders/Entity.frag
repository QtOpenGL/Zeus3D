#version 330
#extension GL_EXT_texture_array : enable
uniform sampler2DArray image;

in vec3 vPos;
in vec3 vTexcoord;
in vec3 vNormal;
in vec3 vColor;

layout (location = 0) out vec3 FragPos;
layout (location = 1) out vec4 FragTex;
layout (location = 2) out vec3 FragNormal;
layout (location = 3) out vec3 FragSpec;

void main() {
	FragTex = texture2DArray(image,vTexcoord);
	FragPos = vPos;
	FragSpec = vColor;
	FragSpec.b = 1.0f;
	FragNormal = normalize(vNormal) * 0.5 + 0.5;
}