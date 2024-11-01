#include <stdio.h>
#include <math.h>
#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Conor/shader.h>
#include <ew/external/stb_image.h>
#include <Conor/texture2D.h>
#include <random>
//Include IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow*, double xoffset, double yoffset);

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, 
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, 
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, 
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 
											   
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f, 
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 
											  
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, 
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 
											   
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, 
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 
											   
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, 
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, 
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, 
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, 
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, 
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, 
											   
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, 
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 
};

glm::vec3 cubePositions[3];

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;

bool firstMouse = true;
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
float fov = 60.0f;

glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, 0.0f);
glm::vec3 lightColor = glm::vec3(0.19f, 0.84f, 0.5f);

float ambientK = 0.1f;
float diffuseK = 0.1f;
float specularK = 0.5f;
float shininess = 32.0f;

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Assignment 5", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}
	// AFTER gladLoadGL
	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();


	//sets up the CUBES
	for (int i = 0; i < 3; i++)
	{
		cubePositions[i] = glm::vec3(-2.0 + (i*2.0), 0.0, 0.0);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	// TEXTURE
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader myShader("assets/vertexShader.vert", "assets/fragmentShader.frag");
	Shader lightShader("assets/vertexShader.vert", "assets/lightFragShader.frag");
	glEnable(GL_DEPTH_TEST);
	

	// TEXTURE STUFF
	unsigned int cat;
	glGenTextures(1, &cat);
	glBindTexture(GL_TEXTURE_2D, cat);


	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load and generate the texture
	stbi_set_flip_vertically_on_load(true);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("assets/cat.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		printf("cat loaded\n");
	}
	else
	{
		printf("Failed to load cat!\n");
	}

	stbi_image_free(data);

	/*myShader.use();
	myShader.setInt("myTexture", 2);
	myShader.setVec3("lightPos", lightPos);
	myShader.setVec3("lightColor", lightColor);
	myShader.setVec3("viewPos", cameraPos);*/

	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//INPUT
		processInput(window);
		
		//UPDATE
		float time = (float)glfwGetTime();

		
		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Uniforms
		myShader.use();
		myShader.setFloat("uTime", time);
		myShader.setInt("myTexture", 2);
		myShader.setVec3("lightPos", lightPos);
		myShader.setVec3("lightColor", lightColor);
		myShader.setVec3("viewPos", cameraPos);

		myShader.setFloat("shininess", shininess);
		myShader.setFloat("ambientK", ambientK);
		myShader.setFloat("diffuseK", diffuseK);
		myShader.setFloat("specularK", specularK);

		glActiveTexture(GL_TEXTURE2); // activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, cat);
		
		projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		int projectionLoc = glGetUniformLocation(myShader.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		{
			glm::mat4 ortho = glm::ortho(-(float)SCREEN_WIDTH / 2.0f, (float)SCREEN_WIDTH / 2.0f,
										-(float)SCREEN_HEIGHT / 2.0f, (float)SCREEN_HEIGHT / 2.0f,
										0.1f, 1000.0f);
			projection = ortho;
			projectionLoc = glGetUniformLocation(myShader.ID, "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		}


		//camera setup
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		
		int viewLoc = glGetUniformLocation(myShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glBindVertexArray(VAO);

		for (unsigned int i = 0; i < 3; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			//translates the 3 cubes to position
			model = glm::translate(model, cubePositions[i]);
			//rotates the cubes around their own local origin/center
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			myShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setFloat("uTime", time);
		lightShader.setVec3("lightColor", lightColor);

		viewLoc = glGetUniformLocation(lightShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		lightShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Start Drawing ImGUI
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		// Create a window called Settings
		ImGui::Begin("Settings");
		ImGui::DragFloat3("Light Position", &lightPos.x, 0.1f);
		ImGui::ColorEdit3("Light Color", &lightColor.r);
		ImGui::SliderFloat("Ambient K", &ambientK, 0.0f, 1.0f);
		ImGui::SliderFloat("Diffuse K", &diffuseK, 0.0f, 1.0f);
		ImGui::SliderFloat("Specular K", &specularK, 0.0f, 1.0f);
		ImGui::SliderFloat("Shininess", &shininess, 2.0f, 1024.0f);
		ImGui::Text(":3");

		ImGui::End();

		// Actually render IMGUI elements using OpenGL
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Drawing happens here!
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	printf("Shutting down...");
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	// esc closes the window, taken from the tutorial
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		cameraSpeed *= 5.0f;  
	}
		
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraUp;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		float sens = 0.3f;
		xoffset *= sens;
		yoffset *= sens;

		yaw += xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);
	}
}
void scroll_callback(GLFWwindow*, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 120.0f)
		fov = 120.0f;
}