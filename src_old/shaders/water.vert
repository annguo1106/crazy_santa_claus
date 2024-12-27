#version 330 core

// TODO 2
// Implement Bling-Phong shading

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 fragPos;
out vec3 fragNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform float noiseScale;
uniform float amplitude;
uniform float timing;
uniform bool isMelting;

const float waveFrequency=2.0;
const float waveAmplitude=20.0;
const float flattenFactor = 1.0;
const float thresholdY = -1.0;


float hash (vec3 p) {
    p = fract(p * 0.3183099 + vec3(0.1, 0.2, 0.3));
    p *= 17.0;
    return fract(p.x * p.y * p.z * (p.x + p.y + p.z));
}

void main() {
     vec3 distortedPos = aPos;
    // distortedPos.y += sin(aPos.x * noiseScale + timing) * amplitude;
    // distortedPos.y += cos(aPos.z * noiseScale + timing) * amplitude * 0.5;

    if(isMelting){
        // 噪聲效果，增加自然性
	    float noise = sin(aPos.y * 10.0 + timing)*6;
	    distortedPos.x += noise;

	    //波動表面
	    distortedPos.z += cos(aPos.y * waveFrequency + timing) * waveAmplitude; // 沿 Z 軸波動

	    float collapseSpeed = log(timing + 1.0); // 防止 log(0)
	    distortedPos.x += aPos.y * cos(collapseSpeed);
	    distortedPos.z += aPos.z * cos(collapseSpeed);

	    // 計算高度對縮放的影響
	    float flattenScale = 1.0 + flattenFactor * (1.0 - smoothstep(0.0, 1.0, abs(aPos.y))); // 平滑控制縮放
	    //distortedPos.x *= flattenScale; // 橫向放大 X
	    //distortedPos.z *= flattenScale; // 橫向放大 Z

	    // 判定是否需要縮放
	    if (distortedPos.z < thresholdY) {
	        distortedPos *= flattenFactor; // 整體放大
	    }
    }

    TexCoord = aTexCoord;
    vec4 worldPos = model * vec4(distortedPos, 1.0);
    fragPos = worldPos.xyz;
    fragNormal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * worldPos;        
}