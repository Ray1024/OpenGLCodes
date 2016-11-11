// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>

#include "Shader.h"

#include "FreeImage.h"

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

	FreeImage_Initialise(TRUE);

	// ������----------------------------------------------------------------------------
	//ͼ1
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	// ��ȡ��ɫģʽ
	fif = FreeImage_GetFileType("../Resource/container.jpg");
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename("../Resource/container.jpg");
	if(fif == FIF_UNKNOWN)
		return -1;

	FIBITMAP * bmp = FreeImage_Load(fif,"../Resource/container.jpg");
	unsigned char* bits = FreeImage_GetBits(bmp);
	int width1 = FreeImage_GetWidth(bmp);
	int height1 = FreeImage_GetHeight(bmp);

	GLuint texture1;
	glGenTextures(1, &texture1);

	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB , width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);
	glGenerateMipmap(GL_TEXTURE_2D);

	FreeImage_Unload(bmp);
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

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ���Ӷ�������
	// �������� 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0); 
	// ��ɫ���� 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat))); 
	glEnableVertexAttribArray(1);
	//  ������������
	glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 8 * sizeof(GLfloat), (GLvoid * )(6*sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// �����������VAO---------------------------------------------------------------------
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// 1. ��VAO
	glBindVertexArray(VAO);

	// 2. �Ѷ������鸴�Ƶ��������ṩ��OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ��EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

	// 3. ���ö�������ָ��
	// �������� 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0); 
	// ��ɫ���� 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat))); 
	glEnableVertexAttribArray(1);
	//  ������������
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

		glBindTexture(GL_TEXTURE_2D, texture1);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// ��������
		glfwSwapBuffers(window);
	}

	// 
	FreeImage_DeInitialise();

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