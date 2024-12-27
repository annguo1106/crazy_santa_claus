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
uniform float timeFactor;
uniform float transFactor;

vec4 dayTint = vec4(1.0, 1.0, 1.0, 1.0);  // daylight
vec4 nightTint = vec4(0.1, 0.1, 0.3, 1.0); // night

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

    // Apply wavy distortion to normals for a water effect
    // vec3 distortedNormal = wavyDistortion(N, distortionScale);

    // Compute reflection
    vec3 reflection = reflect(I, N);
    vec4 reflectedColor = texture(envTexture, reflection);

    // handle sky color

    // copmute refraction
    vec3 refraction = refract(I, N, 1.0 / 1.33); // 1.33 is the refractive index for water
    vec4 refractedColor = texture(envTexture, refraction);
    refractedColor = mix(nightTint * refractedColor, dayTint * refractedColor, timeFactor);
    vec4 waterColor = mix(refractedColor, reflectedColor, fresnel);
    
    vec4 textureColor = texture(ourTexture, TexCoord);
    textureColor = mix(nightTint * textureColor, dayTint * textureColor, timeFactor);
    // Simulate water transparency and color
    // vec4 baseColor = vec4(0.0, 0.3, 0.5, 0.5); // Light blue for water

    // Blend reflection with base color
    // FragColor = mix(refractedColor, reflectedColor, fresnel);
    FragColor = mix(textureColor, waterColor, transFactor);
}