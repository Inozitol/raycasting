#include "CApp.h"
#include <cmath>
#include <iostream>

void CApp::OnRender(){

	width=640;
	height=480;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	Uint32 buffer[height][width];
	std::vector<Uint32> texture[8];
	for(int i=0; i<8; i++) texture[i].resize(tx_width * tx_height);

	//Generating textures
	for(int x=0; x<tx_width; x++){
		for(int y=0; y<tx_height; y++){
			int xorcolor = (x * 256 / tx_width) ^ (y * 256 / tx_height);
			int ycolor = y * 256 / tx_height;
			int xycolor = y * 128 / tx_height + x * 128 / tx_width;
			
			texture[0][tx_width * y + x] = 65536 * 254 * (x != y && x != tx_width - y);
			texture[1][tx_width * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			texture[2][tx_width * y + x] = 256 * xycolor + 65536 * xycolor;
			texture[3][tx_width * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			texture[4][tx_width * y + x] = 256 * xorcolor;
			texture[5][tx_width * y + x] = 65536 * 192 * (x % 16 && y % 16);
			texture[6][tx_width * y + x] = 65536 * ycolor;
			texture[7][tx_width * y + x] = 128 + 256 * 128 + 65536 * 128;
		}
	}

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

		int tex_num = gameMap.Map[mapX][mapY] - 1;

		double wallX;
		if(side == 0)  	wallX = player.yPos + perpWallDist * rayDirY;
		else		wallX = player.xPos + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int xTex = int(wallX * double(tx_width));
		if(side == 0 && rayDirX > 0) xTex = tx_width - xTex - 1;
		if(side == 1 && rayDirY < 0) xTex = tx_width - xTex - 1;

		for(int y = drawStart; y<drawEnd; y++){
			int d = y * 256 - height * 128 + lineHeight * 128;
			int yTex = ((d * tx_height) / lineHeight) / 256;
			Uint32 color = texture[tex_num][tx_height * yTex + xTex];
			buffer[y][x] = color;
		}
		


	}
	playerControl();

	SDL_UpdateTexture(scr_texture, NULL, buffer, 640 * sizeof(Uint32) ); 

	for(int x=0; x<width; x++) 
		for(int y=0; y<height; y++)
			buffer[y][x]=0;

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scr_texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
