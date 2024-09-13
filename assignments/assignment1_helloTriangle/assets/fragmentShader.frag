#version 330 core
out vec4 FragColor;
in vec4 Color;
uniform float uTime;
//uniform vec4 uColor = vec3(1.0);
void main()
{
    //FragColor = Color; //vec4(1.0f, 0.5f, 0.2f, 1.0f); - no longer assigning an abitrary color to the pixels
	FragColor = Color * (cos(uTime) * 0.5 + 0.5);
} 