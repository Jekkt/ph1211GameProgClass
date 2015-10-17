#include "ClassDemoApp.h";

TitleMenu *Menu;
gameLevel *Level;
gameOver *Over;

ClassDemoApp::ClassDemoApp() {
	Setup();	
}

ClassDemoApp::~ClassDemoApp() {
	delete program;
	delete Menu;
	delete Level;
	delete Over;
	SDL_JoystickClose(joystick);
	SDL_QUIT;
}

GLuint ClassDemoApp::LoadTexture(const char *image_path) {

	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(surface);

	return textureID;

}

void ClassDemoApp::Render() {


	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	projectionMatrix.setOrthoProjection(-x_units, x_units, -y_units, y_units, -1.0f, 1.0f);

	modelMatrix.identity();

	program->setModelMatrix(modelMatrix);
	program->setProjectionMatrix(projectionMatrix);
	program->setViewMatrix(viewMatrix);

	glUseProgram(program->programID);

	

	switch (state) {
	case STATE_MAIN_MENU:
		Menu->Render();
		break;
	case STATE_GAME_LEVEL:
		Level->Render();
		break;
	case STATE_GAME_OVER:
		Over->Render();
	}

	SDL_GL_SwapWindow(displayWindow);

}

void ClassDemoApp::Update(float elapsed) {
	//update entities
	//first y
	/*
	player.update(elapsed);

	player.y += player.velocity_Y * elapsed;


	float penetration = fabs( fabs(player.y - block.y) - player.height/2.0f - block.height / 2.0f);
	*/

	//then x

	
	
	


	switch (state) {
	case STATE_MAIN_MENU:
		Menu->Update(elapsed);
		elapsedTime += elapsed;
		if (elapsedTime > 6.0f) {
			state = 1;
		}
		break;
	case STATE_GAME_LEVEL:
		Level->Update(elapsed);
		if (Level->gameIsOver) {
			state = 2;
		}
		break;
	case STATE_GAME_OVER:
		Over->Update(elapsed);
	}

}

void ClassDemoApp::DrawSpriteSheetSprite(int index, int spriteCountX, int spriteCountY) {

	float u = (float)(((int)index) % spriteCountX) / (float)spriteCountX;
	float v = (float)(((int)index) / spriteCountX) / (float)spriteCountY;

	float width = 1.0f / (float)spriteCountX;
	float height = 1.0f / (float)spriteCountY;

	

}

void ClassDemoApp::Setup() {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

	SDL_Joystick *joystick = SDL_JoystickOpen(0);

	displayWindow = SDL_CreateWindow("Cool Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x_reso, y_reso, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
#ifdef _WINDOWS
	glewInit();
#endif

	glViewport(0, 0, x_reso, y_reso);

	program = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
	Menu = new TitleMenu(program);
	Level = new gameLevel(program);
	Over = new gameOver(program);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ClassDemoApp::ProcessInput() {

	while (SDL_PollEvent(&event)) {


		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			bool isPressed = false;
			switch (event.key.keysym.sym) {
			case SDLK_o:
				state--;
				std::cout << "Switched State Down " << state << std::endl;
				break;
			case SDLK_p:
				state++;
				std::cout << "Switched State Up" << state << std::endl;
				break;
			case SDLK_SPACE:
				std::cout << "Space pressed!" << std::endl;
				if (!Level->bullets[0]->isShot) {
					Level->bullets[0]->isShot = true;
					Level->bullets[0]->isActive = true;
					Level->bullets[0]->velocity_y = 3;
					Level->bullets[0]->xPos = Level->player->xPos;
					Level->bullets[0]->yPos = Level->player->yPos;
				}
				break;
			case SDLK_LEFT:
				if (!leftIsPressed) {
					Level->player->velocity_x = -2;
					leftIsPressed = true;
					}
					break;
				case SDLK_RIGHT:
					Level->player->velocity_x =  2;
					rightIsPressed = true;
					break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			bool isPressed = false;
			switch (event.key.keysym.sym) {
			case SDLK_o:
				break;
			case SDLK_p:
				break;
			case SDLK_SPACE:
				isShooting = false;
				Level->bullets[0]->acceleration_y = 0;

				break;
			case SDLK_LEFT:
				if (!rightIsPressed) {
					Level->player->velocity_x = 0;
				}
				leftIsPressed = false;
				break;
			case SDLK_RIGHT:
				rightIsPressed = false;

				if (!leftIsPressed) {
					Level->player->velocity_x = 0;
				}
				break;
			}
		}
		else if (event.type == SDL_MOUSEMOTION) {

			float unitX = (((float)event.motion.x / x_reso) * x_units) - x_units / 2.0f;
			float unitY = (((float)(y_reso - event.motion.y) / y_reso) * y_units) - y_units / 2.0f;

			float positionX = unitX;
			float positionY = unitY;

		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {

			printf("INDEX: %i\n", (event.button));
			angle += 3.1415926536f * 0.25f;

		}
		else if (event.type == SDL_JOYAXISMOTION) {
			if (event.jaxis.which == 0) {
				if (event.jaxis.axis == 0) {
					float floatVal = ((float)event.jaxis.value) / 32767.0f;
					//ADD fabs threshold
					float xDir = floatVal;
				}
				else if (event.jaxis.axis == 1) {
					float floatVal = ((float)event.jaxis.value) / 32767.0f;
					//ADD fabs threshold
					float yDir = floatVal;
				}
			}
		}
		else if (event.type == SDL_JOYBUTTONDOWN) {

			if (event.jbutton.button == 0) {
				//turn turn quarter pi

			}

		}

		//Keyboard Input
		const Uint8 *keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_LEFT]) {
			//go left
			//std::cout << "Pressing Left" << std::endl;
			//angle += elapsed;
		}
		else if (keys[SDL_SCANCODE_RIGHT]) {
			// go right
			//std::cout << "Pressing Right" << std::endl;
			//angle -= elapsed;
		}
		

	}

}

bool ClassDemoApp::UpdateAndRender() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;


	ProcessInput();
	Update(elapsed);
	Render();

	return done;
}