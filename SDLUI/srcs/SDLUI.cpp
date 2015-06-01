/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLUI.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 19:14:38 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/01 15:24:19 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <string>
#include "SDLUI.hpp"
#include "IBlock.hpp"
#include "IGame.hpp"
#include "ISnake.hpp"

SDLUI::SDLUI(std::pair<int, int> gameSize)
	: _gameSize(gameSize), _shouldClose(false)
{
}

SDLUI::~SDLUI(void)
{
	if (_window != NULL)
		SDL_DestroyWindow(_window);
	if (_font != NULL)
		TTF_CloseFont(_font);
	SDL_Quit();
	TTF_Quit();
}

void				SDLUI::init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
		throw std::runtime_error("Cannot init SDL");
	_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_gameSize.first * CHUNK_SIZE, _gameSize.second * CHUNK_SIZE + OFFSET_TOP, SDL_WINDOW_SHOWN);
	if (_window == NULL)
		throw std::runtime_error("Cannot open window");
	_surface = SDL_GetWindowSurface(_window);
	_font = TTF_OpenFont(FONT_LOCATION, FONT_SIZE);
	if (_font == NULL)
		throw std::runtime_error("Cannot open font");
	_events[SDLK_UP] = EVENT_UP;
	_events[SDLK_RIGHT] = EVENT_RIGHT;
	_events[SDLK_DOWN] = EVENT_DOWN;
	_events[SDLK_LEFT] = EVENT_LEFT;
	_events[SDLK_SPACE] = EVENT_SPACE;
	_events[SDLK_r] = EVENT_R;
	_events[SDLK_1] = EVENT_1;
	_events[SDLK_2] = EVENT_2;
	_events[SDLK_3] = EVENT_3;
	_events[SDLK_4] = EVENT_4;
	_events[SDLK_5] = EVENT_5;
	_events[SDLK_6] = EVENT_6;
	_events[SDLK_7] = EVENT_7;
}

EventType			SDLUI::getEvent(void)
{
	SDL_Event			e;

	if (!SDL_PollEvent(&e))
		return (EVENT_NOPE);
	if (e.type == SDL_QUIT)
		_shouldClose = true;
	else if (e.type == SDL_KEYDOWN)
	{
		auto it = _events.find(e.key.keysym.sym);
		if (it != _events.end())
			return (it->second);
		if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE)
			_shouldClose = true;
	}
	return (EVENT_NOPE);
}

void				SDLUI::draw(IGame const &game)
{
	_drawBackground();
	_drawBlocks(game.getBlocks());
	_drawSnake(game.getSnake());
	_drawGrid();
	_drawHeader(game);
	SDL_UpdateWindowSurface(_window);
}

void				SDLUI::_drawBackground(void)
{
	SDL_Rect			rect{0, 0, _gameSize.first * CHUNK_SIZE, OFFSET_TOP};

	SDL_FillRect(_surface, NULL, SDL_MapRGB(_surface->format, C_BACKGROUND));
	SDL_FillRect(_surface, &rect, SDL_MapRGB(_surface->format, 0, 0, 0));
}

void				SDLUI::_drawGrid(void)
{
	SDL_Rect			rect{0, OFFSET_TOP, 1, _gameSize.second * CHUNK_SIZE};
	Uint32				color = SDL_MapRGB(_surface->format, C_GRID);

	for (rect.x = _gameSize.first * CHUNK_SIZE; rect.x > 0; rect.x -= CHUNK_SIZE)
		SDL_FillRect(_surface, &rect, color);
	rect = {0, 0, _gameSize.first * CHUNK_SIZE, 1};
	for (rect.y = _gameSize.second * CHUNK_SIZE + OFFSET_TOP; rect.y > OFFSET_TOP; rect.y -= CHUNK_SIZE)
		SDL_FillRect(_surface, &rect, color);
}

void				SDLUI::_drawBlocks(std::list<IBlock*> const &blocks)
{
	SDL_Rect			rect{0, 0, CHUNK_SIZE, CHUNK_SIZE};
	Uint32				colors[IBlock::NOPE] = {
		SDL_MapRGB(_surface->format, C_BLOCK_GROW),
		SDL_MapRGB(_surface->format, C_BLOCK_WALL),
		SDL_MapRGB(_surface->format, C_BLOCK_WALL_S),
		SDL_MapRGB(_surface->format, C_BLOCK_BONUS)
	};

	for (IBlock const *b : blocks)
	{
		rect.x = b->getX() * CHUNK_SIZE;
		rect.y = b->getY() * CHUNK_SIZE + OFFSET_TOP;
		if (b->getType() >= 0 && b->getType() < IBlock::NOPE)
			SDL_FillRect(_surface, &rect, colors[b->getType()]);
	}
}

void				SDLUI::_drawSnake(ISnake const &snake)
{
	SDL_Rect			rect{0, 0, CHUNK_SIZE, CHUNK_SIZE};
	auto				color = SDL_MapRGB(_surface->format, C_SNAKE);

	for (auto &c : snake.getChunks())
	{
		rect.x = c.first * CHUNK_SIZE;
		rect.y = c.second * CHUNK_SIZE + OFFSET_TOP;
		SDL_FillRect(_surface, &rect, color);
	}
	if (snake.isDie())
	{
		auto head = snake.getChunks().begin();
		rect.x = head->first * CHUNK_SIZE;
		rect.y = head->second * CHUNK_SIZE + OFFSET_TOP;
		SDL_FillRect(_surface, &rect, SDL_MapRGB(_surface->format, C_SNAKE_DEAD));
	}
}

void				SDLUI::_drawHeader(IGame const &game)
{
	int					x = _gameSize.first * 2;
	int					y;

	y = CHUNK_SIZE / 2;
	_drawText(x, y, std::string("Score: ") += std::to_string(game.getScore()));
	y += CHUNK_SIZE;
	_drawText(x, y, std::string("Time: ") += std::to_string(game.getPlayTime()));
	y += CHUNK_SIZE;
	if (game.isPaused())
		_drawText(CHUNK_SIZE, CHUNK_SIZE * 3.5, std::string(
			game.getSnake().isDie() ? "GAME OVER"
				: "PAUSE"));
}

void				SDLUI::_drawText(int x, int y, std::string const &str)
{
	SDL_Surface			*surface;
	SDL_Rect			dst;

	surface = TTF_RenderText_Solid(_font, str.c_str(), {C_TEXT, 0});
	if (surface == NULL)
		return ;
	dst.x = x;
	dst.y = y;
	dst.w = surface->w;
	dst.h = surface->h;
	SDL_BlitSurface(surface, NULL, _surface, &dst);
	SDL_FreeSurface(surface);
}

bool				SDLUI::windowShouldClose(void) const
{
	return (_shouldClose);
}
