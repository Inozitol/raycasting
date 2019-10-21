#include "CApp.h"

#include <iostream>
#include <ctime>

CApp::CApp() {     
	Surf_Display = NULL;
	win = NULL;
	renderer = NULL;

	Running = true;

	time=0;
	oldTime=0;
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

int main(int argc, char* argv[]){
	CApp theApp;
	
	return theApp.OnExecute();
}
