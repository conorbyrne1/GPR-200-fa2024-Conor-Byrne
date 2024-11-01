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
uniform vec3 viewPos;
uniform float shininess;
uniform float ambientK;
uniform float diffuseK;
uniform float specularK;

void main()
{

	vec4 texSample = texture(myTexture, TexCoord);

	float ambientStrength = ambientK;
	vec3 ambient = ambientStrength * lightColor;
    
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	//float diff = diffuseK;
	vec3 diffuse = diffuseK * diff * lightColor;

	float specularStrength = specularK;
	
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	vec3 reflectDir = reflect(-lightDir, norm);
	
	float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
	vec3 specular = lightColor * spec;

	vec3 result = (ambient + diffuse + specular) * vec3(texSample);

	//FragColor = texture(myTexture, TexCoord);
	FragColor = vec4(result, 1.0);
} 