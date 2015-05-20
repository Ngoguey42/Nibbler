/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLUI.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 19:14:38 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/20 19:44:05 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include "SDLUI.hpp"
#include "IBlock.hpp"

SDLUI::SDLUI(std::pair<int, int> gameSize)
	: _gameSize(gameSize)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error("Cannot init SDL");
	_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
	if (_window == NULL)
		throw std::runtime_error("Cannot open window");
}

SDLUI::~SDLUI(void)
{
	if (_window != NULL)
		SDL_DestroyWindow(_window);
	SDL_Quit();
}
