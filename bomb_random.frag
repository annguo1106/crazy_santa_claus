#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform float timing;
uniform sampler2D ourTexture;

void main() {
    vec4 textureColor = texture(ourTexture, TexCoords);
    FragColor = mix(textureColor, vec4(1.0, 1.0, 1.0, 1.0), timing / 10);
}