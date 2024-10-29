#version 330 core
out vec4 FragColor;

in vec4 Color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform float uTime;
uniform sampler2D myTexture;
uniform vec3 lightPos;

void main()
{
	//float ambientStrength = 0.1;
	//vec3 ambient = ambientStrength * lightColor;

	//vec3 result = ambient * objectColor;
	//FragColor = vec4(result, 1.0);
    FragColor = texture(myTexture, TexCoord);
} 