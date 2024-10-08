#version 330 core
layout(location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 Color; //Varying
uniform float uTime;
uniform mat4 _Model;

// scale matrix
mat4 scale(float x, float y, float z){
	return mat4(
		x, 0.0, 0.0, 0.0,
		0.0, y, 0.0, 0.0,
		0.0, 0.0, z, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	/*mat3 m;
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z; */
}

// rotation matrix
mat4 rotateZ(float a){
	mat4 m;
	m[0][0] = cos(a);
	m[1][0] = -sin(a);
	m[0][1] = sin(a);
	m[1][1] = cos(a);
	m[2][2] = 1;
	m[3][3] = 1;
	return m;
}

// translation matrix
mat4 translate(float x, float y, float z){
	mat4 m = mat4(1); //IDENTITY matrix
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
	return m;
}


void main()
{
	Color = aColor; //Pass-through - not actually editing the color in this shader, just assigning a value and sending it back
	vec4 pos = vec4(aPos,1.0);
	//pos.y += sin

// traditionally you do scale -> rotate -> translate 	
	//mat4 M = translate(0.3,0.3,0.0) * rotateZ(radians(uTime*90.0)) * scale(2.0, 1.0, 1.0);
	//pos = M * pos;
	//gl_Position = pos;
	gl_Position = _Model * pos;
}