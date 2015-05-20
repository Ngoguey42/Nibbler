/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:48:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/20 17:02:16 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include "nibbler.h"
#include "SfmlUI.hpp"

extern "C"
{

IUI				*INIT_FUNCTION(std::pair<int, int> gameSize)
{
	static sf::Texture	*sprites = NULL;
	static sf::Font		*font = NULL;

	if (sprites == NULL)
	{
		sprites = new sf::Texture();
		if (!sprites->loadFromFile(SPRITES_LOCATION))
		{
			delete sprites;
			throw std::runtime_error("Cannot load sprites");
		}
		sprites->setSmooth(true);
	}
	if (font == NULL)
	{
		font = new sf::Font();
		if (!font->loadFromFile(FONT_LOCATION))
		{
			delete font;
			throw std::runtime_error("Cannot load font");
		}
	}
	return (new SfmlUI(gameSize, *sprites, *font));
}

}
