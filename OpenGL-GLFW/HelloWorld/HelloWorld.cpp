// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>

/************************************************************************
 * 一些函数声明
 ************************************************************************/
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);


/************************************************************************
 * 程序入口
 ************************************************************************/
int main()
{
	// 初始化GLFW----------------------------------------------------
	glfwInit();
	// 配置GLFW----------------------------------------------------
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// 创建GLFW窗口----------------------------------------------------
	GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL",nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// 初始化GLEW-------------------------------------------------------
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// 设置窗口的大小和位置----------------------------------------------
	glViewport(0, 0, 800, 600);

	// 注册回调函数-------------------------------------------------------
	glfwSetKeyCallback(window, key_callback);

	// while循环/游戏循环（game loop）---------------------------------
	while(!glfwWindowShouldClose(window))
	{
		// 检查及调用事件
		glfwPollEvents();

		// 这里是渲染命令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 交换缓冲
		glfwSwapBuffers(window);
	}

	// 清理/释放资源-------------------------------------------------------
	glfwTerminate();
	return 0;
}


/************************************************************************
 * 一些函数实现
 ************************************************************************/
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	// 当用户按下ESC, 我们就把WindowShouldClose设置为true, 关闭应用
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}