#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texcoord;
layout (location = 3) in vec3 color;
layout (location = 4) in float objectid;

uniform mat4 modelMatrices[100];
uniform mat4 viewProjectMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

out vec3 vTexcoord;
out vec3 vPos;
out vec3 vColor;
out vec3 vNormal;
const float af = 0.6f;
const float df = 1.2f;

void main() {	
	float af = 0.6; float df = 1.2;
	vColor = vec3(af, df, 1.0) * color * 0.005;
	vNormal = vec3(normalMatrix * vec4(normal,0.0f));
	vTexcoord = texcoord;
	vec4 tmp = modelMatrix * vec4(position,1.0f);
	vPos = tmp.xyz;
	gl_Position = viewProjectMatrix * tmp;
}