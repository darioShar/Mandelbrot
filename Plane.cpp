#include "Plane.h"


	Plane::Plane(Vue const & view)
		: _view(view)
		, _renderState(RenderState::Running)
	{
		parametersFile.open("Parameters.txt", ios::app);
		if (!parametersFile.is_open()) {
			fatalError("Couldn't open file to write parameters.");
		}
	}


	Plane::~Plane()
	{
	}

	void Plane::initSystems()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		_window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
		//SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
		if (_window == nullptr) {
			fatalError("SDL_Window could not be created.");
		}
		SDL_GLContext glContext = SDL_GL_CreateContext(_window);
		if (glContext == nullptr) {
			fatalError("SDL_GL context could not be created.");
		}

		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew.");
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// Background white
		glClearColor(0.0, 1.0, 1.0, 1.0);

		// Sprite
		_sprite.init();

		initShaders();
	}

	void Plane::initShaders() {
		_colorProgram.compileShaders("Shaders/NoChanges.vert", "Shaders/CalculationAndColorShader.frag");
		_colorProgram.addAttribute("vertexPosition");
		_colorProgram.addAttribute("vertexColor");
		_colorProgram.linkShaders();
	}

	void Plane::processInput() {
		SDL_Event evnt;
		while (SDL_PollEvent(&evnt)) {
			switch (evnt.type) {
			case SDL_QUIT:
				_renderState = RenderState::Exit;
				break;
			case SDL_MOUSEBUTTONDOWN:
				printf("Parameters :\n\
				Xmin = %.18lf,\n\
				Xmax = %.18lf,\n\
				Ymin = %.18lf,\n\
				Ymax = %.18lf\n\n\
				Mouse Cursor Position : %.18lf , %.18lf\n\n\n",
					_view.xmin,
					_view.xmax,
					_view.ymin,
					_view.ymax,
					(double)evnt.motion.x * (_view.xmax - _view.xmin) / (double)WIDTH,
					(double)evnt.motion.y * (_view.ymax - _view.ymin) / (double)HEIGHT);
				parametersFile << fixed << setprecision(numeric_limits<double>::digits10 + 1) << "Parameters :\nXmin = " << _view.xmin << "\nXmax = " << _view.xmax << "\nYmin = " << _view.ymin << "\nYmax = " << _view.ymax << "\n\nMouse Cursor : " <<
					(double)evnt.motion.x * (_view.xmax - _view.xmin) / (double)WIDTH << " , " << (double)evnt.motion.y * (_view.ymax - _view.ymin) / (double)HEIGHT << "\n\n\n";
				break;
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.sym) {
				case SDLK_z:
					_view.move(0.0, MOVE_FACTOR);
					break;
				case SDLK_s:
					_view.move(0.0, -MOVE_FACTOR);
					break;
				case SDLK_q:
					_view.move(ASPECT_RATIO * (-MOVE_FACTOR), 0.0f);
					break;
				case SDLK_d:
					_view.move(ASPECT_RATIO * MOVE_FACTOR, 0.0f);
					break;
				case SDLK_e:
					_view.zoom(ZOOM_FACTOR);
					MOVE_FACTOR /= ZOOM_FACTOR;
					break;
				case SDLK_a:
					_view.zoom(1.0f / ZOOM_FACTOR);
					MOVE_FACTOR *= ZOOM_FACTOR;
					break;

				}
				break;
			}
		}
	}

	void Plane::drawGame() {
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_colorProgram.use();

		GLuint uniformLocation;
		uniformLocation = _colorProgram.getUniformLocation("WIDTH");
		glUniform1i(uniformLocation, WIDTH);

		uniformLocation = _colorProgram.getUniformLocation("HEIGHT");
		glUniform1i(uniformLocation, HEIGHT);

		uniformLocation = _colorProgram.getUniformLocation("iter");
		glUniform1i(uniformLocation, ITERATIONS);

		uniformLocation = _colorProgram.getUniformLocation("xmin");
		glUniform1d(uniformLocation, _view.xmin);

		uniformLocation = _colorProgram.getUniformLocation("xmax");
		glUniform1d(uniformLocation, _view.xmax);

		uniformLocation = _colorProgram.getUniformLocation("ymin");
		glUniform1d(uniformLocation, _view.ymin);

		uniformLocation = _colorProgram.getUniformLocation("ymax");
		glUniform1d(uniformLocation, _view.ymax);


		_sprite.draw();
		_colorProgram.unuse();
		SDL_GL_SwapWindow(_window);
	}

	void Plane::gameLoop() {
		while (_renderState == RenderState::Running) {
			processInput();
			drawGame();
		}
	}


	void Plane::run() {
		initSystems();
		gameLoop();
	}
