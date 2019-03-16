#pragma once
#include "Graphics.h"
#include "RGBTexture/RGBTexture.h"

class Graphics
{
public:
	void draw(RGBTexture& texture);

	static Graphics* const getGraphics();

	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics& graphics) = delete;

private:
	static Graphics* instance;

	static void initializeShader();
	static void initializeVertexData();

	Graphics();
	~Graphics();

	static unsigned int shaderProgramID;
	static unsigned int vao;
	static unsigned int vbo;
	static unsigned int ibo;

};
