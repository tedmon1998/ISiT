#version 330 core

in vec2 vertexPosition;
in vec2 vertexTextureCoords;
out vec2 textureCoords;

uniform vec2 textureScale;

void main()
{
  gl_Position = vec4(vertexPosition, 0, 1);
  textureCoords = textureScale * vertexTextureCoords;
}
