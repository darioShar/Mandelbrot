   #include "OpenGlSprite.h"


	OpenGlSprite::OpenGlSprite()
	{
		//Always initialize your buffer IDs to 0
		_vboID = 0;
	}


	OpenGlSprite::~OpenGlSprite()
	{
		//Always remember to delete your buffers when
		//you are done!
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}


	void OpenGlSprite::init()
	{
		if (_vboID == 0) {
			glGenBuffers(1, &_vboID);
		}

		setVertexData();

		//Tell opengl to bind our vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Upload the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(_vertexData), _vertexData, GL_STATIC_DRAW);

		//Unbind the buffer (optional)
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void OpenGlSprite::draw()
	{
		//bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Tell opengl that we want to use the first
		//attribute array. We only need one array right
		//now since we are only using position.
		glEnableVertexAttribArray(0);

		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (void*)offsetof(MyVertex, position));
		//This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(MyVertex), (void*)offsetof(MyVertex, color));

		//Draw the 6 vertices to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//Disable the vertex attrib array. This is not optional.
		glDisableVertexAttribArray(0);

		//Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);


	}

	void OpenGlSprite::setVertexData() {
		// First Triangle
		_vertexData[0].setPosition(-1.0f, -1.0f);
		_vertexData[1].setPosition(1.0f, -1.0f);
		_vertexData[2].setPosition(1.0f, 1.0f);

		// Second one
		_vertexData[3].setPosition(-1.0f, -1.0f);
		_vertexData[4].setPosition(-1.0f, 1.0f);
		_vertexData[5].setPosition(1.0f, 1.0f);


		for (int i = 0; i < 6; i++) {
			_vertexData[i].setColor(255, 255, 255, 255);
		}
	}
