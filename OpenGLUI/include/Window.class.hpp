/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 10:20:38 by ngoguey           #+#    #+#             */
//   Updated: 2015/05/19 15:14:04 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_CLASS_HPP
# define WINDOW_CLASS_HPP

# include <utility>
# include <iostream>
# include <stdexcept>
# include <queue>
# include <tuple>
# include <deque>

# include <GLFW/glfw3.h>

# include "nibbler.h"
# include "OpenGLLib.h"
# include "IUI.hpp"
# include "AngledSnakePoints.class.hpp"

class Window : public IUI
{
	Window() = delete;
	Window(Window const &src) = delete;
	Window						&operator=(Window const &rhs) = delete;
public:
	static std::queue<EventType>				pendingEvents;

	Window(std::pair<int, int> gridSize);
	virtual ~Window();

	EventType					getEvent(void);

	void						draw(IGame const &game);
	bool						windowShouldClose(void) const;
	
protected:
private:

	void						_put_grid(void) const;
	void						_put_lol(void) const;
	void						_put_block(std::pair<int, int> const &pos,
										   std::tuple<float, float, float> c) const;
	void						_put_head(
		std::pair<int, int> const &selfPos,
		std::pair<int, int> const &prevPos,
		float phase, float ratio) const;
	void						_putSnakeChunk(
		std::pair<int, int> const &selfPos,
		std::pair<int, int> const &prevPos,
		std::pair<int, int> const &nextPos,
		float phase, bool narrowFront = false
		) const;
	
	GLFWwindow						*_win;
	std::pair<int, int> const		_tmpGridSize;		// Grid size (Ctor)
	
	std::pair<int, int> const		_winSize;			// Window size
	std::pair<float, float> const	_topLeftCell;	// Top left cell coords

	float							_lastTime;
	float							_phase;
	float							_deathTime;

#define TEMPLATE_SIZE(S) S[0], S[1], S[2], S[3], S[4], S[5]
	static constexpr ftce::Array<size_t, 6>    sinSize
		{AngledSnakePoints::calcPointsArraySize(true)};
	static constexpr ftce::Array<CornerPoints<TEMPLATE_SIZE(sinSize)>, NUM_PRECALC_POINTS>
	sinPoints{AngledSnakePoints::buildPointsArray<TEMPLATE_SIZE(sinSize)>(true)};
	static constexpr ftce::Array<size_t, 6>    dexSize
		{AngledSnakePoints::calcPointsArraySize(false)};
	static constexpr ftce::Array<CornerPoints<TEMPLATE_SIZE(dexSize)>, NUM_PRECALC_POINTS>
	dexPoints{AngledSnakePoints::buildPointsArray<TEMPLATE_SIZE(dexSize)>(false)};

	
#undef TEMPLATE_SIZE
	// std::array<AngledSnakePoints, NUM_PRECALC_POINTS>	sinPoints;
	
};
//std::ostream					&operator<<(std::ostream &o, Window const &rhs);

#endif // ************************************************** WINDOW_CLASS_HPP //
