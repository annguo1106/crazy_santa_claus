 #version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 Normal;
    vec4 Position;
    vec4 Color;
} gs_in[];

out vec4 Color;
uniform float timing;

void emitTriangle(vec4 p0, vec4 p1, vec4 p2, vec4 c0, vec4 c1, vec4 c2) {
    gl_Position = p0;
    Color = c0;
    EmitVertex();

    gl_Position = p1;
    Color = c1;
    EmitVertex();

    gl_Position = p2;
    Color = c2;
    EmitVertex();
    EndPrimitive();
}

void main() {
    vec4 p0 = gs_in[0].Position;
    vec4 p1 = gs_in[1].Position;
    vec4 p2 = gs_in[2].Position;

    vec4 c0 = gs_in[0].Color;
    vec4 c1 = gs_in[1].Color;
    vec4 c2 = gs_in[2].Color;

    emitTriangle(p0, p1, p2, c0, c1, c2);
}