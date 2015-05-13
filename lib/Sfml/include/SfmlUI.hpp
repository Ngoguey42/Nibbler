/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SfmlUI.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:49:37 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/13 13:27:06 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFMLUI_HPP
# define SFMLUI_HPP

# include <utility>
# include <SFML/Graphics.hpp>
# include "nibbler.h"
# include "IBlock.hpp"
# include "IUI.hpp"

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

	std::map<int, EventType>	_events;

	sf::VertexArray				_line;

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
