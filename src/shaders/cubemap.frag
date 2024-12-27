#version 330 core

// TODO 4-1
// Implement CubeMap shading
out vec4 FragColor;

in vec3 TexCoord; 

uniform samplerCube ourTexture;
uniform float timeFactor;
// uniform float time;

vec4 dayTint = vec4(1.0, 1.0, 1.0, 1.0);  // daylight
vec4 nightTint = vec4(0.1, 0.1, 0.3, 1.0); // night
float starBrightness = 0.3;

float hash (vec3 p) {
    p = fract(p * 0.3183099 + vec3(0.1, 0.2, 0.3));
    p *= 17.0;
    return fract(p.x * p.y * p.z * (p.x + p.y + p.z));
}

void main() {
    vec4 skyColor = texture(ourTexture, TexCoord);
    // vec4 baseColor = mix(nightTint * skyColor, dayTint * skyColor, timeFactor);
    // if (timeFactor < 0.3) {
    //     float starIntensity = (1.0 - timeFactor / 0.3) * starBrightness;
    //     float star = random(floor(TexCoord * 100.0));
    //     if (star > 0.99 && TexCoord.y > 0.0) {
    //         baseColor += vec4(starIntensity);
    //     }
    // }
    // float brightness = mix(0.3, 1.0, timeFactor);
    // baseColor *= brightness;
    // FragColor = vec4(baseColor, 1.0);
    float brightness = 0.0;
    // if (TexCoord.y > 0.25) {
    float topFactor = smoothstep(-0.5, 1.0, TexCoord.y);
    float noise = hash(TexCoord * 50.0);
    brightness = pow(noise, 12.0);
    brightness = brightness > 0.5? brightness: 0.0;
    brightness *= topFactor;
    // }
    
    // float twinkle = sin(timeFactor + hash(TexCoord * 50.0) * 6.28) * 0.5 + 0.5;
    // brightness *= twinkle;
    vec4 starColor = vec4(brightness, brightness, brightness, 1.0);
    // float starVisible = smoothstep(0.0, 0.3, 1.0 - timeFactor);
    // FragColor = mix(nightTint * skyColor, dayTint * skyColor, timeFactor)
    // FragColor = baseColor + starColor * starVisible;
    // vec4 stars = texture(starTexture, TexCoords);
    FragColor = mix(nightTint * skyColor + starColor, dayTint * skyColor, timeFactor);
}