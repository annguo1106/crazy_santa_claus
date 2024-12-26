#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform vec3 particlePosition; // 每個粒子的世界空間位置
uniform mat4 projection;       // 投影矩陣
uniform mat4 view;             // 視圖矩陣
uniform mat4 model;

void main() {
    // 將粒子的世界空間位置轉換為裁剪空間
    gl_Position = projection * view * vec4(particlePosition, 1.0);

    gl_PointSize = 5.0; // 點大小可以根據需求修改
}
