#version 330 core

in vec2 TexCoord; // 從 Vertex Shader 傳遞來的紋理座標
out vec4 FragColor;

uniform sampler2D ourTexture; // 目標貼圖
uniform float time; // 時間參數，用於控制融化

void main() {
    // 基本紋理顯示
    vec4 baseColor = texture(ourTexture, TexCoord);

    // 添加融化效果：模擬流動
    float flow = sin(TexCoord.y * 10.0 + time * 2.0) * 0.1;
    vec2 meltTexCoords = vec2(TexCoord.x + flow, TexCoord.y - time * 0.1);

    // 測試範圍，避免超出邊界
    //meltTexCoords = clamp(meltTexCoords, 0.0, 1.0);

    // 取樣紋理，混合效果
    vec4 meltedColor = texture(ourTexture, meltTexCoords);

    // 透明度或亮度效果
    float alpha = clamp(1.0 - time * 0.2, 0.3, 1.0); // 隨時間逐漸減弱
    FragColor = mix(baseColor, meltedColor, 0.5) * vec4(1.0, 1.0, 1.0, alpha);
}
