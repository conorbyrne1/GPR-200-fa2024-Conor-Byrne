#version 330 core
layout(location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform float uTime;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	; gl_Position = transform * vec4(aPos, 1.0f);
	; TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	// note that we read the muliplication from right to left
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}