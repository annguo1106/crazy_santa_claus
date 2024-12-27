#version 330 core

// TODO 2
// Implement Bling-Phong shading

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 fragPos;
out vec3 fragNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform float noiseScale;
uniform float amplitude;

// for melting
uniform float timing;
const float waveFrequency=2.0;
const float waveAmplitude=20.0;
const float flattenFactor = 1.0;
const float thresholdY = -1.0;

float hash (vec3 p) {
    p = fract(p * 0.3183099 + vec3(0.1, 0.2, 0.3));
    p *= 17.0;
    return fract(p.x * p.y * p.z * (p.x + p.y + p.z));
}

void main() {
    vec3 distortedPos = aPos;
    distortedPos.y += sin(aPos.x * noiseScale + time) * amplitude;
    distortedPos.y += cos(aPos.z * noiseScale + time) * amplitude * 0.5;

    TexCoord = aTexCoord;
    vec4 worldPos = model * vec4(distortedPos, 1.0);
    fragPos = worldPos.xyz;
    fragNormal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * worldPos;        
}