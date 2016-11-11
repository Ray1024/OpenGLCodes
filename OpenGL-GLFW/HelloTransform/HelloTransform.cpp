// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>

// Shader
#include "Shader.h"

// SOIL
#include "SOIL.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/************************************************************************
 * һЩ��������
 ************************************************************************/
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);


/************************************************************************
 * �������
 ************************************************************************/
int main()
{
	// ��ʼ��GLFW----------------------------------------------------
	glfwInit();
	// ����GLFW----------------------------------------------------
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// ����GLFW����----------------------------------------------------
	GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL",nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// ��ʼ��GLEW-------------------------------------------------------
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// ���ô��ڵĴ�С��λ��----------------------------------------------
	glViewport(0, 0, 800, 600);

	// ע��ص�����-------------------------------------------------------
	glfwSetKeyCallback(window, key_callback);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ��Ⱦ׼������

	// ������----------------------------------------------------------------------------
	//ͼ1
	int width1, height1;
	unsigned char* image1 = SOIL_load_image("../Resource/container.png", &width1, &height1, 0, SOIL_LOAD_RGBA);

	GLuint texture1;
	glGenTextures(1, &texture1);

	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	//ͼ2
	int width2, height2;
	unsigned char* image2 = SOIL_load_image("../Resource/container2.png", &width2, &height2, 0, SOIL_LOAD_RGB);

	GLuint texture2;
	glGenTextures(1, &texture2);

	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);

	// ���㻺�����VBO----------------------------------------------------------------------
	// ��������
	GLfloat vertices[] = {
		// Positions			// Colors				// Texture Coords
		0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Bottom Left
		-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,		0.0f, 1.0f // Top Left
	};

	GLuint indices[] = { // ��ʼ��0!
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	// �����������VAO---------------------------------------------------------------------
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// �ֱ��
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

	// 3. ���ö�������ָ�룺��������+ ��ɫ����+������������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat))); 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 8 * sizeof(GLfloat), (GLvoid * )(6*sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//4. ���VAO
	glBindVertexArray(0);

	// ��ɫ������---------------------------------------------------------------------------
	Shader ourShader("vertex.vert", "fragment.frag");

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// whileѭ��/��Ϸѭ����game loop��---------------------------------
	while(!glfwWindowShouldClose(window))
	{
		// ��鼰�����¼�
		glfwPollEvents();

		// ��������Ⱦ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		// �����任����
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, glm::radians((GLfloat)glfwGetTime()*50.0f), glm::vec3(0.0f, 0.0f, 1.0f));


		// ���任���󴫸�Uniform����
		GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		// ������ͼƬ����Uniform����
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);

		// ����
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// ��������
		glfwSwapBuffers(window);
	}

	// ����/�ͷ���Դ-------------------------------------------------------
	glfwTerminate();
	return 0;
}


/************************************************************************
 * һЩ����ʵ��
 ************************************************************************/
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	// ���û�����ESC, ���ǾͰ�WindowShouldClose����Ϊtrue, �ر�Ӧ��
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}