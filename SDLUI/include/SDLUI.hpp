/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLUI.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 19:14:35 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/01 13:32:53 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDLUI_HPP
# define SDLUI_HPP

# include <utility>
# include <map>
# include <list>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include "nibbler.h"
# include "IUI.hpp"

# define CHUNK_SIZE			16
# define OFFSET_TOP			48

# define C_GRID				0, 0, 0
# define C_BACKGROUND		24, 54, 32
# define C_SNAKE			0, 0, 0
# define C_SNAKE_DEAD		64, 0, 0
# define C_BLOCK_GROW		192, 0, 0
# define C_BLOCK_WALL		0, 0, 0
# define C_BLOCK_WALL_S		0, 0, 0
# define C_BLOCK_BONUS		0, 192, 192
# define C_TEXT				230, 230, 230

# define FONT_LOCATION		"SDLUI/misc/font.ttf"
# define FONT_SIZE			CHUNK_SIZE

class	SDLUI : public IUI
{
public:
	SDLUI(std::pair<int, int> gameSize);
	virtual ~SDLUI(void);

	virtual void			init(void);

	virtual EventType		getEvent(void);

	virtual void			draw(IGame const &game);

	virtual bool			windowShouldClose(void) const;

protected:

	std::pair<int, int>		_gameSize;

	std::map<SDL_Keycode, EventType>	_events;

	SDL_Window				*_window;
	SDL_Surface				*_surface;
	TTF_Font				*_font;

	bool					_shouldClose;

	void					_drawBackground(void);
	void					_drawGrid(void);
	void					_drawBlocks(std::list<IBlock*> const &blocks);
	void					_drawSnake(ISnake const &snake);
	void					_drawHeader(IGame const &game);

	void					_drawText(int x, int y, std::string const &str);

private:
	SDLUI(SDLUI const &src);
	SDLUI					&operator=(SDLUI const &rhs);
};

#endif
