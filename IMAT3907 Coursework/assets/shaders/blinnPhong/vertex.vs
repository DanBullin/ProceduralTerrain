#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in mat4 aModel;
layout (location = 9) in int aTexUnit1;
layout (location = 10) in int aTexUnit2;
layout (location = 11) in vec4 aTint;
layout (location = 12) in float aShininess;
layout (location = 13) in vec4 aSubTextureUV;

float hash(float n);
float snoise(vec3 x);
float noise(vec3 position, int octaves);

// Interface block for the outputs of the vertex shader
out VS_OUT {
	vec2 TexCoords1;
	vec2 TexCoords2;
	flat int TexUnit1;
	flat int TexUnit2;
	vec4 Tint;
	vec3 ViewPos;
	vec3 Normal;
	vec3 FragPos;
	float Shininess;
} vs_out;

layout(std140) uniform Camera
{
	mat4 u_view;
	mat4 u_projection;
	vec3 u_viewPos;
};

layout(std140) uniform Tessellation
{
	int u_tessellationEquation;
	bool u_generateY;
	int u_octaves;
	float u_scale;
	float u_frequency;
	float u_amplitude;
	float u_amplitudeDivisor;
	float u_frequencyMultiplier;
};

void main()
{
    // Output the texture coordinates
    vs_out.TexCoords1.x = aSubTextureUV.x + ((aSubTextureUV.z - aSubTextureUV.x) * aTexCoords.x);
    vs_out.TexCoords1.y = aSubTextureUV.y + ((aSubTextureUV.w - aSubTextureUV.y) * aTexCoords.y);
	
	vs_out.TexCoords2 = aTexCoords;
	
	// Output the texture unit
	vs_out.TexUnit1 = aTexUnit1;
	vs_out.TexUnit2 = aTexUnit2;
	
	// Output the tint
	vs_out.Tint = aTint;

	// Output View position
	vs_out.ViewPos = u_viewPos;
	
	// Get the model matrix used for the current terrain grid
	mat4 model = aModel;
	vec3 newPos = vec3(model[3][0], 0.0, model[3][2]);
	model[3][1] = noise(newPos, u_octaves);
	newPos = vec3(model * vec4(aPos, 1.0));

	vs_out.FragPos = vec3(aModel * vec4(aPos, 1.0));
	
    vs_out.Normal = aNormal;  
	
	vs_out.Shininess = aShininess;

    gl_Position = u_projection * u_view * aModel * vec4(aPos, 1.0);
}

float hash(float n) {
    return fract(sin(n) * 753.5453123);
}

float snoise(vec3 x)
{
	vec3 p = floor(x);
	vec3 f = fract(x);
	f = f * f * (3.0f - (2.0f * f));

	float n = p.x + p.y * 157.0f + 113.0f * p.z;
	return mix(mix(mix(hash(n + 0.0f), hash(n + 1.0f), f.x),
		mix(hash(n + 157.0f), hash(n + 158.0f), f.x), f.y),
		mix(mix(hash(n + 113.0f), hash(n + 114.0f), f.x),
			mix(hash(n + 270.0f), hash(n + 271.0f), f.x), f.y), f.z);
}

float noise(vec3 position, int octaves)
{
	float total = 0.0;
	float frequency = u_frequency;
	float maxAmplitude = 0.0;
	float amplitude = u_amplitude;
	float scale = u_scale;
	
	for(int i = 0; i < octaves; i++)
	{
		total += snoise(position * frequency) * amplitude;
		frequency *= u_frequencyMultiplier;
		amplitude /= u_amplitudeDivisor;
		maxAmplitude += amplitude;
	}
	return (total / maxAmplitude) * scale;
}