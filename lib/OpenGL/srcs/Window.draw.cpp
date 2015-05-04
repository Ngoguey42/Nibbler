// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.draw.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/30 08:24:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/04 15:53:03 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//#include <iostream>
#include "Window.class.hpp"
#include <cmath>

// * MEMBER FUNCTIONS / METHODS ********************************************* //

static void					rotateChunk(
	std::pair<int, int> const &prevDelta, std::pair<int, int> const &nextDelta)
{
	if ((prevDelta.first != 0) != (nextDelta.first != 0))
	{
		//angle
	}
	else if (prevDelta.first != 0)
	{
		//x changes
		if (prevDelta.first > 0)
		{
			glRotatef(-90.f, 0, 0, 1);
			glTranslatef(-CHUNK_SIZE, 0.f, 0.f);
		}
		else
		{
			glRotatef(90.f, 0, 0, 1);
			glTranslatef(0.f, -CHUNK_SIZE, 0.f);
			
		}
	}
	else
	{
		//ychanges
		if (prevDelta.second > 0)
			return ;
		else
		{
			glRotatef(180.f, 0, 0, 1);
			glTranslatef(0.f, -CHUNK_SIZE, 0.f);
			glTranslatef(-CHUNK_SIZE, 0.f, 0.f);
		}
	}
	return ;
}


void						Window::_putSnakeChunk(
	std::pair<int, int> selfPos,
	std::pair<int, int> prevPos, float entryAngle,
	std::pair<int, int> nextPos, float exitAngle,
	std::tuple<float, float, float> color1,
	std::tuple<float, float, float> color2) const
{
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

	rotateChunk(std::make_pair<int, int>(selfPos.first - prevPos.first,
										 selfPos.second - prevPos.second),
				std::make_pair<int, int>(selfPos.first - nextPos.first,
										 selfPos.second - nextPos.second));
	
	glBegin(GL_TRIANGLE_STRIP);

	glColor3f(1.f, 0.f, 1.f);
	// glColor3f(std::get<0>(color2), std::get<1>(color2), std::get<2>(color2));
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

void						Window::_putSnakeChunk(
	std::pair<int, int> selfPos,
	std::pair<int, int> prevPos,
	std::pair<int, int> nextPos,
	float phase,
	std::tuple<float, float, float> color1,
	std::tuple<float, float, float> color2) const
{
	std::pair<int, int> const prevDelta =
		std::make_pair<int, int>(selfPos.first - prevPos.first,
								 selfPos.second - prevPos.second);
	std::pair<int, int> const nextDelta =
		std::make_pair<int, int>(selfPos.first - nextPos.first,
								 selfPos.second - nextPos.second);
	std::pair<float, float> const	topLeft(
		_topLeftCell.first + _cellSize * selfPos.first,
		_topLeftCell.second + _cellSize * selfPos.second);
	float ratio = fmod(glfwGetTime(), 5.f) / 5.f; //debug
	(void)ratio;
	(void)color1;
	(void)color2;
	
	glLoadIdentity();
	glTranslatef(topLeft.first, topLeft.second, -0.0f);
	rotateChunk(prevDelta, nextDelta);
	
	// glRotatef(ratio * 360.f, 0, 1, 0);
	// glRotatef(0.f, 0, 1, 0);	

	float curphase = phase;

	float r = 0.f, g = 0.33f, b = .66f;
	float z = 20.f;
	float x, y = 0.f;

	if ((prevDelta.first != 0) != (nextDelta.first != 0))
	{
		
	}
	else
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i <= POINTS_PER_SIDE; i++)
		{
			x = (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV;
				
			r += 0.33f; g += 0.33f; b += 0.33f;
			glColor3f(fmod(r, 1.f), fmod(g, 1.f), fmod(b, 1.f));
			glVertex3f(x * CHUNK_SIZE, y, 0.f);
			glColor3f(.0f, 0.5f, 0.0f);
			glVertex3f((x + SNAKE_WIDTH_HALF) * CHUNK_SIZE, y, z);

			y += TRIANGLES_DISTANCE;
			curphase += PHASE_PER_TRIANGLE;
		}
		glEnd();
	
		glBegin(GL_TRIANGLE_STRIP);
		curphase = phase;	
		y = 0.f;
		for (int i = 0; i <= POINTS_PER_SIDE; i++)
		{
			x = (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV;
		
			glColor3f(.7f, 0.f, 0.0f);
			glVertex3f((x + SNAKE_WIDTH) * CHUNK_SIZE, y, 0.f);
			glColor3f(.0f, 0.5f, 0.0f);
			glVertex3f((x + SNAKE_WIDTH_HALF) * CHUNK_SIZE, y, z);
				
			y += TRIANGLES_DISTANCE;
			curphase += PHASE_PER_TRIANGLE;
		}	
		glEnd();
	}
	return ;
}
