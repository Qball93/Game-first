#include "Game.h"
#include <iostream>

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	std::cout << "wtf im creating here ";
	//attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL INIT SUCCESS\n";
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);

		int flags = 0;
		if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }

		if (m_pWindow != 0)
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // renderer init succes
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 36, 24, 24, 255);

			}
			else
			{
				std::cout << "renderer creation failed\n";
				return false;

			}

			//return true;
		}
		else
		{
			std::cout << "window creation failed\n";
			return false;
		}

		std::cout << "Init success\n";
		m_bRunning = true; // everything started successfully start the main loop

		SDL_Surface* pTempSurface = SDL_LoadBMP("assets/animate.bmp");
		m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
		SDL_FreeSurface(pTempSurface);

		//SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

		m_destinationRectangle.x = m_sourceRectangle.x = 0; 
		m_destinationRectangle.y = m_sourceRectangle.y = 0; 
		m_destinationRectangle.w = m_sourceRectangle.w = 128;
		m_destinationRectangle.h = m_sourceRectangle.h = 82;
			
		//SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);

		
	}
}


void Game::update() 
{ 
	m_sourceRectangle.x = 128 * int(((SDL_GetTicks() / 100) % 6));
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); //clear the render to draw color;
	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
	SDL_RenderPresent(m_pRenderer);
	
}


void Game::clean()
{
	std::cout << "Cleaning game\n";

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				m_bRunning = false;
				break;
			}
			default :
				break;
		}
	}
}