#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Application::Application(const std::string& title, unsigned int width, unsigned int height)
{
	if (!glfwInit())
	{
		std::cout << "Couldn't initialize glfw.\n";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		std::cin.get();
		std::terminate();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

		std::cin.get();
		std::terminate();
	}

}

Application::~Application()
{
	glfwTerminate();
}


void Application::run()
{
	this->initialize();

	glfwSwapInterval(0);
	glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		this->update();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void Application::initialize() { }
void Application::update() { }
