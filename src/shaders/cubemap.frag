#version 330 core
in vec3 TexCoords;

out vec4 FragColor;

uniform samplerCube skybox;
// TODO 4-1
// Implement CubeMap shading

void main()
{
    // 從 cubemap 紋理取樣  
    FragColor = texture(skybox, TexCoords);
}