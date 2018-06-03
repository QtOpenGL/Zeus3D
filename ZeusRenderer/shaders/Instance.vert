#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texcoord;
layout (location = 3) in vec3 color;
layout (location = 4) in mat4 instanceMatrix;

uniform mat4 viewProjectMatrix;

out vec3 vTexcoord;
out vec3 vPos;
out vec3 vColor;
out vec3 vNormal;


void main() {
	vNormal = vec3(instanceMatrix * vec4(normal,0.0f));
	vTexcoord = texcoord;
	float af = 0.6; float df = 1.2;
	vColor = vec3(af, df, 1.0) * color * 0.005;
	vec4 tmp = instanceMatrix * vec4(position,1.0f);
	vPos = tmp.xyz;
	gl_Position = viewProjectMatrix * tmp;
}
