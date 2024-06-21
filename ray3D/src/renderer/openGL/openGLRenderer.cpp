#include "openGLRenderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include "renderer/buffer.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "resource/mesh.h"

#include "world/primitives.h"
#include "world/camera.h"

namespace ray3D
{

	std::unique_ptr<shader> testShader;
	std::unique_ptr<shader> lightShader;
	std::unique_ptr<shader> gridShader;
	std::unique_ptr<mesh> cube;
	std::unique_ptr<mesh> pointLight;
	std::unique_ptr<mesh> grid;
	std::unique_ptr<camera> flyCam;
	std::unique_ptr<texture> sampleTexture;

	glm::vec3 lightPosition;
	glm::vec3 lightColor;

	glm::mat4 modelMat;

	auto openGLRenderer::init(ui32 width, ui32 height) -> bool
	{
		const GLubyte* vendorName = glGetString(GL_VENDOR);
		R3D_LOGD("Graphics vendor : {}", (const char*)vendorName);

		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		cube = primitives::getCube();
		pointLight = primitives::getCube();
		grid = primitives::getGrid(100, 15.0f, 40.0f);

		//Read and Create Shaders
		testShader = shader::create(R"(E:\Live Tutorial\ray3D\assets\shaders\vert.glsl)", R"(E:\Live Tutorial\ray3D\assets\shaders\frag.glsl)");
		lightShader = shader::create(R"(E:\Live Tutorial\ray3D\assets\shaders\light_vert.glsl)", R"(E:\Live Tutorial\ray3D\assets\shaders\light_frag.glsl)");
		gridShader = shader::create(R"(E:\Live Tutorial\ray3D\assets\shaders\grid_vert.glsl)", R"(E:\Live Tutorial\ray3D\assets\shaders\grid_frag.glsl)");
		sampleTexture = texture::create(R"(E:\Live Tutorial\ray3D\assets\textures\TCom_Pavement_Medieval_1K_albedo.png)");

		lightPosition = glm::vec3(-2.0f, 0.0f, -2.0f);
		lightColor = glm::vec3(1.0f);

		lightShader->bind();
		lightShader->setUniformVec3("lightColor", lightColor);

		cameraProps props = {};
		props.aspectRatio = _f32(width) / _f32(height);
		props.fov = 45.0f;
		props.cameraFlySpeed = 5.0f;
		props.cameraSensitivity = 5.0f;
		props.position = glm::vec3(0.0f, 0.0f, -5.0f);
		props.rotation = glm::vec3(90.0f, 0.0f, 0.0f);
		props.zFar = 100.0f;
		props.zNear = 0.001f;

		flyCam = std::make_unique<camera>(props);

		return true;
	}

	auto openGLRenderer::beginFrame() -> void
	{
		glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	auto openGLRenderer::draw(f32 deltaTime) -> void
	{
		//Render light cube

		lightShader->bind();
		lightShader->setUniformMat4("projectionMat", flyCam->getProjectionMat());
		lightShader->setUniformMat4("viewMat", flyCam->getViewMat());
		lightShader->setUniformVec3("lightColor", lightColor);

		lightPosition = glm::vec3(6.0f * cos(glfwGetTime()), 6.0f * sin(glfwGetTime()), 0.0f);
		modelMat = glm::translate(glm::mat4(1.0f), lightPosition);
		modelMat = glm::scale(modelMat, glm::vec3(0.1f));
		lightShader->setUniformMat4("modelMat", modelMat);

		pointLight->getVertexBuffer()->bind();
		pointLight->getIndexBuffer()->bind();

		glDrawElements(GL_TRIANGLES, pointLight->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);

		//Render cube
		flyCam->update(deltaTime);

		testShader->bind();
		testShader->setTexture("albedo", sampleTexture->getTextureID(), 0);
		testShader->setUniformMat4("projectionMat", flyCam->getProjectionMat());
		testShader->setUniformMat4("viewMat", flyCam->getViewMat());

		modelMat = glm::mat4(1.0f);
		testShader->setUniformMat4("modelMat", modelMat);

		testShader->setUniformVec3("lightPosition", lightPosition);
		testShader->setUniformVec3("cameraPosition", flyCam->getPosition());
		testShader->setUniformVec3("lightColor", lightColor);

		cube->getVertexBuffer()->bind();
		cube->getIndexBuffer()->bind();

		glDrawElements(GL_TRIANGLES, cube->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);

		gridShader->bind();
		gridShader->setUniformMat4("projectionMat", flyCam->getProjectionMat());
		gridShader->setUniformMat4("viewMat", flyCam->getViewMat());
		gridShader->setUniformMat4("modelMat", glm::mat4(1.0f));

		grid->getVertexBuffer()->bind();
		grid->getIndexBuffer()->bind();

		glLineWidth(1.2f);

		glDrawElements(GL_LINES, grid->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}
	
	auto openGLRenderer::endFrame() -> void
	{
	}

	auto openGLRenderer::onResize(ui32 width, ui32 height) -> void
	{
		mWidth = width;
		mHeight = height;
		flyCam->onResize(width, height);
	}
}