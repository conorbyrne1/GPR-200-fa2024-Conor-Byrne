#define STB_IMAGE_IMPLEMENTATION
#include "../ew/external/stb_image.h"
#include "../ew/external/glad.h"

//int width, height, nrChannels;
//unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//
//unsigned int texture;
//glGenTextures(1, &texture);

//filterMode: GL_NEAREST, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, etc
//wrapMode; GL_REPEAT, GL_CLAMP_TO_BORDER, etc
unsigned int loadTexture2D(const char* filePath, int filterMode, int wrapMode);