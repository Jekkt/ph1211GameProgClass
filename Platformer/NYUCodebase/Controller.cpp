/*

SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

// SDL_JoystickOpen is passed the joystick index

SDL_Joystick * playerOneController = SDL_JoystickOpen(0);

//game loop

// clean up for each open joystick

SDL_JoystickClose(playerOneController);


*/