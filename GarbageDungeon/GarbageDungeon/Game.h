#pragma once
#include <stdio.h>
#include <iostream>
#include<string>
#include<sstream>
#include"Sprite.h"
#include "SDL.h"
using namespace std;

class Game {
protected:
	bool done = false;
	string bgfile = "Forest0.bmp";
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	SDL_Window* window = NULL;
	SDL_Texture* bg = NULL;
	SDL_Surface* surface = NULL;
	SDL_Renderer* renderer = NULL;
	Sprite *s;
	SDL_Event e;

public:
	void init() { SDL_Init(SDL_INIT_VIDEO); }

	void createWindow(SDL_Window* &window, string winName) {
		window = SDL_CreateWindow(winName.c_str(), SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	}

	void setBG(SDL_Window* window)
	{
		surface = SDL_LoadBMP("Forest0.bmp");
		renderer = SDL_CreateRenderer(window, -1, 0);
		bg = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bg, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	void run()
	{
		createWindow(this->window, "Garbage Dungeon");
		setBG(this->window);
		Sprite carl = carl.createSprite(renderer, "duderight.bmp", 75, 80, 0, 275);
		while (!done)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					done = true;
				}
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, bg, NULL, NULL);
			SDL_RenderCopy(renderer, carl.getSpriteTexture(), &carl.getsrc(), &carl.getdest());
			eventHandler(e, carl);
			SDL_RenderPresent(renderer);
		}
	}

	SDL_Window *getWindow() { return this->window; }
	SDL_Texture *getBackground() { return this->bg; }
	SDL_Surface *getSurface() { return this->surface; }
	SDL_Renderer *getRenderer() { return this->renderer; }

	void eventHandler(SDL_Event e, Sprite &sprite) {
		if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
		{
			if (!sprite.isfacingright()) sprite.switchDirection(sprite, renderer);
			sprite.move(renderer, bg, sprite, e);
		}
		if (currentKeyStates[SDL_SCANCODE_ESCAPE])
			done = true;
		if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
		{
			if (sprite.isfacingright()) sprite.switchDirection(sprite, renderer);
			sprite.move(renderer, bg, sprite, e);
		}
		if (currentKeyStates[SDL_SCANCODE_SPACE] || currentKeyStates[SDL_SCANCODE_UP])
		{
			sprite.jump(renderer, bg, sprite);
			//jump resets dest after each command
			sprite.move(renderer, bg, sprite, e);
		}
	}

	void endGame(SDL_Window* window)
	{
		SDL_Delay(100);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};
