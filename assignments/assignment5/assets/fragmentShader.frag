#version 330 core
out vec4 FragColor;

in vec4 Color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform float uTime;
uniform sampler2D myTexture;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{

	vec4 texSample = texture(myTexture, TexCoord);

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	//vec3 result = ambient * texSample;
	
    
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * vec3(texSample);

	//FragColor = texture(myTexture, TexCoord);
	FragColor = vec4(result, 1.0);
} 