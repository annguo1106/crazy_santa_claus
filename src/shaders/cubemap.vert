#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 view;
uniform mat4 projection;

// TODO 4-1
// Implement CubeMap shading
void main()
{
    TexCoords = aPos;

    // 去掉 view 矩陣的平移，保持 cubemap 靜止
    mat4 viewNoTranslation = mat4(mat3(view));

    vec4 pos = projection * viewNoTranslation * vec4(aPos, 1.0);
    //頂點位置設置為屏幕的最大深度
    gl_Position = pos.xyww;
}