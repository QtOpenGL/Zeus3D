#version 330
layout (location = 0) in vec3 position;
layout (location = 4) in mat4 instanceMatrix;

uniform mat4 lightSpaceMatrix;

void main() {
	vec4 tmp = instanceMatrix * vec4(position,1.0f);
	gl_Position =  lightSpaceMatrix * tmp;
}
