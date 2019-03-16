#pragma once

struct Pixel
{
	Pixel()
		:r(0x11), g(0x22), b(0x33) {};
	Pixel(unsigned char R, unsigned char G, unsigned char B)
		:r(R), g(G), b(B) {};


	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class RGBTexture
{
public:
	RGBTexture(unsigned int width, unsigned int height);
	~RGBTexture();

	void update();

	inline Pixel& getPixel(unsigned int x, unsigned int y) { return imageBuffer[x][y]; };

	inline unsigned int getTextureID() { return activeTextureID; }
	inline unsigned int getWidth() const { return width; }
	inline unsigned int getHeight() const { return height; }

private:
	Pixel** imageBuffer;
	const unsigned int width;
	const unsigned int height;

	unsigned int activeTextureID;
	unsigned int textureID;

	static unsigned int textureCount;
};
