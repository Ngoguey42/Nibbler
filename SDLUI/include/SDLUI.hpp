/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLUI.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 19:14:35 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/29 16:42:01 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDLUI_HPP
# define SDLUI_HPP

# include <utility>
# include <map>
# include <list>
# include <SDL2/SDL.h>
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

	bool					_shouldClose;

	virtual void			_drawBackground(void);
	virtual void			_drawGrid(void);
	virtual void			_drawBlocks(std::list<IBlock*> const &blocks);
	virtual void			_drawSnake(ISnake const &snake);
	virtual void			_drawHeader(IGame const &game);

private:
	SDLUI(SDLUI const &src);
	SDLUI					&operator=(SDLUI const &rhs);
};

#endif
