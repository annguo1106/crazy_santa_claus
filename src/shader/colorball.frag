#version 330 core
out vec4 FragColor;

in vec4 Color; 

uniform vec3 rainbowColor;

void main() {
    FragColor = Color;
} 