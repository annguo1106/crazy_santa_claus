#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out VS_OUT {
    vec3 Normal;
    vec4 Position;
    vec4 Color;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float rand1;
uniform float rand2;
uniform float rand3;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	// vs_out.TexCoord = aTexCoord;
	vs_out.Position = projection * view * model * vec4(aPos, 1.0);
    vs_out.Normal = normalize(mat3(transpose(inverse(model))) * aNormal);
    vs_out.Color.x = rand1;
    vs_out.Color.y = rand2;
    vs_out.Color.z = rand3;
    vs_out.Color.w = 1.0;
}