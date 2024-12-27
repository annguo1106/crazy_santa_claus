#version 330 core

// TODO 2
// Implement Bling-Phong shading

out vec4 FragColor;

in vec2 TexCoord;
in vec3 fragPos;
in vec3 fragNormal;

uniform sampler2D ourTexture;
uniform samplerCube envTexture;
uniform vec3 cameraPos;
uniform float time;
uniform float distortionScale;

vec4 dayTint = vec4(1.0, 1.0, 1.0, 1.0);  // daylight

vec3 wavyDistortion(vec3 normal, float scale) {
    float waveFrequency = 20;  // Higher value for more waves
    float waveAmplitude = 10;   // Higher value for stronger waves
    normal.x += sin(normal.y * waveFrequency + time) * waveAmplitude * scale;
    normal.z += cos(normal.x * waveFrequency + time) * waveAmplitude * scale;
    return normalize(normal);
}

void main() {
    vec3 I = normalize(fragPos - cameraPos);
    // vec3 N = normalize(fragNormal);
    vec3 N = wavyDistortion(normalize(fragNormal), distortionScale);
    float fresnel = pow(1.0 - max(dot(I, N), 0.0), 3.0) * 0.7;

    // Compute reflection
    vec3 reflection = reflect(I, N);
    vec4 reflectedColor = texture(envTexture, reflection);

    // copmute refraction
    vec3 refraction = refract(I, N, 1.0 / 1.33); // 1.33 is the refractive index for water
    vec4 refractedColor = texture(envTexture, refraction);
    refractedColor = dayTint * refractedColor;
    FragColor = mix(refractedColor, reflectedColor, fresnel);
}