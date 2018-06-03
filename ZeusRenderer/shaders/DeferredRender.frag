#version 330 core
in vec2 vTexcoord;
uniform sampler2D posBuffer;
uniform sampler2D texBuffer;
uniform sampler2D normalBuffer;
uniform sampler2D specBuffer;
uniform sampler2D depthBuffer;
uniform sampler2D shadowBuffer;
uniform vec3 CameraPos;
uniform float nearPlane,farPlane;
uniform mat4 lightSpaceMatrix;

layout (location = 0) out vec4 SceneColor;
layout (location = 1) out vec4 BrightColor;

// parallel lighting
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

// point lighting
struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define MAX_POINT_LIGHTS 100
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightsNum;
uniform float exposure;

struct Fog{
	float fogDensity;
	vec3 fogColor;
};
uniform Fog fog;

// lighting calculation
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 texColor, float shadowFactor);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 texColor);
// depth linearization
float LinearizeDepth(float Depth);
vec3 CalcFog(vec3 texColor,Fog fogEffect,float zPos);
// shadow calculation
float ShadowCalculation(vec3 pos,vec3 normal,vec3 lightDir);
float PcfSampling(vec2 texcoord);
float random(vec3 seed, int i);

void main() {
	vec3 FragColor;
	// get texture info
	vec3 FragPos = texture(posBuffer,vTexcoord).rgb;
	vec3 Normal = texture(normalBuffer,vTexcoord).rgb;
	Normal = (Normal - 0.5f)*2.0f;
	vec3 TexColor = texture(texBuffer,vTexcoord).rgb;
	vec3 ViewDir = normalize(CameraPos - FragPos);

	// 1. shadow calculation
	float shadowFactor = ShadowCalculation(FragPos,Normal,dirLight.direction);

	// 2.parallel lighting
	FragColor = CalcDirLight(dirLight,Normal,ViewDir,TexColor,shadowFactor);

	// 3.point lighting
	float factor = texture(specBuffer,vTexcoord).b;
	for(int i = 0;i < pointLightsNum;++i){
		FragColor += factor*CalcPointLight(pointLights[i],Normal,ViewDir,FragPos,TexColor);
	}

	// 5. calc fog effect
	FragColor = CalcFog(FragColor,fog,texture(depthBuffer,vTexcoord).r);

	// extract bright part
	//float brightness = dot(FragColor, vec3(0.7152, 0.2126, 0.0722));
   //if(brightness > 0.7)
		BrightColor = vec4(FragColor,1.0f);
	SceneColor = vec4(FragColor,1.0f);
	
/*	BrightColor = FragColor-vec3(1.0f);*/

	// 6.hdr
	//FragColor = vec3(1.0f) - exp(-FragColor*exposure);

	// 7.gamma correction
	//const float gamma = 2.2f;
	//FragColor = pow(FragColor,vec3(1.0/gamma));
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 texColor, float shadowFactor)
{
    vec3 lightDir = normalize(light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // 合并结果
    vec3 ambient  = light.ambient  * texColor;
    vec3 diffuse  = light.diffuse  * diff * texColor;
    vec3 specular = light.specular * spec * texColor;
    return (ambient + (diffuse + specular)*(shadowFactor));
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 texColor)
{
	 vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                 light.quadratic * (distance * distance));    
    // 合并结果
    vec3 ambient  = light.ambient  * texColor;
    vec3 diffuse  = light.diffuse  * diff * texColor;
    vec3 specular = light.specular * spec * texColor;
    return (ambient + diffuse + specular)*attenuation;
}

float LinearizeDepth(float Depth){
	float z = Depth * 2.0 - 1.0; // back to NDC 
	return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}

vec3 CalcFog(vec3 texColor,Fog fogEffect,float zPos)
{
	float fogDist = LinearizeDepth(zPos);
	const float LOG2E = 1.442695;
	float factor = exp2(-fogEffect.fogDensity * fogEffect.fogDensity * fogDist * fogDist *LOG2E);
	factor = clamp(factor,0.0,1.0);
	return mix(fogEffect.fogColor,texColor,factor);
}

// poisson sampling
vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);

float ShadowCalculation(vec3 pos,vec3 normal,vec3 lightDir)
{
	vec4 fragPosLightSpace = lightSpaceMatrix*vec4(pos,1.0f);
	vec3 projCoords = fragPosLightSpace.xyz;
	projCoords = projCoords*0.5 + 0.5;
	float currentDepth = projCoords.z;
	float bias = max(0.05*(1.0-dot(normal,lightDir)),0.000);
	float shadowFactor = 1.0;
	float mag = 0.00143;
	int index = 0;
	index = int(16.0 * random(gl_FragCoord.xyy, 0)) % 16;
	if(PcfSampling(projCoords.xy+poissonDisk[index]*mag) <= (currentDepth - bias))shadowFactor -= 0.25f;
	index = int(16.0 * random(gl_FragCoord.xyy, 1)) % 16;
	if(PcfSampling(projCoords.xy+poissonDisk[index]*mag) <= (currentDepth - bias))shadowFactor -= 0.25f;
	index = int(16.0 * random(gl_FragCoord.xyy, 2)) % 16;
	if(PcfSampling(projCoords.xy+poissonDisk[index]*mag) <= (currentDepth - bias))shadowFactor -= 0.25f;
	index = int(16.0 * random(gl_FragCoord.xyy, 3)) % 16;
	if(PcfSampling(projCoords.xy+poissonDisk[index]*mag) <= (currentDepth - bias))shadowFactor -= 0.25f;
	if(projCoords.z > 1.0) shadowFactor = 0.0;
	return shadowFactor;
}

float PcfSampling(vec2 texcoord)
{
	return texture(shadowBuffer,texcoord).r;
}

// gen random number
float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898, 78.233, 45.164, 94.673));
	return fract(sin(dot_product) * 43758.5453);
}