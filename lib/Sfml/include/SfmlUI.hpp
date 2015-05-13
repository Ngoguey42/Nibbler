/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SfmlUI.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:49:37 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/13 14:20:51 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFMLUI_HPP
# define SFMLUI_HPP

# include <utility>
# include <SFML/Graphics.hpp>
# include "nibbler.h"
# include "IBlock.hpp"
# include "IUI.hpp"

# define FONT_LOCATION		"lib/Sfml/misc/font.ttf"

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

	sf::Font					_font;

	std::map<int, EventType>	_events;

	sf::VertexArray				_line;

	void						_drawText(float x, float y, std::string const &text, unsigned int size);
	void						_drawGrid(void);
	void						_drawWallBlock(int x, int y);
	void						_drawGrowBlock(int x, int y);
	void						_drawSnakeChunk(int x, int y);
	void						_drawLine(int x, int y, int w, int h);

	static sf::VideoMode		_getWindowSize(std::pair<int, int> gameSize, int &chunkSize);

private:
	SfmlUI(void);
	SfmlUI(SfmlUI const &src);
	SfmlUI			&operator=(SfmlUI const &rhs);
};

#endif
