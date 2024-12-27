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
uniform bool isMelting;

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

    // Compute reflection
    vec3 reflection = reflect(I, N);
    vec4 reflectedColor = texture(envTexture, reflection);

    // copmute refraction
    vec3 refraction = refract(I, N, 1.0 / 1.33); // 1.33 is the refractive index for water
    vec4 refractedColor = texture(envTexture, refraction);
    refractedColor = mix(nightTint * refractedColor, dayTint * refractedColor, timeFactor);
    FragColor = mix(refractedColor, reflectedColor, fresnel);

    // if (isMelting) {
    //     // 原始紋理顏色
    //     vec4 baseColor = texture(ourTexture, TexCoord);

    //     // 添加流動效果
    //     float flow = sin(TexCoord.y * 10.0 + time * 2.0) * 0.1; // 水平波動流動
    //     vec2 meltTexCoords = vec2(TexCoord.x + flow, TexCoord.y - time * 0.1); // 模擬融化紋理坐標
    //     vec4 meltedColor = texture(ourTexture, meltTexCoords);

    //     // 混合反射、折射與融化效果
    //     vec4 combinedColor = mix(refractedColor, reflectedColor, fresnel); // 原本效果
    //     FragColor = mix(combinedColor, meltedColor, 0.999); // 與融化效果混合

    //     // 增加透明度處理
    //     float alpha = clamp(1.0 - time * 0.2, 0.3, 1.0); // 隨時間逐漸透明
    //     FragColor.a *= alpha;
    // } else {
    //     // 非融化模式，保持原本的反射與折射混合效果
    //     FragColor = mix(refractedColor, reflectedColor, fresnel);
    // }
}