 #version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 12) out;

in VS_OUT {
    vec2 TexCoord;
    vec3 Normal;
    vec4 Position;
} gs_in[];

out vec2 TexCoords;

uniform float timing;

float rand(vec3 seed) {
    return fract(sin(dot(seed, vec3(12.9898, 78.233, 45.164))) * 43758.5453123);
}

vec4 explode(vec4 position, vec3 normal, vec3 randomOffset) {
    float magnitude = 20;
    vec3 direction = (normal + randomOffset) * timing * timing / 0.8 * magnitude;
    return position + vec4(direction, 0);
}

vec3 getNormal() {
    vec3 a = vec3(gs_in[0].Position) - vec3(gs_in[1].Position);
    vec3 b = vec3(gs_in[2].Position) - vec3(gs_in[1].Position);
    return normalize(cross(b, a));
}

void emitTriangle(vec4 p0, vec4 p1, vec4 p2, vec2 t0, vec2 t1, vec2 t2) {
    gl_Position = p0;
    TexCoords = t0;
    EmitVertex();

    gl_Position = p1;
    TexCoords = t1;
    EmitVertex();

    gl_Position = p2;
    TexCoords = t2;
    EmitVertex();
    EndPrimitive();
}

void main() {
    vec3 Normal = -getNormal();

    vec3 randomOffset0 = vec3(rand(gs_in[0].Position.xyz), rand(gs_in[1].Position.xyz), rand(gs_in[2].Position.xyz)) * 0.5 - 0.25;
    vec3 randomOffset1 = vec3(rand(gs_in[1].Position.xyz), rand(gs_in[2].Position.xyz), rand(gs_in[0].Position.xyz)) * 0.5 - 0.25;
    vec3 randomOffset2 = vec3(rand(gs_in[2].Position.xyz), rand(gs_in[0].Position.xyz), rand(gs_in[1].Position.xyz)) * 0.5 - 0.25;
    
    vec4 p0 = gs_in[0].Position;
    vec4 p1 = gs_in[1].Position;
    vec4 p2 = gs_in[2].Position;
    vec4 mid01 = (p0 + p1) / 2;
    vec4 mid02 = (p0 + p2) / 2;
    vec4 mid12 = (p1 + p2) / 2;

    p0 = explode(p0, Normal, randomOffset0);
    p1 = explode(p1, Normal, randomOffset1);
    p2 = explode(p2, Normal, randomOffset2);
    mid01 = explode(mid01, Normal, randomOffset0 + randomOffset1);
    mid02 = explode(mid02, Normal, randomOffset0 + randomOffset2);
    mid12 = explode(mid12, Normal, randomOffset1 + randomOffset2);

    vec2 t0 = gs_in[0].TexCoord;
    vec2 t1 = gs_in[1].TexCoord;
    vec2 t2 = gs_in[2].TexCoord;
    vec2 midt01 = (gs_in[0].TexCoord + gs_in[1].TexCoord) / 2;
    vec2 midt02 = (gs_in[0].TexCoord + gs_in[2].TexCoord) / 2;
    vec2 midt12 = (gs_in[1].TexCoord + gs_in[2].TexCoord) / 2;

    emitTriangle(p0, mid01, mid02, t0, midt01, midt02);
    emitTriangle(mid01, p1, mid12, midt01, t1, midt12);
    emitTriangle(mid12, p2, mid02, midt12, t2, midt02);
    emitTriangle(mid01, mid12, mid02, midt01, midt12, midt02);
}