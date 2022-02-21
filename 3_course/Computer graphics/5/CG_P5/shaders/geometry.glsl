#version 400 core
layout (lines) in;
layout (triangle_strip, max_vertices = 39) out;
in VertexData {
    vec3 color;
} extra_data[];

out vec3 color_f;


void DrowSquare(vec4 position, vec3 rgb)
{
    color_f = rgb;
    gl_Position = position + vec4(-0.2, -0.4, 0.0, 0.0);   // 1:нижняя-левая
    EmitVertex();
    gl_Position = position + vec4(0.62, -0.32, 0.0, 0.0);    // 2:нижняя-правая
    EmitVertex();
    gl_Position = position + vec4(-0.29, 0.5, 0.0, 0.0);     // 3:верхняя-левая
    EmitVertex();
    gl_Position = position + vec4(0.54, 0.58, 0.0, 0.0);    // 4:верхняя-правая
    EmitVertex();
    EndPrimitive();
}
void DrowTriangle1(vec4 position, vec3 rgb)
{
    color_f = rgb;
    gl_Position = position + vec4(-0.19, -0.39, 0.0, 0.0);   // 1:нижняя-левая
    EmitVertex();
    gl_Position = position + vec4(0.10, -0.18, 0.0, 0.0);    // 2:нижняя-правая
    EmitVertex();
    gl_Position = position + vec4(-0.28, 0.48, 0.0, 0.0);     // 3:верхняя-левая
    EmitVertex();
    EndPrimitive();
}
void DrowTriangle2(vec4 position, vec3 rgb)
{
    color_f = rgb;
    gl_Position = position + vec4(-0.27, 0.49, 0.0, 0.0);   // 1:нижняя-левая
    EmitVertex();
    gl_Position = position + vec4(-0.08, 0.17, 0.0, 0.0);    // 2:нижняя-правая
    EmitVertex();
    gl_Position = position + vec4(0.52, 0.565, 0.0, 0.0);     // 3:верхняя-левая
    EmitVertex();
    EndPrimitive();
}
void DrowTriangle3(vec4 position, vec3 rgb)
{
    color_f = rgb;
    gl_Position = position + vec4(0.25, 0.365, 0.0, 0.0);   // 1:нижняя-левая
    EmitVertex();
    gl_Position = position + vec4(0.53, 0.555, 0.0, 0.0);    // 2:нижняя-правая
    EmitVertex();
    gl_Position = position + vec4(0.605, -0.30, 0.0, 0.0);     // 3:верхняя-левая
    EmitVertex();
    EndPrimitive();
}

void DrowTriangle4(vec4 position, vec3 rgb)
{
    color_f = rgb;
    gl_Position = position + vec4(0.413, 0.03, 0.0, 0.0);   // 1:нижняя-левая
    EmitVertex();
    gl_Position = position + vec4(0.598, -0.31, 0.0, 0.0);    // 2:нижняя-правая
    EmitVertex();
    gl_Position = position + vec4(-0.16, -0.385, 0.0, 0.0);     // 3:верхняя-левая
    EmitVertex();
    EndPrimitive();
}

void DrowSquareMin(vec4 position, vec3 rgb)
{
    color_f = rgb;
    gl_Position = position + vec4(0.115, -0.17, 0.0, 0.0);   // 1:нижняя-левая
    EmitVertex();
    gl_Position = position + vec4(0.405, 0.04, 0.0, 0.0);    // 2:нижняя-правая
    EmitVertex();
    gl_Position = position + vec4(-0.07, 0.16, 0.0, 0.0);     // 3:верхняя-левая
    EmitVertex();
    gl_Position = position + vec4(0.235, 0.36, 0.0, 0.0);    // 4:верхняя-правая
    EmitVertex();
    EndPrimitive();
}

void DrowTriangle5(vec4 position, vec3 rgb)
{
    color_f = rgb;
    gl_Position = position + vec4(0.03, 0.03, 0.0, 0.0);   // 1:нижняя-левая
    EmitVertex();
    gl_Position = position + vec4(0.405, 0.04, 0.0, 0.0);    // 2:нижняя-правая
    EmitVertex();
    gl_Position = position + vec4(0.235, 0.37, 0.0, 0.0);    // 4:верхняя-правая
    EmitVertex();
    EndPrimitive();
}
void DrowTriangle6(vec4 position, vec3 rgb)
{
    color_f = rgb;
    gl_Position = position + vec4(0.045, 0.03, 0.0, 0.0);   // 1:нижняя-левая
    EmitVertex();
    gl_Position = position + vec4(0.405, 0.04, 0.0, 0.0);    // 2:нижняя-правая
    EmitVertex();
    gl_Position = position + vec4(0.245, 0.311, 0.0, 0.0);    // 4:верхняя-правая
    EmitVertex();
    EndPrimitive();
}
void DrowTriangle7(vec4 position, vec3 rgb)
{
    color_f = rgb;
    gl_Position = position + vec4(0.055, 0.045, 0.0, 0.0);   // 1:нижняя-левая
    EmitVertex();
    gl_Position = position + vec4(0.3955, 0.054, 0.0, 0.0);    // 2:нижняя-правая
    EmitVertex();
    gl_Position = position + vec4(0.24, 0.35, 0.0, 0.0);    // 4:верхняя-правая
    EmitVertex();
    EndPrimitive();
}

void main() {

    //Draw the first triangle
    //------------------------------RED---------------------------------------------
    DrowTriangle7(gl_in[0].gl_Position, vec3(1.0, 1.0, 1.0));
    DrowTriangle6(gl_in[0].gl_Position, vec3(1.0, 0.0, 0.0));
    DrowTriangle5(gl_in[0].gl_Position, vec3(0.0, 0.0, 0.0));
    DrowSquareMin(gl_in[0].gl_Position, vec3(1.0, 1.0, 1.0));
    DrowTriangle4(gl_in[0].gl_Position, vec3(0.0, 1.0, 0.0));
    DrowTriangle3(gl_in[0].gl_Position, vec3(0.0, 0.0, 1.0));
    DrowTriangle2(gl_in[0].gl_Position, vec3(1.0, 0.0, 0.0));
    DrowTriangle1(gl_in[0].gl_Position, vec3(1.0, 1.0, 0.0));
    DrowSquare(gl_in[0].gl_Position, vec3(0.0, 0.0, 0.0));

//    DrowSquare(gl_in[0].gl_P);
}//