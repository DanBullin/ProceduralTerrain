#version 440 core
			
layout(location = 0) out vec4 colour;

in vec2 texCoord;
in flat int texUnit;
in vec4 tint;

layout(std140) uniform LightSpace
{
	mat4 u_lightSpaceMatrix;
	float u_nearPlane;
	float u_farPlane;
};


uniform sampler2D[16] u_textures;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_nearPlane * u_farPlane) / (u_farPlane + u_nearPlane - z * (u_farPlane - u_nearPlane));	
}

void main()
{
    float depthValue = texture(u_textures[texUnit], texCoord).r;
    //colour = vec4(vec3(LinearizeDepth(depthValue) / u_farPlane), 1.0); // perspective
    colour = vec4(vec3(depthValue), 1.0); // orthographic
}