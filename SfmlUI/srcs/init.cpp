/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:48:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/20 18:35:02 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include "nibbler.h"
#include "SfmlUI.hpp"

extern "C"
{

static sf::Texture		sprites;
static bool				sprites_loaded = false;
static sf::Font			font;
static bool				font_loaded = false;

IUI				*INIT_FUNCTION(std::pair<int, int> gameSize)
{
	if (!sprites_loaded)
	{
		if (!sprites.loadFromFile(SPRITES_LOCATION))
			throw std::runtime_error("Cannot load sprites");
		sprites_loaded = true;
	}
	if (!font_loaded)
	{
		if (!font.loadFromFile(FONT_LOCATION))
			throw std::runtime_error("Cannot load font");
		font_loaded = true;
	}
	return (new SfmlUI(gameSize, sprites, font));
}

}
