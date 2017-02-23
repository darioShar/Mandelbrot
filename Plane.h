#pragma once
#include <glew\glew.h>
#include <SDL\SDL.h>
#include "View.h"
#include "GLSLProgram.h"
#include "OpenGlSprite.h"
#include <limits>
#include <iomanip>

	using namespace std;

	constexpr int WIDTH = 1920;
	constexpr int HEIGHT = 1080;
	constexpr double ASPECT_RATIO = (double)WIDTH / (double)HEIGHT;

	constexpr int ITERATIONS = 10000;
	constexpr double ZOOM_FACTOR = 1.3;



	enum RenderState {
		Running,
		Exit
	};

	class Plane
	{
		double MOVE_FACTOR = 0.2;
		Vue _view;
		ofstream parametersFile;

		void initSystems();
		void initShaders();
		void gameLoop();
		void processInput();
		void drawGame();

		RenderState _renderState;
		SDL_Window* _window;
		OpenGlSprite _sprite;
		GLSLProgram _colorProgram;

	public:
		Plane(Vue const &);
		~Plane();

		void run();

	};
