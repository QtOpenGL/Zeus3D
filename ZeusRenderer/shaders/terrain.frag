#version 330 core
in vec2 Texcoord;
in vec3 Normal;
in vec3 Color;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
uniform sampler2D bTexture;
uniform sampler2D blendMap;

out vec4 color;

void main(void) {
    vec4 blendMapColor = texture(blendMap, Texcoord);

    float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);

    vec2 tiledCoords =      Texcoord * 40.0;
    vec4 backgroundTextureColor = texture(backgroundTexture, tiledCoords) * backTextureAmount;
    vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColor.r;
    vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColor.g;
    vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColor.b;

    vec4 totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;
    color = totalColor;
}
