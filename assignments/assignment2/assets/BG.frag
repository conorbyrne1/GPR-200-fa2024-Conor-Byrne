#version 330 core
out vec4 FragColor;

in vec4 Color;
in vec2 TexCoord;

uniform float uTime;

// uniform sampler2D ourTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
} 