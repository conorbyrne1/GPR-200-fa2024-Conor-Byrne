#define STB_IMAGE_IMPLEMENTATION
#include "../ew/external/stb_image.h"
#include "../ew/external/glad.h"


float vertices[] = {
	//   X     Y     Z			 R     G     B     A        texture coords

		0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,    // top right
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 0.0f,    // bottom right
		-0.5f,  -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 0.0f,    // top left 
		-0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 1.0f     // bottom left

};

unsigned int indices[] = { // note that we start from 0!
	0, 1, 3, // first triangle
	1, 2, 3 // second triangle
};

float BGvertices[] = {
	//   X     Y     Z			 R     G     B     A        texture coords

		2.0f, 2.0f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,		20.0f, 20.0f,    // top right
		2.0f, -2.0f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,		20.0f, 0.0f,    // bottom right
		-2.0f,  -2.0f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 0.0f,    // top left 
		-2.0f, 2.0f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 20.0f     // bottom left

};

void loadTexture2D(const char* filePath, int filterMode, int wrapMode)
{

	//Position XYZ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//COLOR RGBA
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	// TEXTURE
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);
};