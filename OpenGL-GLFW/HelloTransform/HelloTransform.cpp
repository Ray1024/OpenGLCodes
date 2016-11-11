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

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 渲染准备工作

	// 纹理处理----------------------------------------------------------------------------
	//图1
	int width1, height1;
	unsigned char* image1 = SOIL_load_image("../Resource/container.png", &width1, &height1, 0, SOIL_LOAD_RGBA);

	GLuint texture1;
	glGenTextures(1, &texture1);

	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	//图2
	int width2, height2;
	unsigned char* image2 = SOIL_load_image("../Resource/container2.png", &width2, &height2, 0, SOIL_LOAD_RGB);

	GLuint texture2;
	glGenTextures(1, &texture2);

	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);

	// 顶点缓冲对象VBO----------------------------------------------------------------------
	// 顶点数据
	GLfloat vertices[] = {
		// Positions			// Colors				// Texture Coords
		0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Bottom Left
		-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,		0.0f, 1.0f // Top Left
	};

	GLuint indices[] = { // 起始于0!
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	// 顶点数组对象VAO---------------------------------------------------------------------
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 分别绑定
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

	// 3. 设置顶点属性指针：顶点属性+ 颜色属性+纹理坐标属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat))); 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 8 * sizeof(GLfloat), (GLvoid * )(6*sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//4. 解绑VAO
	glBindVertexArray(0);

	// 着色器处理---------------------------------------------------------------------------
	Shader ourShader("vertex.vert", "fragment.frag");

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// while循环/游戏循环（game loop）---------------------------------
	while(!glfwWindowShouldClose(window))
	{
		// 检查及调用事件
		glfwPollEvents();

		// 这里是渲染命令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		// 创建变换矩阵
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, glm::radians((GLfloat)glfwGetTime()*50.0f), glm::vec3(0.0f, 0.0f, 1.0f));


		// 将变换矩阵传给Uniform变量
		GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		// 将两个图片传给Uniform变量
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);

		// 绘制
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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