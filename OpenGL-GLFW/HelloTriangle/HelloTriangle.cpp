// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include "Shader.h"

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

	// ��Ⱦ׼������--------------------------------------------------------

	// ��ɫ��---------------------------------------------------------------
	Shader ourShader("vertex.vert", "fragment.frag");

	//-----------------------------------------------------------------------------------------
	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,   // ���Ͻ�
		0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};

	GLuint indices[] = { // ��ʼ��0!
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	// ����һ�������������VAO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// 1. ��VAO
	glBindVertexArray(VAO);

	// 2. �����ǵĶ������鸴�Ƶ�һ�����㻺���У��ṩ��OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. �������ǵ��������鵽һ�����������У��ṩ��OpenGLʹ��
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);

	// 3. ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid * )0);
	glEnableVertexAttribArray(0);

	// 4. ���VAO�������EBO����ע����󻺳��൱��û�а󶨻��壬�����ڽ��VAO֮���󻺳壩
	glBindVertexArray(0);

	// �߿�ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// whileѭ��/��Ϸѭ����game loop��---------------------------------
	while(!glfwWindowShouldClose(window))
	{
		// ��鼰�����¼�
		glfwPollEvents();

		// ��������Ⱦ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();
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