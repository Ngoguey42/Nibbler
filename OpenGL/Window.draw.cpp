// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.draw.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/30 08:24:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/01 11:29:31 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//#include <iostream>
#include "Window.class.hpp"
#include <cmath>

// * MEMBER FUNCTIONS / METHODS ********************************************* //

void						Window::_putSnakeChunk(
	std::pair<int, int> selfPos,
	std::pair<int, int> prevPos, float entryAngle,
	std::pair<int, int> nextPos, float exitAngle,
	std::tuple<float, float, float> color1,
	std::tuple<float, float, float> color2) const
{
/*	std::pair<int, int> const		deltaPrev(selfPos.first - prevPos.first,
	selfPos.second - prevPos.second);
	std::pair<int, int> const		deltaNext(selfPos.first - nextPos.first,
	selfPos.second - nextPos.second);
*/
	std::pair<float, float> const	topLeft(
		_topLeftCell.first + _cellSize * selfPos.first,
		_topLeftCell.second + _cellSize * selfPos.second);
	entryAngle = DEG_TO_RAD(entryAngle);
	exitAngle = DEG_TO_RAD(exitAngle);
	float const					dxt1 = _cellSize/((1 / cosf(entryAngle)) + 2);
	float const					dzt1 = tanf(entryAngle) * dxt1;
	float const					dxt2 = _cellSize/((1 / cosf(exitAngle)) + 2);
	float const					dzt2 = tanf(exitAngle) * dxt2;

	glLoadIdentity();
	glTranslatef(
		topLeft.first,
		topLeft.second, -0.0f);

	float ratio = fmod(glfwGetTime(), 15.f) / 15.f; //debug
	(void)ratio;
	// glRotatef(ratio * 360.f, 0, 1, 0);
	// glRotatef(90.f, 0, 1, 0);	

	
	glBegin(GL_TRIANGLE_STRIP);

	// glColor3f(1.f, 0.f, 1.f);
	glColor3f(std::get<0>(color2), std::get<1>(color2), std::get<2>(color2));
	glVertex3f(0.f,	0.f, 0.f);
	glColor3f(std::get<0>(color1), std::get<1>(color1), std::get<2>(color1));
	glVertex3f(0.f,	_cellSize, 0.f);

	glColor3f(std::get<0>(color1), std::get<1>(color1), std::get<2>(color1));
	glVertex3f(dxt1, 0.f, dzt1);
	glColor3f(std::get<0>(color2), std::get<1>(color2), std::get<2>(color2));
	glVertex3f(dxt2, _cellSize, dzt2);

	glColor3f(std::get<0>(color2), std::get<1>(color2), std::get<2>(color2));
	glVertex3f(_cellSize - dxt1, 0.f, dzt1);
	glColor3f(std::get<0>(color1), std::get<1>(color1), std::get<2>(color1));
	glVertex3f(_cellSize - dxt2, _cellSize , dzt2);

	glColor3f(std::get<0>(color1), std::get<1>(color1), std::get<2>(color1));
	glVertex3f(_cellSize, 0.f, 0.f);
	glColor3f(std::get<0>(color2), std::get<1>(color2), std::get<2>(color2));
	glVertex3f(_cellSize, _cellSize, 0.f);
	glEnd();
	return ;
	(void)selfPos;
	(void)prevPos;
	(void)entryAngle;
	(void)nextPos;
	(void)exitAngle;
	(void)color1;
	(void)color2;
}
