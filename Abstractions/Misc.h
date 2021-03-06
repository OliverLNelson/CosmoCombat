//misc
#include <chrono>
int randint(int min, int max);
void smoothFinish(SDL_Window* window, SDL_Renderer* renderer);
void quickInit();
void quickInit(int colorDepth, int samples);

int randint(int min, int max) {
	return min + rand() % (max - min);
}

int now(){

	return chrono::system_clock::now().time_since_epoch().count();

}

int clamp(int val, int min, int max){

	if(val<min){
		return min;
	}
	if(val>max){
		return max;
	}
	return val;

}

float fclamp (float val, float min, float max){
	if(val<min){
		return min;
	}
	if(val>max){
		return max;
	}
	return val;
}

void smoothFinish(SDL_Window *window,SDL_Renderer*renderer) { //smoothly close and finish data buffers for the end of the program
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();
}
void quickInit() {
    quickInit(8, 2);
}
void quickInit(int colorDepth ,int samples) {
	// should be       8             2
	//most likely
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, colorDepth);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, colorDepth);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, colorDepth);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, colorDepth);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, samples);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}


//anti-error main method;
