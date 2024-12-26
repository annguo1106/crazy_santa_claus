#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time; // 時間參數，用於控制融化

out vec2 TexCoord; // 傳遞給 Fragment Shader

const float waveFrequency=2.0;
const float waveAmplitude=20.0;
const float flattenFactor = 1.0;
const float thresholdY = -1.0;

void main() {
    vec3 modifiedPos = aPos;

    // 噪聲效果，增加自然性
    float noise = sin(aPos.y * 10.0 + time)*6;
    modifiedPos.x += noise;

    //波動表面
    modifiedPos.z += cos(aPos.y * waveFrequency + time) * waveAmplitude; // 沿 Z 軸波動

    //隨時間collapse
    modifiedPos.x += aPos.z* sin(time);
    modifiedPos.y += aPos.y* sin(time);

    // 計算高度對縮放的影響
    //float flattenScale = 1.0 + flattenFactor * (1.0 - smoothstep(0.0, 1.0, abs(aPos.y))); // 平滑控制縮放
    //modifiedPos.x *= flattenScale; // 橫向放大 X
    //modifiedPos.z *= flattenScale; // 橫向放大 Z

    // 計算模型的中心 Y 值
    float modelCenterY = model[3][1]; // 模型矩陣的位移分量代表中心 Y

    // 判定是否需要縮放
    if (modelCenterY < thresholdY) {
        modifiedPos *= flattenFactor; // 整體放大
    }


    // 最終頂點位置
    gl_Position = projection * view * model * vec4(modifiedPos, 1.0);
    TexCoord = aTexCoord; // 傳遞紋理座標
}
