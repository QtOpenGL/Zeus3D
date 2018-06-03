#version 330
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texcoord;
layout (location = 3) in vec3 color;
layout (location = 4) in vec4 boneids;
layout (location = 5) in vec4 weights;

uniform mat4 viewProjectMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
uniform mat4 boneMatrix[100];

out vec3 vTexcoord;
out vec3 vPos;
out vec3 vColor;
out vec3 vNormal;
const float af = 0.6f;
const float df = 1.2f;

void main() {	
	mat4 boneMat;
	boneMat  = boneMatrix[int(boneids.x)] * weights.x;
	boneMat += boneMatrix[int(boneids.y)] * weights.y;
	boneMat += boneMatrix[int(boneids.z)] * weights.z;
	boneMat += boneMatrix[int(boneids.w)] * weights.w;
	vec4 position = boneMat * vec4(vertex, 1.0);

	float af = 0.6; float df = 1.2;
	vColor = vec3(af, df, 1.0) * color * 0.005;

	vec4 tmpNorm = boneMat * vec4(normal,0.0f);
	vNormal = vec3(normalMatrix * tmpNorm);

	vTexcoord = texcoord; 
	vTexcoord.y = 1.0f - texcoord.y; 
	vec4 tmp = modelMatrix * position;
	vPos = tmp.xyz;
	gl_Position = viewProjectMatrix * modelMatrix * position;
}
