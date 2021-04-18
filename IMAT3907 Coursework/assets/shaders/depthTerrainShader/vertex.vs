#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in mat4 aModel;
layout (location = 6) in int aTexUnit;
layout (location = 7) in vec4 aTint;
layout (location = 8) in vec4 aSubTextureUV;

// Interface block for the outputs of the vertex shader
out VS_OUT {
	vec3 FragPos;
} vs_out;

void main()
{
    vs_out.FragPos = vec3(aModel * vec4(aPos, 1.0));
}