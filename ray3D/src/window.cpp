#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>

#include "window.h"
#include "shader.h"
#include "log.h"

namespace ray3D
{
	window::window(const uint32_t Width, const uint32_t Height, const std::string& Title):
		mWidth(Width), mHeight(Height), mTitle(Title)
	{
		if (!glfwInit())
		{
			LOG("Failed to initalize GLFW");
			return;
		}
		LOG("Successfully initalized GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Create Window
		mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
		if (!mWindow)
		{
			LOG("Failed to create Window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(mWindow);

		//Load OpenGL functions
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG("Failed to initalize GLAD (OpenGL Loader)");
			glfwTerminate();
			return;
		}
	}

	window::~window()
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	auto window::run() -> void
	{

		//Read and Create Shaders
		shader testShader(R"(E:\Live Tutorial\ray3D\ray3D\src\shaders\vert.glsl)", R"(E:\Live Tutorial\ray3D\ray3D\src\shaders\frag.glsl)");

		//Vertex
		float vertices[] = 
		{
				//Position			//Color
			0.0f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,		//0
			0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,		//1
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,		//2
		};

		uint32_t indices[] = 
		{
			0, 1, 2
		};

		GLuint vertBuffer, vertAttributeArray, indexBuffer;

		glGenBuffers(1, &vertBuffer);
		glGenBuffers(1, &indexBuffer);
		glGenVertexArrays(1, &vertAttributeArray);

		glBindVertexArray(vertAttributeArray);
		glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glViewport(0, 0, mWidth, mHeight);

		while (!glfwWindowShouldClose(mWindow))
		{
			glClearColor(0.5f, 0.0f, 0.5f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			testShader.bind();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBindVertexArray(vertAttributeArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(mWindow);
			glfwPollEvents();
		}
	}
}