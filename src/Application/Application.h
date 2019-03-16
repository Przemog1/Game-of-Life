#pragma once

#include <string>

struct GLFWwindow;

class Application
{
public:
	Application(const std::string& title, unsigned int width, unsigned int height);
	virtual ~Application();

	void run();

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
private:
	virtual void initialize() = 0;
	virtual void update() = 0;

	GLFWwindow* window;
};
