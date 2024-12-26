#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;
uniform vec3 lightPos;
uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float gloss;
uniform vec3 cameraPos;
uniform sampler2D ourTexture;

// TODO 2
// Implement Bling-Phong shading
void main()
{
    vec4 color = texture(ourTexture, TexCoord);

    // 光照計算
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = 2.0 * max(dot(normal, lightDir), 0.0) * normal - lightDir;

    //ambient
    vec3 ambient = lightAmbient  * materialAmbient;

    //diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = lightDiffuse * materialDiffuse * diff;

    //spacular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), gloss); //gloss = 10
    vec3 specular = lightSpecular * materialSpecular * spec;

    vec3 result = ambient + diffuse + specular;
    FragColor = clamp(vec4(result, 1.0) * color, 0.0, 1.0);

}