#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 fragPos;
in vec3 fragNormal;

uniform sampler2D ourTexture;
uniform samplerCube envTexture;
uniform vec3 cameraPos;
uniform float timing;
uniform float distortionScale;
uniform float timeFactor;
uniform bool isMelting;

vec4 dayTint = vec4(1.0, 1.0, 1.0, 1.0);  // daylight
vec4 nightTint = vec4(0.1, 0.1, 0.3, 1.0); // night

vec3 wavyDistortion(vec3 normal, float scale) {
    float waveFrequency = 20;  // Higher value for more waves
    float waveAmplitude = 10;   // Higher value for stronger waves
    normal.x += sin(normal.y * waveFrequency + timing) * waveAmplitude * scale;
    normal.z += cos(normal.x * waveFrequency + timing) * waveAmplitude * scale;
    return normalize(normal);
}

void main() {
    vec3 I = normalize(fragPos - cameraPos);
    vec3 N = wavyDistortion(normalize(fragNormal), distortionScale);

    // Fresnel effect
    float fresnel = pow(1.0 - max(dot(I, N), 0.0), 3.0) * 0.7;

    // Compute reflection
    vec3 reflection = reflect(I, N);
    vec4 reflectedColor = texture(envTexture, reflection);

    // Compute refraction
    vec3 refraction = refract(I, N, 1.0 / 1.33); // 1.33 is the refractive index for water
    vec4 refractedColor = texture(envTexture, refraction);
    refractedColor = mix(nightTint * refractedColor, dayTint * refractedColor, timeFactor);

    // 融化模式
    if(isMelting) {
        // 使用反射和折射顏色混合作為 meltedColor
        vec4 meltedColor = mix(refractedColor, reflectedColor, fresnel);

        // 透明度或亮度效果
        float alpha = 0.5 + 0.5 * sin(timing * 2.0); // 波動範圍 [0.0, 1.0]

        // 逐漸變白
        float whiteness = clamp(timing * 0.1, 0.0, 0.8); // 隨時間逐漸增加白色
        vec4 whiteColor = vec4(1.0, 1.0, 1.0, alpha); // 白色同時受 alpha 影響

        // 最終顏色混
        FragColor = mix(meltedColor, whiteColor, whiteness);
    } else {
        // 非融化模式，保持原本的反射與折射混合效果
        FragColor = mix(refractedColor, reflectedColor, fresnel);
    }
}
