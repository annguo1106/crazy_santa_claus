#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 FragPos;

uniform sampler2D ourTexture;
uniform float timeFactor;

vec4 dayTint = vec4(1.0, 1.0, 1.0, 1.0);  // daylight
vec4 nightTint = vec4(0.1, 0.1, 0.3, 1.0); // night
// uniform vec3 rainbowColor;

vec3 rainbowColor;
vec4 textureColor;

vec3 rainbow(float value) {
    float bandwidth = 50;
    float r = sin(value / bandwidth * 6.28318 + 0.0); // Red channel
    float g = sin(value / bandwidth * 6.28318 + 2.094); // Green channel
    float b = sin(value / bandwidth * 6.28318 + 4.188); // Blue channel
    return vec3(r, g, b) * 0.5 + 0.5; // Normalize to [0, 1]
}

void main() {
    // float value = (FragPos.y + 1.0) / 2.0;
    float value = FragPos.y;
    rainbowColor = rainbow(value);
    textureColor = texture(ourTexture, TexCoord);
    // FragColor = textureColor * 0.6 + rainbowColor * 0.4;
    vec4 baseColor = vec4(rainbowColor, 1.0) * 0.6 + textureColor * 0.4;
    FragColor =  mix(nightTint * textureColor, dayTint * baseColor, timeFactor);
}