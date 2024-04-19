#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>

#include "window.h"
#include "renderer/shader.h"
#include "core/core.h"

#include "renderer/buffer.h"

namespace ray3D
{
	window::window(const ui32 Width, const ui32 Height, const std::string& Title):
		mWidth(Width), mHeight(Height), mTitle(Title)
	{

		logger::init();

		if (!glfwInit())
		{
			R3D_LOGE("Failed to initalize GLFW");
			return;
		}
		R3D_LOGD("Successfully initalized GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Create Window
		mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
		if (!mWindow)
		{
			R3D_LOGE("Failed to create Window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(mWindow);

		//Load OpenGL functions
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			R3D_LOGE("Failed to initalize GLAD (OpenGL Loader)");
			glfwTerminate();
			return;
		}
	}

	window::~window()
	{
		logger::shutdown();
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	auto window::run() -> void
	{

		//Read and Create Shaders
		shader testShader(R"(E:\Live Tutorial\ray3D\ray3D\src\shaders\vert.glsl)", R"(E:\Live Tutorial\ray3D\ray3D\src\shaders\frag.glsl)");

		//Vertex
		std::vector<f32> vertices = 
		{
				//Position			//Color
			-0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,		//0
			0.5f, 0.5f, 0.0f,   0.0f, 0.2f, 0.0f,		//1
			0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,		//2
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,		//3
		};

		std::vector<ui32> indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		std::shared_ptr<vertexBuffer> vertBuffer = vertexBuffer::create(vertices, vertAttribLayoutType::pos_col);
		std::shared_ptr<indexBuffer> idxBuffer = indexBuffer::create(indices);

		glViewport(0, 0, mWidth, mHeight);

		while (!glfwWindowShouldClose(mWindow))
		{
			glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			testShader.bind();
			vertBuffer->bind();
			idxBuffer->bind();
			
			glDrawElements(GL_TRIANGLES, idxBuffer->getCount(), GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(mWindow);
			glfwPollEvents();
		}
	}
}