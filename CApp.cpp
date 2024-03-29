#include "CApp.h"

#include <iostream>
#include <ctime>

CApp::CApp() {     
	Surf_Display = NULL;
	win = NULL;
	renderer = NULL;
	scr_texture = NULL;

	Running = true;

	time=0;
	oldTime=0;

	tx_width = 64;
	tx_height = 64;
}

int CApp::OnExecute() {
	if(OnInit() == false){
		return -1;
	}

	SDL_Event Event;

	while(Running){
		while(SDL_PollEvent(&Event)){
			OnEvent(&Event);
		}

		OnLoop();
		OnRender();
	}

	OnCleanup();

	return 0;
}

void CApp::playerControl(){
	oldTime = time;
	time = clock();
	double frameTime = (time - oldTime) / (double) CLOCKS_PER_SEC;
	double moveSpeed = frameTime * 5.0;
	double rotSpeed = frameTime * 3.0;
	double oldDirX;
	double oldDirY;
	double oldPlaneX;
	double oldPlaneY;
		if(keyStatus(SDLK_UP)){ 
			if(gameMap.Map[int(player.xPos + player.xDir * moveSpeed)][int(player.yPos)] == false) player.xPos += player.xDir * moveSpeed;
			if(gameMap.Map[int(player.xPos)][int(player.yPos + player.yDir * moveSpeed)] == false) player.yPos += player.yDir * moveSpeed;
		}

		if(keyStatus(SDLK_DOWN)){ 
			if(gameMap.Map[int(player.xPos - player.xDir * moveSpeed)][int(player.yPos)] == false) player.xPos -= player.xDir * moveSpeed;
			if(gameMap.Map[int(player.xPos)][int(player.yPos - player.yDir * moveSpeed)] == false) player.yPos -= player.yDir * moveSpeed;
		}

		if(keyStatus(SDLK_RIGHT)){ 
			oldDirX = player.xDir;
			player.xDir = player.xDir * cos(-rotSpeed) - player.yDir * sin(-rotSpeed);
			player.yDir = oldDirX * sin(-rotSpeed) + player.yDir * cos(-rotSpeed);
			oldPlaneX = player.xPlane;
			player.xPlane = player.xPlane * cos(-rotSpeed) - player.yPlane * sin(-rotSpeed);
			player.yPlane = oldPlaneX * sin(-rotSpeed) + player.yPlane * cos(-rotSpeed);
		}

		if(keyStatus(SDLK_LEFT)){
			oldDirX = player.xDir;
			player.xDir = player.xDir * cos(rotSpeed) - player.yDir * sin(rotSpeed);
			player.yDir = oldDirX * sin(rotSpeed) + player.yDir * cos(rotSpeed);
			oldPlaneX = player.xPlane;
			player.xPlane = player.xPlane * cos(rotSpeed) - player.yPlane * sin(rotSpeed);
			player.yPlane = oldPlaneX * sin(rotSpeed) + player.yPlane * cos(rotSpeed);
		}
}

void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod){
	pressKey(sym);
}

void CApp::OnKeyUp(SDL_Keycode sym, Uint16 mod){
	releaseKey(sym);
}

void CApp::display_buffer(Uint32* buffer){
	SDL_LockSurface(Surf_Display);
	Uint32* p_buffer;
	p_buffer = (Uint32*)Surf_Display->pixels;

	for(int x=0; x<display.w; x++){
		for(int y=0; y<display.h; y++){
			*p_buffer = buffer[y * display.w + x];
			p_buffer++;
		}
		p_buffer += Surf_Display->pitch / 4;
		p_buffer -= display.w;
	}
	SDL_UnlockSurface(Surf_Display);
}

int main(int argc, char* argv[]){
	CApp theApp;
	
	return theApp.OnExecute();
}

