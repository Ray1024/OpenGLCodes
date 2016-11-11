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
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f, 0.0f, 0.0f),
		glm::vec3( 2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f, 2.0f, -2.5f),
		glm::vec3( 1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	// �����������VAO---------------------------------------------------------------------
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ���Ӷ�������
	// �������� 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0); 
	//  ������������
	glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 5 * sizeof(GLfloat), (GLvoid * )(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// ���VAO
	glBindVertexArray(0);

	// ��ɫ������---------------------------------------------------------------------------
	Shader ourShader("vertex.vert", "fragment.frag");

	// �����任����-------------------------------------------------------------------------

	glm::mat4 model;
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(45.0f, 800.f / 600.f, 0.1f, 100.0f);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// whileѭ��/��Ϸѭ����game loop��---------------------------------
	while(!glfwWindowShouldClose(window))
	{
		// ��鼰�����¼�
		glfwPollEvents();

		// ���������� depth buffer
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ���Ʊ���
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		// ���任���󴫸�Uniform����
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLint projectionLoc = glGetUniformLocation(ourShader.Program, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// ������ͼƬ����Uniform����
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);

		// ����
		glBindVertexArray(VAO);

		for(GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			if (i==1 || i== 3 || i==6 || i==9)
			{
				model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime()*50.f), glm::vec3(1.0f, 0.3f, 0.5f));
			}else
			{
				GLfloat angle = 20.0f * i;
				model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			}
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

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