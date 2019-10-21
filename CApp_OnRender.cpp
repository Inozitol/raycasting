#include "CApp.h"
#include <cmath>

void CApp::OnRender(){
	SDL_DisplayMode display;

	for(int i=0; i<SDL_GetNumVideoDisplays(); ++i){
		if(SDL_GetCurrentDisplayMode(i, &display)){
			width=1200;
			height=900;
		}else{
			width=display.w;
			height=display.h;
		}
	}
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderClear(renderer);


	for(int x=0; x<width; x++){
		double cameraX = 2 * x / double(width) - 1;
		double rayDirX = player.xDir + player.xPlane * cameraX;
		double rayDirY = player.yDir + player.yPlane * cameraX;

		int mapX = int(player.xPos);
		int mapY = int(player.yPos);
		
		double sideDistX;
		double sideDistY;

		double deltaDistX = std::abs(1 / rayDirX);
		double deltaDistY = std::abs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if(rayDirX < 0){
			stepX = -1;
			sideDistX = (player.xPos - mapX) * deltaDistX;
		}else{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player.xPos) * deltaDistX;
		}

		if(rayDirY < 0){
			stepY = -1;
			sideDistY = (player.yPos - mapY) * deltaDistY;
		}else{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player.yPos) * deltaDistY;
		}

		while(hit == 0){
			if(sideDistX < sideDistY){
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}else{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			if(gameMap.Map[mapX][mapY] > 0) hit = 1;
		}

		if(side == 0) 	perpWallDist = (mapX - player.xPos + (1 - stepX) / 2) / rayDirX;
		else 		perpWallDist = (mapY - player.yPos + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(height / perpWallDist);

		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height)drawEnd = height - 1;

		if(side == 1)SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
		else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		
		playerControl();

		SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
	}


	SDL_RenderPresent(renderer);
}
