#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;

void main() {
    float angle = sin(time * 2.0f) * 20.0f; 
    mat4 rotationMatrix = mat4(1.0f);
    vec4 rotationCenter = vec4(20.0f, aPos.y, 140.0f, 1.0f);
    rotationMatrix[0][0] = cos(radians(angle));  // cos(angle)
    rotationMatrix[0][2] = sin(radians(angle));  // sin(angle)
    rotationMatrix[2][0] = -sin(radians(angle)); // -sin(angle)
    rotationMatrix[2][2] = cos(radians(angle));  // cos(angle)

    vec4 rotatedPosition = vec4(aPos, 1.0);
    if (aPos.z > 130.0f && aPos.x > 20.0f) {
        vec4 translatedPosition = rotatedPosition - rotationCenter;
        rotatedPosition = rotationMatrix * translatedPosition;
        // rotatedPosition = rotatedPosition + vec4(rotationCenter, 1.0);
        // rotatedPosition = (rotatedPosition.x, aPos.y, rotatedPosition.z, 1.0) + rotationCenter;
        rotatedPosition = rotatedPosition + rotationCenter;
    }
    // rotatedPosition += vec3(20.0f, aPos.y, 140.0f);
    // rotatedPosition = rotatedPosition + vec4(rotationCenter, 1.0);
    gl_Position = projection * view * model * rotatedPosition;
	TexCoord = aTexCoord;
    // FragPos = model * vec4(staggeredPosition, 1.0);
}