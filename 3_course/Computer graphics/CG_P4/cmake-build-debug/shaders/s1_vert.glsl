#version 330 core

in vec3 vertexPosition;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;


void main()
{
//  gl_Position = matProjection * matView * matModel * vec4(vertexPosition, 1);
  gl_Position = matProjection *matView * matModel * vec4(vertexPosition, 1);
}
