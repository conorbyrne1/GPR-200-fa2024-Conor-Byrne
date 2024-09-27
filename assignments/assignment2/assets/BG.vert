#version 330 core
layout(location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 Color; //Varying
out vec2 TexCoord;

uniform float uTime;
void main()
{
	Color = aColor; //Pass-through - not actually editing the color in this shader, just assigning a value and sending it back
	TexCoord = aTexCoord * 5.0;

	vec3 pos = aPos * 4.0;

	pos.x += mod(uTime*0.2, 1.0);
	
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);

}