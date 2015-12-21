#include "ClassDemoApp.h";

#define PI 3.14159265359f;

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//projectionMatrix.setOrthoProjection(-ortho_width, ortho_width, -ortho_height, ortho_height, -1.0f, 1.0f);

	projectionMatrix.setPerspectiveProjection(45.0f * 3.14159265359f/180.0f, x_reso/y_reso, 0.1f, 200.0f);
	//gluLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0);
	//modelMatrix.identity();
	//viewMatrix.identity();


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

	//SDL_WarpMouseInWindow(displayWindow, x_reso / 2, y_reso / 2);

	

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
	//SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	glViewport(0, 0, x_reso, y_reso);
	SDL_WarpMouseInWindow(displayWindow, x_reso / 2, y_reso / 2);


	program = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
	Menu = new TitleMenu(program);
	Level = new gameLevel(program);
	Over = new gameOver(program);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//depth buffer writing;
	glDepthMask(GL_TRUE);

	glEnable(GL_DEPTH_TEST); // enable depth testing

	glDepthFunc(GL_LEQUAL);

	camRot = Vector3(0,0,0);

	glGenFramebuffers(1, &frameBuffer);


	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);



	jumpSound = Mix_LoadWAV("Jump10.wav");
	bgMus = Mix_LoadWAV("undyne_genocide");

	//vector to glsl shaders
	//GLint lightPositionsUniform = glGetUniformLocation(program.programID, "lightPositions");
	/**/



}

void ClassDemoApp::ProcessInput() {

	

	while (SDL_PollEvent(&event)) {
		

		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			bool isPressed = false;
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				done = true;
				break;


			case SDLK_w:
				Level->player1->acceleration_z = cos(-Level->player1->rotation.y) * -5.0f;
				Level->player1->acceleration_x = sin(-Level->player1->rotation.y) * -5.0f;
				printf("cosine: %f ", (cos(Level->player1->rotation.y)));
				printf(" sine: %f\n ", (sin(Level->player1->rotation.y)));
				break;
			case SDLK_a:
				Level->player1->acceleration_x = -5.0f;
				break;
			case SDLK_s:
				Level->player1->acceleration_z = cos(-Level->player1->rotation.y) * 5.0f;
				Level->player1->acceleration_x = sin(-Level->player1->rotation.y) * 5.0f;
				printf("cosine: %f ", (cos(Level->player1->rotation.y)));
				printf(" sine: %f\n ", (sin(Level->player1->rotation.y)));
				break;
			case SDLK_d:
				Level->player1->acceleration_x = 5.0f;
				break;

				
			case SDLK_l:
				vector = vector.normalize(Level->player1->position);
				std::cout << vector.x << " " << vector.y << " " << vector.z << std::endl;
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
					Level->player1->velocity_y += 1.2f;
					Level->player1->isOnGround = false;
					Mix_PlayChannel(-1, jumpSound, 0);

				}
				else if (!doublejump && isJumping) {
					doublejump = true;
					Level->player1->velocity_y += 1.2f;
					Mix_PlayChannel(-1, jumpSound, 0);
				}
				break;
			case SDLK_LEFT:
				Level->player1->rotation.y -= 0.1f;
				break;
			case SDLK_RIGHT:
				Level->player1->rotation.y += 0.1f;
				break;

			case SDLK_UP:
				Level->player1->rotation.x -= 0.1f;
				break;
			case SDLK_DOWN:
				Level->player1->rotation.x += 0.1f;
				break;
			default:

				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			bool isPressed = false;
			switch (event.key.keysym.sym) {
			case SDLK_w:
				//Level->player1->acceleration_z = 0.0f;
				//Level->player1->acceleration_x = 0.0f;

				printf("xPos: %f ", (Level->player1->position.x));
				printf(" zPos: %f\n ", (Level->player1->position.z));

				break;
			case SDLK_a:
				Level->player1->acceleration_x = 0.0f;
				break;
			case SDLK_s:
				//Level->player1->acceleration_z = 0.0f;
				//Level->player1->acceleration_x = 0.0f;
				break;
			case SDLK_d:
				Level->player1->acceleration_x = 0.0f;
				break;
			case SDLK_o:
				break;
			case SDLK_p:
				break;
			case SDLK_SPACE:
				isShooting = false;

				break;
			case SDLK_LEFT:
				if (!rightIsPressed) {
					Level->player1->acceleration_x = 0;
				}
				leftIsPressed = false;
				break;
			case SDLK_RIGHT:
				rightIsPressed = false;

				if (!leftIsPressed) {
					Level->player1->acceleration_x = 0;
				}
				break;
			}
		}
		else if (event.type == SDL_MOUSEMOTION) {



			//float unitX = (((float)event.motion.x / x_reso) * ortho_width) - ortho_width / 2.0f;
			float unitY = (float)(event.motion.xrel)/360.0f;
			float unitX = (float)(event.motion.yrel)/360.0f;

			float yaw = unitX;
			camRot.x += unitX;
			camRot.y += unitY;
			

			Level->yaw += yaw;

			Level->player1->rotation.x = camRot.x;
			Level->player1->rotation.y = camRot.y;

			if (Level->yaw > 360.0f) {
				Level->yaw = 0.0f;
			}

			if (Level->yaw < 0.0f) {
				Level->yaw = 360.0f;
			}

			//printf("xRot: %f ", (camRot.x));
			//printf(" yRot: %f\n ", (camRot.y));

			printf("xRot: %f ", (Level->player1->rotation.x));
			printf(" yRot: %f\n ", (Level->player1->rotation.y));

			//printf("yaw: %f\n", (Level->yaw));
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
	elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	ProcessInput();

	float fixedElapsed = elapsed + timeLeftOver;
	if (fixedElapsed > 0.0166666f * 6.0f) {
		fixedElapsed = 0.0166666f * 6.0f;
	}
	while (fixedElapsed >= 0.0166666f) {
		fixedElapsed -= 0.0166666f;
		//Update(fixedElapsed);
	}
	timeLeftOver = fixedElapsed;


	Update(elapsed);
	Render();

	return done;
}

