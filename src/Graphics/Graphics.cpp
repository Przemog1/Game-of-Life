#include "Graphics.h"
#include <glad\glad.h>
#include <iostream>

void Graphics::initializeVertexData()
{
	float vertices[] = {
		-1.0f,  1.0f,	0.0f, 1.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,	1.0f, 0.0f,
		 1.0f,  1.0f,	1.0f, 1.0f
	};

	unsigned int indices[] = { 0, 1, 2, 3, 0, 2 };

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}
void Graphics::initializeShader()
{

	shaderProgramID = glCreateProgram();

	unsigned int vertexShader   = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertexShaderCode =
		"#version 330 core\n"
		"layout(location = 0)in vec2 position;\n"
		"layout(location = 1)in vec2 _texUV;\n"
		"out vec2 texUV;\n"
		"void main()\n { gl_Position = vec4(position , 0.0, 1.0); texUV = _texUV; }\0";

	const char* fragmentShaderCode =
		"#version 330 core\n"
		"out vec4 fragColor;\n"
		"in vec2 texUV;\n"
		"uniform sampler2D tex;\n"
		"void main()\n { fragColor = texture(tex,texUV); }\0";

	glShaderSource(vertexShader, 1, &vertexShaderCode, 0);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, 0);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	int vcs;
	int fcs;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vcs);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fcs);

	std::cout << vcs << fcs;

	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);

	glLinkProgram(shaderProgramID);
	glValidateProgram(shaderProgramID);

	glUseProgram(shaderProgramID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Graphics* const Graphics::getGraphics()
{
	if(!instance)
		instance = new Graphics();

	return instance;
}

void Graphics::draw(RGBTexture& texture)
{
	glUniform1i(glGetUniformLocation(shaderProgramID, "tex"), texture.getTextureID());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

Graphics::Graphics()
{
	initializeVertexData();
	initializeShader();
}

Graphics::~Graphics()
{
	glDeleteShader(shaderProgramID);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

Graphics* Graphics::instance = nullptr;

unsigned int Graphics::shaderProgramID = 0;
unsigned int Graphics::vao = 0;
unsigned int Graphics::vbo = 0;
unsigned int Graphics::ibo = 0;
