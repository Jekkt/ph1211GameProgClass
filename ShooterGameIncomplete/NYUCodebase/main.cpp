#include "ClassDemoApp.h"


// 60 FPS (1.0f/60.0f)

#define FIXED_TIMESTEP 0.0166666f;
#define MAX_TIMESTEPS 6;


int main(int argc, char *argv[])
{
	ClassDemoApp app;
	while(!app.UpdateAndRender()){}
		return 0;
	}

