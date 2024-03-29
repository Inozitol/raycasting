#include "CApp.h"

bool CApp::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		return false;
	}
	win = SDL_CreateWindow("Wolfenstein Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

	renderer = SDL_CreateRenderer(win, -1, 0);

	if(win == NULL){
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, 640, 480);

	scr_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);

	return true;
}
