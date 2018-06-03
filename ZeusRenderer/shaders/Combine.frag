#version 330 core
in vec2 vTexcoord;

uniform sampler2D sceneTexture;
uniform sampler2D bloomTexture;
uniform float exposure;

out vec4 FragColor;

void main()
{             
/*    const float gamma = 2.2;
    vec3 hdrColor = texture(scene, vTexcoord).rgb;      
    vec3 bloomColor = texture(bloomBlur, vTexcoord).rgb;
    hdrColor += bloomColor; // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));*/
	vec3 result = texture(bloomTexture,vTexcoord).xyz;
    FragColor = vec4(result, 1.0f);
}