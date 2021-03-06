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

	Mix_FreeChunk(jumpSound);
	Mix_FreeChunk(bgMus);

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

	projectionMatrix.setOrthoProjection(-ortho_width, ortho_width, -ortho_height, ortho_height, -1.0f, 1.0f);

	modelMatrix.identity();

	//program->setModelMatrix(modelMatrix);
	program->setProjectionMatrix(projectionMatrix);
	//program->setViewMatrix(viewMatrix);

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

	if (Level->test->isOnGround) {
		isJumping = false;
		doublejump = false;
	}

	if (!leftIsPressed && !rightIsPressed) {
		if(Level->test->velocity_x < 0){
			Level->test->velocity_x += 1.8f*elapsed;
			if (Level->test->velocity_x >= 0) {
				Level->test->velocity_x = 0.0f;
				Level->test->acceleration_x = 0.0f;
			}
		}
		else {
			Level->test->velocity_x -= 1.8f*elapsed;
			if (Level->test->velocity_x <= 0) {
				Level->test->velocity_x = 0.0f;
				Level->test->acceleration_x = 0.0f;
			}
		}
	}
	


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
		if (!musicIsPlaying) {
			Mix_PlayChannel(-1, bgMus, -1);
			musicIsPlaying = true;
		}
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

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

	

	jumpSound = Mix_LoadWAV("Jump10.wav");
	bgMus = Mix_LoadWAV("undyne_genocide");

	

}

void ClassDemoApp::ProcessInput() {

	while (SDL_PollEvent(&event)) {


		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			bool isPressed = false;
			switch (event.key.keysym.sym) {
			case SDLK_l:
				std::cout << Level->test->xPos << std::endl;
				std::cout << Level->test->yPos << std::endl;
				std::cout << Level->entities[3]->xPos << std::endl;
				std::cout << Level->entities[3]->yPos << std::endl;
				break;
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
				if (!isJumping) {
					isJumping = true;
					Level->test->velocity_y += 1.2f;
					Level->test->isOnGround = false;
					Mix_PlayChannel(-1, jumpSound, 0);
					
				}
				else if (!doublejump && isJumping) {
					doublejump = true;
					Level->test->velocity_y += 1.2f;
					Mix_PlayChannel(-1, jumpSound, 0);
				}
				break;
			case SDLK_LEFT:
				if (!leftIsPressed) {
					Level->test->acceleration_x = -1.8f;
					Level->test->velocity_x = Level->test->velocity_x / 2.0f;
					leftIsPressed = true;
					}
					break;
				case SDLK_RIGHT:
					if (!rightIsPressed) {
						Level->test->acceleration_x = 1.8f;
						Level->test->velocity_x = Level->test->velocity_x / 2.0f;
						rightIsPressed = true;
					}
					break;
				default:

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
				
				break;
			case SDLK_LEFT:
				if (!rightIsPressed) {
					Level->test->acceleration_x = 0;
				}
				leftIsPressed = false;
				break;
			case SDLK_RIGHT:
				rightIsPressed = false;

				if (!leftIsPressed) {
					Level->test->acceleration_x = 0;
				}
				break;
			}
		}
		else if (event.type == SDL_MOUSEMOTION) {

			float unitX = (((float)event.motion.x / x_reso) * ortho_width) - ortho_width / 2.0f;
			float unitY = (((float)(y_reso - event.motion.y) / y_reso) * ortho_height) - ortho_height / 2.0f;

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

	float fixedElapsed = elapsed + timeLeftOver;
	if (fixedElapsed > 0.0166666f * 6.0f) {
		fixedElapsed = 0.0166666f * 6.0f;
	}
	while (fixedElapsed >= 0.0166666f) {
		fixedElapsed -= 0.0166666f;
		Update(fixedElapsed);
	}
	timeLeftOver = fixedElapsed;

	
	//Update(elapsed);
	Render();

	return done;
}

