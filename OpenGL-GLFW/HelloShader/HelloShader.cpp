// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>

#include "Shader.h"

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

	// 渲染准备工作--------------------------------------------------------
	// 创建顶点缓冲对象VBO
	GLfloat vertices[] = {
		// 位置						// 颜色
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// 右下
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// 左下
		0.0f, 0.5f, 0.0f,			0.0f, 0.0f, 1.0f	// 上
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 链接顶点属性
	// 顶点属性 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0); 
	// 颜色属性 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat))); 
	glEnableVertexAttribArray(1);

	// 生成一个顶点数组对象VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// 1. 绑定VAO
	glBindVertexArray(VAO);

	// 2. 把顶点数组复制到缓冲中提供给OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. 设置顶点属性指针
	// 顶点属性 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0); 
	// 颜色属性 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat))); 
	glEnableVertexAttribArray(1);

	//4. 解绑VAO
	glBindVertexArray(0);

	// 着色器处理
	Shader ourShader("vertex.vert", "fragment.frag");

	// while循环/游戏循环（game loop）---------------------------------
	while(!glfwWindowShouldClose(window))
	{
		// 检查及调用事件
		glfwPollEvents();

		// 这里是渲染命令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

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