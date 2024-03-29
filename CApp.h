#ifndef _CAPP_H_
	#define _CAPP_H_

#include <SDL2/SDL.h>

#include "CSurface.h"
#include "CEvent.h"
#include "CAnimation.h"
#include "CEntity.h"
#include "CMap.h"
#include "CPlayer.h"

class CApp : public CEvent {
	private:
		bool Running;

		SDL_Surface* Surf_Display;
		SDL_Surface* Surf_Test;

		SDL_Window *win;
		SDL_Renderer *renderer;

		SDL_Texture *scr_texture;

		SDL_DisplayMode display;

		CMap gameMap;
		CPlayer player;

		double time;
		double oldTime;

		int width,height;
		int tx_width,tx_height;

	public:
		CApp();
		
		int OnExecute();
		bool OnInit();
		void OnEvent(SDL_Event* Event);
		void OnLButtonDown(int mX, int mY);
		void OnKeyDown(SDL_Keycode sym, Uint16 mod);
		void OnKeyUp(SDL_Keycode sym, Uint16 mod);
		void OnExit();
		void OnLoop();
		void OnRender();
		void OnCleanup();
		void playerControl();
		void display_buffer(Uint32* buffer);
};

#endif
