#version 330 core
layout(location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 Color; //Varying
uniform float uTime;
void main()
{
	Color = aColor; //Pass-through - not actually editing the color in this shader, just assigning a value and sending it back
	vec3 pos = aPos;
	pos.y += (cos(uTime + 6.0 - pos.x)/3);
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}