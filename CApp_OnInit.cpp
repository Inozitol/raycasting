#include "CApp.h"

bool CApp::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		return false;
	}
	win = SDL_CreateWindow("Doom Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if(win == NULL){
		return false;
	}

	return true;
}
