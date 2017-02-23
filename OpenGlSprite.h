#pragma once
#include <glew\glew.h>
#include <cmath>
#include <cstddef>

struct MyVertex {
	struct Position {
		float x;
		float y;
	} position;
	struct Color {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	} color;

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}
};



class OpenGlSprite
{
	float _x;
	float _y;
	float _height;
	float _width;
	GLuint _vboID;   // GLuint = unsigned int of 32 bit.

	MyVertex _vertexData[6];

	void setVertexData();

public:
	OpenGlSprite();
	~OpenGlSprite();

	void init();
	void draw();
};

