#version 330 core

out vec4 FragColor; // 輸出像素顏色

uniform vec4 particleColor; // 每個粒子的顏色 (包含透明度)

void main() {
    // 粒子顏色
    FragColor = particleColor;

    // 可選：模擬粒子邊緣的漸變透明效果 (圓形粒子)
    float dist = length(gl_PointCoord - vec2(0.5)); // 計算像素到點中心的距離
    if (dist > 0.5) {
        discard; // 超出半徑的像素丟棄
    }
    FragColor.a *= 1.0 - smoothstep(0.4, 0.5, dist); // 邊緣漸變透明
}

