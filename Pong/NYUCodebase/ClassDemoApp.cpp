#include "ClassDemoApp.h";

ClassDemoApp::ClassDemoApp() {
	Setup();
}

ClassDemoApp::~ClassDemoApp() {
	delete program;
	SDL_JoystickClose(joystick);
	//SDL_QUIT;
}

GLuint ClassDemoApp::loadTexture(const char *image_path) {

	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	return textureID;

}

void ClassDemoApp::DrawSpriteSheetSprite(int index, int spriteCountX, int spriteCountY) {

	float u = (float)(((int)index) % spriteCountX) / (float)spriteCountX;
	float v = (float)(((int)index) / spriteCountX) / (float)spriteCountY;

	float width = 1.0 / (float)spriteCountX;
	float height = 1.0 / (float)spriteCountY;

	

}

void ClassDemoApp::Setup() {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

	SDL_Joystick *joystick = SDL_JoystickOpen(0);

	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
#ifdef _WINDOWS
	glewInit();
#endif




	glViewport(0, 0, 640, 360);

	program = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");

}

void ClassDemoApp::ProcessInput() {
	if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
		done = true;
	}
	else if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
			angle = 0.0f;
			std::cout << "Space pressed!" << std::endl;
		}
	}
	else if (event.type == SDL_MOUSEMOTION) {

		float unitX = (((float)event.motion.x / x_reso) * x_units) - x_units / 2.0f;
		float unitY = (((float)(y_reso - event.motion.y) / y_reso) * y_units) - y_units / 2.0f;

		float positionX = unitX;
		float positionY = unitY;

	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {

		printf("INDEX: %i\n", event.button);
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
}

void ClassDemoApp::UpdateAndRender() {

	ProcessInput();

}