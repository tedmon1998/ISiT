#version 400 core
layout (lines) in;
layout (triangle_strip, max_vertices = 12) out;

in VertexData {
    vec3 color;
} extra_data[];

out vec3 color_f;



void main() {

    //Draw the first triangle
    for(int i = 0; i<gl_in.length();i++)
    {
        color_f =  vec3(1,0,0);
        gl_Position = gl_in[i].gl_Position;
        gl_Position.y-= 0.8;
        gl_Position.x+= 0.0;
        EmitVertex();
    }
    color_f =  vec3(1,0,0);
    gl_Position.x = 0.5f*(gl_in[0].gl_Position.x+gl_in[1].gl_Position.x)+1.5;
    gl_Position.y = sqrt(3)*0.5f*(gl_in[1].gl_Position.x-gl_in[0].gl_Position.x)+gl_in[0].gl_Position.y - 0.6;
    gl_Position.z = 0.0f;
    gl_Position.w = 1.5f;
    EmitVertex();
    gl_Position.y = sqrt(3)*0.5f*(gl_in[1].gl_Position.x-gl_in[0].gl_Position.x)+gl_in[0].gl_Position.y - 2.5;
    EmitVertex();
    EndPrimitive();


    //Draw the second triangle
    for(int i = 0; i<gl_in.length();i++)
    {
        color_f =  vec3(0,1,1);
        gl_Position =gl_in[i].gl_Position;
        gl_Position.y+=sqrt(3)*0.5f*(gl_in[1].gl_Position.x-gl_in[0].gl_Position.x)*2.0f/3.0f;
        gl_Position.z = -0.01f;
        EmitVertex();
    }
    color_f =  vec3(0,1,1);
    gl_Position.x = 0.5f*(gl_in[0].gl_Position.x+gl_in[1].gl_Position.x);
    gl_Position.y = sqrt(3)*0.5f*(gl_in[1].gl_Position.x-gl_in[0].gl_Position.x)/(-3.0f)+gl_in[0].gl_Position.y;
    gl_Position.z = -0.01f;
    gl_Position.w = 1.0f;
    EmitVertex();
    EndPrimitive();


    //Draw the second triangle
    for(int i = 0; i<gl_in.length();i++)
    {
        color_f =  vec3(1,0,0);
        gl_Position =gl_in[i].gl_Position;
        gl_Position.y+=sqrt(3)*0.5f*(gl_in[1].gl_Position.x-gl_in[0].gl_Position.x)*2.0f/3.0f;
        gl_Position.z = -0.01f;
        EmitVertex();
    }
    color_f =  vec3(1,0,0);
    gl_Position.x = 0.5f*(gl_in[0].gl_Position.x+gl_in[1].gl_Position.x);
    gl_Position.y = sqrt(3)*0.5f*(gl_in[1].gl_Position.x-gl_in[0].gl_Position.x)/(-3.0f)+gl_in[0].gl_Position.y + 1.0;
    gl_Position.z = -0.01f;
    gl_Position.w = 1.0f;
    EmitVertex();
    EndPrimitive();

    //Draw the second triangle
    for(int i = 0; i<gl_in.length();i++)
    {
        color_f =  vec3(1,0,1);
        gl_Position =gl_in[i].gl_Position;
        gl_Position.y+=sqrt(3)*0.5f*(gl_in[1].gl_Position.x-gl_in[0].gl_Position.x)*2.0f/3.0f;
        gl_Position.z = -0.01f;
        EmitVertex();
    }
    color_f =  vec3(1,0,1);
    gl_Position.x = 0.5f*(gl_in[0].gl_Position.x+gl_in[1].gl_Position.x);
    gl_Position.y = sqrt(3)*0.5f*(gl_in[1].gl_Position.x-gl_in[0].gl_Position.x)/(-3.0f)+gl_in[0].gl_Position.y + 1.5;
    gl_Position.z = -0.01f;
    gl_Position.w = 1.0f;
    EmitVertex();
    EndPrimitive();



}//