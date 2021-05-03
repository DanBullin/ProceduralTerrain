#version 440 core
			
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in VS_OUT {
	vec4 Tint;
	flat int TexUnit;
	vec2 TexCoords;
} fs_in;

uniform sampler2D[16] u_diffuseMap;

void main()
{    
    	FragColor = texture(u_diffuseMap[fs_in.TexUnit], fs_in.TexCoords) * fs_in.Tint;
	BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}