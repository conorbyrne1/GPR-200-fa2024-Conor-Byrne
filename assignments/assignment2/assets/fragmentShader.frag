#version 330 core
out vec4 FragColor;

in vec4 Color;
in vec2 TexCoord;

uniform float uTime;

uniform sampler2D texture3;

void main()
{
   FragColor = texture(texture3, TexCoord);
} 