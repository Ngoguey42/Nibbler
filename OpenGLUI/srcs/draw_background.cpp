// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   draw_background.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/29 15:44:16 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/29 17:45:09 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "OpenGLLib.h"
#include "OpenGLUI.class.hpp"
#include <cmath>
#include <cfenv>

// * C-STYLE FUNCTIONS ****************************************************** //
// * MEMBER FUNCTIONS / METHODS ********************************************* //

OpenGLUI::bg_points						OpenGLUI::_buildBgDatas(void) const
{
	std::fesetround(FE_UPWARD);
	typedef ftce::VtsColor<1u, float, 2u>			bgPointTmp;
	typedef std::vector<std::vector<bgPointTmp>>	bgPointsTmp;
			// Calculating vectors sizes.
	bg_points						ret;
	std::pair<int, int> const		numPoints(
		std::lrint(static_cast<float>(_winSize.first +
									  BG_POINTS_RAND_RANGE) /
				   BG_POINTS_PADDINGF) + 1,
		std::lrint(static_cast<float>(_winSize.second +
									  BG_POINTS_RAND_RANGE) /
				   BG_POINTS_PADDINGF) + 1);
			// Calculation first point's data.
	std::pair<float, float> const	topLeftPos(
		static_cast<float>(
			(numPoints.first - 1) * BG_POINTS_PADDING - _winSize.first) / -2.f,
		static_cast<float>(
			(numPoints.second - 1) * BG_POINTS_PADDING - _winSize.second) / -2.f);
	ftce::Vertex<float, 2u>			curPos(topLeftPos);		
	bgPointsTmp						bgPoints(numPoints.second);

			// Creating points in temp arrays
	for (int y = 0; y < numPoints.second; y++)
	{		// Foreach lines
		bgPoints[y].reserve(numPoints.first);
		curPos.x = topLeftPos.first;		
		for (int x = 0; x < numPoints.first; x++)
		{	// Foreach columns
			// Create a point with semi-random color/position.
			bgPointTmp	tmp;

			tmp.v[0] = ftce::Vertex<float, 2u>(
				curPos.x + BG_POINTS_RAND_RANGEHALFF -
				BG_POINTS_RAND_RANGEF * randf(),
				curPos.y + BG_POINTS_RAND_RANGEHALFF -
				BG_POINTS_RAND_RANGEF * randf());
			if (std::rand() % 100 < BG_PERCENT_GREY)
				tmp.c = BG_MAIN_GREY;
			else
				tmp.c = BG_PINK_PLUS_HALFDELTA - BG_DELTA_PINK * randf();
			bgPoints[y].push_back(std::move(tmp));
			curPos.x += BG_POINTS_PADDINGF;
		}
		curPos.y += BG_POINTS_PADDINGF;
	}
			// Putting together points 3 by 3
	ret.reserve((numPoints.first - 1) + (numPoints.second - 1) * 2);
	for (int y = 1; y < numPoints.second; y++)
	{		// Foreach lines
		for (int x = 1; x < numPoints.first; x++)
		{	// Foreach columns, save the two topLeft triangles.
			// Using ftce::VtsColor's variadic constructor.
			ret.emplace_back(bgPoints[y - 1][x - 1].c / 3.f +
							 bgPoints[y - 1][x    ].c / 3.f +
							 bgPoints[y    ][x - 1].c / 3.f,
							 bgPoints[y - 1][x - 1].v[0],
							 bgPoints[y - 1][x    ].v[0],
							 bgPoints[y    ][x - 1].v[0]);
			ret.emplace_back(bgPoints[y - 1][x    ].c / 3.f +
							 bgPoints[y    ][x    ].c / 3.f +
							 bgPoints[y    ][x - 1].c / 3.f,
							 bgPoints[y - 1][x    ].v[0],
							 bgPoints[y    ][x    ].v[0],
							 bgPoints[y    ][x - 1].v[0]);
		}
	}
	return (ret);
}

void								OpenGLUI::_putBackground(void) const
{
	for (auto const &it : this->_bgDatas)
	{
		glBegin(GL_TRIANGLE_STRIP);
		glColor3ub(it.c.r, it.c.g, it.c.b);
		glVertex3f(it.v[0].x, it.v[0].y, 0.f);
		glVertex3f(it.v[1].x, it.v[1].y, 0.f);
		glVertex3f(it.v[2].x, it.v[2].y, 0.f);
		glEnd();
	}
	return ;
}
