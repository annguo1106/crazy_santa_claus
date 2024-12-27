#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 TexCoord;
    vec3 Normal;
    vec4 Position;
} gs_in[];

out vec2 TexCoords;

uniform float timing;

vec4 explode(vec4 position, vec3 normal) {
    float magnitude = 20;
    vec3 direction = normal * timing * magnitude;
    return position + vec4(direction, 0);
}

vec3 getNormal() {
    vec3 a = vec3(gs_in[0].Position) - vec3(gs_in[1].Position);
    vec3 b = vec3(gs_in[2].Position) - vec3(gs_in[1].Position);
    return normalize(cross(b, a));
}

void main() {
    vec3 Normal = -getNormal();
    
    gl_Position = explode(gs_in[0].Position, Normal);
    TexCoords = gs_in[0].TexCoord;
    EmitVertex();

    gl_Position = explode(gs_in[1].Position, Normal);
    TexCoords = gs_in[1].TexCoord;
    EmitVertex();

    gl_Position = explode(gs_in[2].Position, Normal);
    TexCoords = gs_in[2].TexCoord;
    EmitVertex();
    EndPrimitive();
}