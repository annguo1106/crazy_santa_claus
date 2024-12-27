#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 fragPos;
out vec3 fragNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float timing;
uniform float noiseScale;
uniform float amplitude;

const float waveFrequency = 2.0;
const float waveAmplitude = 20.0;
const float flattenFactor = 1.0;
const float thresholdY = 0.5;

const float maxFlattenFactor = 1.0; 
const float minFlattenFactor = 0.0; 
const float flattenDuration = 7.0; 

float hash(vec3 p) {
    p = fract(p * 0.3183099 + vec3(0.1, 0.2, 0.3));
    p *= 17.0;
    return fract(p.x * p.y * p.z * (p.x + p.y + p.z));
}

void main() {
    vec3 distortedPos = aPos;
    distortedPos.y += sin(aPos.x * noiseScale + timing) * amplitude;
    distortedPos.y += cos(aPos.z * noiseScale + timing) * amplitude * 0.5;

    if(isMelting) {
	    // 增加自然性
		float noise = sin(aPos.z * 10.0 + timing)*6;
		distortedPos.x += noise;

		//波動表面
		distortedPos.y += cos(aPos.z * waveFrequency + timing) * waveAmplitude; // 沿 Z 軸波動

		float collapseSpeed = log(timing + 1.0); // 防止 log(0)
		distortedPos.x += aPos.y * cos(collapseSpeed);

		// 線性插值控制y
		float currentFlattenFactor = mix(maxFlattenFactor, minFlattenFactor, clamp(timing / flattenDuration, 0.0, 1.0));
		distortedPos.z *= currentFlattenFactor;

		float flattenScale = 1.0 + flattenFactor * (1.0 - smoothstep(0.0, 1.0, abs(aPos.z))); // 平滑控制縮放
		distortedPos.x *= flattenScale; // 橫向放大 X
		distortedPos.y *= flattenScale; // 橫向放大 Z

		// 低於一定高度放大
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
