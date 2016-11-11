// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>

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

	// whileѭ��/��Ϸѭ����game loop��---------------------------------
	while(!glfwWindowShouldClose(window))
	{
		// ��鼰�����¼�
		glfwPollEvents();

		// ��������Ⱦ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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