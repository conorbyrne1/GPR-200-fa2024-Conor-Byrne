#include <stdio.h>
#include <math.h>
#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Conor/shader.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
	//X      Y      Z     R     G     B     A
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
};

glm::mat4 scale(float x, float y, float z) {
	return glm::mat4(
		x, 0.0, 0.0, 0.0,
		0.0, y, 0.0, 0.0,
		0.0, 0.0, z, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
}

glm::mat4 rotateZ(float a) {
	glm::mat4 m;
	m[0][0] = cos(a);
	m[1][0] = -sin(a);
	m[0][1] = sin(a);
	m[1][1] = cos(a);
	m[2][2] = 1;
	m[3][3] = 1;
	return m;
}

glm::mat4 translate(float x, float y, float z) {
	glm::mat4 m = glm::mat4(1); //IDENTITY matrix
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
	return m;
}


int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}
	//Initialization goes here!
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	//Vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//Position XYZ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//COLOR RGBA
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	Shader myShader("assets/vertexShader.vert", "assets/fragmentShader.frag");

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		//INPUT
		//UPDATE
		float time = (float)glfwGetTime();


		//DRAW
		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//render the triangle
		myShader.use();
		myShader.setFloat("uTime", time); //shoutout james for helping me with this line

		for (int i = 0; i < 20; i++)
		{
			glm::mat4 model = glm::mat4(1);
			//model = scale(2.0f, 1.0f, 1.0f) * model;
			//model = rotateZ(time + i) * model;
			model = translate(cosf(time + i), sinf(time + i), 0.0f) * model;
			myShader.setMat4("_Model", model);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		


		glBindVertexArray(VAO); //this happens 2x for clarity's sake
		
		//DRAW CALL
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Drawing happens here!
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}
