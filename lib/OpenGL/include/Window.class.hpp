/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 10:20:38 by ngoguey           #+#    #+#             */
//   Updated: 2015/05/11 09:20:12 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_CLASS_HPP
# define WINDOW_CLASS_HPP

# include <utility>
# include <iostream>
# include <stdexcept>
# include <deque>

# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include "nibbler.h"
# include "OpenGLLib.h"
# include "IUI.hpp"
# include "AngledSnakePoints.class.hpp"

class Window : public IUI
{
public:
	Window(std::pair<int, int> gridSize, float cellSize);
	virtual ~Window();

	EventType					getEvent(void);

	void						draw(IGame const &game);
	bool						windowShouldClose(void) const;
	
protected:
private:
	Window();
	Window(Window const &src);
	Window						&operator=(Window const &rhs);

	void						_put_grid(void) const;
	void						_put_lol(void) const;
	void                        _put_block(std::pair<int, int> const &pos)
		const;
	void						_putSnakeChunk(
		std::pair<int, int> selfPos,
		std::pair<int, int> prevPos, float entryAngle,
		std::pair<int, int> nextPos, float exitAngle,
		std::tuple<float, float, float> color1 = std::make_tuple(0.f, 1.f, 0.f),
		std::tuple<float, float, float> color2 = std::make_tuple(0.f, 0.f, 1.f)
		) const;
	void						_putSnakeChunk(
		std::pair<int, int> selfPos,
		std::pair<int, int> prevPos,
		std::pair<int, int> nextPos,
		float phase,
		std::tuple<float, float, float> color1 = std::make_tuple(0.f, 1.f, 0.f),
		std::tuple<float, float, float> color2 = std::make_tuple(0.f, 0.f, 1.f)
		) const;
	
	GLFWwindow					*_win;
	std::pair<int, int> const	_tmpGridSize;		// Grid size (Ctor)
	float const					_cellSize;			// Cell size (Ctor)
	
	std::pair<int, int> const	_winSize;			// Window size
	std::pair<float, float> const	_topLeftCell;	// Top left cell coords

	float						_phase;

	std::array<AngledSnakePoints, NUM_PRECALC_POINTS>	sinPoints;
	
};
//std::ostream					&operator<<(std::ostream &o, Window const &rhs);

#endif // ************************************************** WINDOW_CLASS_HPP //
