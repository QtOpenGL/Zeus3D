#version 330
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec4 boneids;
layout (location = 2) in vec4 weights;

uniform mat4 lightSpaceMatrix;
uniform mat4 modelMatrix;
uniform mat4 boneMatrix[100];

void main() {	
	mat4 boneMat;
	boneMat  = boneMatrix[int(boneids.x)] * weights.x;
	boneMat += boneMatrix[int(boneids.y)] * weights.y;
	boneMat += boneMatrix[int(boneids.z)] * weights.z;
	boneMat += boneMatrix[int(boneids.w)] * weights.w;
	vec4 position = boneMat * vec4(vertex, 1.0);
	gl_Position =  lightSpaceMatrix * modelMatrix * position;
}
