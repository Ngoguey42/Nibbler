/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SfmlUI.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:49:37 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/19 15:51:40 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFMLUI_HPP
# define SFMLUI_HPP

# include <utility>
# include <SFML/Graphics.hpp>
# include "nibbler.h"
# include "IBlock.hpp"
# include "IUI.hpp"

# define FONT_LOCATION		"SfmlUI/misc/font.ttf"
# define SPRITES_LOCATION	"SfmlUI/misc/sprites.png"

# define SPRITES_SIZE		64

# define MAX_CHUNK_SIZE		64

# define GRID_COLOR			150, 255, 0

class	SfmlUI : public sf::RenderWindow, public IUI
{
public:
	SfmlUI(std::pair<int, int> gameSize);
	virtual ~SfmlUI(void);

	virtual EventType			getEvent(void);

	virtual void				draw(IGame const &game);

	virtual bool				windowShouldClose(void) const;

protected:

	std::pair<int, int>			_gameSize;
	int							_chunkSize;

	sf::Texture					_sprites;
	sf::Sprite					_snakeHeadSprite;
	sf::Sprite					_snakeBodySprite;
	sf::Sprite					_snakeCornerSprite;
	sf::Sprite					_snakeTailSprite;

	sf::Font					_font;

	std::map<sf::Keyboard::Key, EventType>	_events;

	sf::VertexArray				_line;

	void						_drawGrid(void);

	void						_drawWallBlock(int x, int y);
	void						_drawGrowBlock(int x, int y);
	void						_drawBonusBlock(int x, int y);

	void						_drawSnake(ISnake const &snake);

	void						_drawOverlay(std::string const &text);
	void						_drawText(float x, float y, std::string const &text, unsigned int size);
	void						_drawLine(int x, int y, int w, int h);

	static sf::VideoMode		_getWindowSize(std::pair<int, int> gameSize, int &chunkSize);

private:
	SfmlUI(void);
	SfmlUI(SfmlUI const &src);
	SfmlUI			&operator=(SfmlUI const &rhs);
};

#endif
