// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.draw.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/30 08:24:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/04/30 13:59:45 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//#include <iostream>
#include "Window.class.hpp"
#include <cmath>

// * MEMBER FUNCTIONS / METHODS ********************************************* //

void					putSquarePoints(
	std::pair<float, float> const &size, Window::e_alignement align,
	float point2Z, float point3Z)
{
	glBegin(GL_TRIANGLE_STRIP);
	// glBegin(GL_QUADS);
	switch(align)
	{
	case Window::e_alignement::left:
		glColor3f(0.f, 0.0f, 0.9f);
		glVertex3f(0.f, -size.second / 2.f, 0.f);
		glColor3f(0.5f, 0.57f, 0.f);
		glVertex3f(0.f, size.second / 2.f, 0.f);
//		glColor3f(0.5f, 0.57f, 0.f);
		glVertex3f(size.first, -size.second / 2.f, point2Z);
		glColor3f(0.f, 0.0f, 0.9f);
		glVertex3f(size.first, size.second / 2.f, point3Z);
		
		glVertex3f(size.first, -size.second / 2.f, point2Z);
		break;
	case Window::e_alignement::right:
		break;
	case Window::e_alignement::top:
		break;
	case Window::e_alignement::bottom:
		break;		
	}
	glEnd();
	return ;
}

void						Window::_putSnakeChunk(
	std::pair<int, int> selfPos,
	std::pair<int, int> prevPos, float entryAngle,
	std::pair<int, int> nextPos, float exitAngle) const
{
	std::pair<int, int> const		deltaPrev(selfPos.first - prevPos.first,
											  selfPos.second - prevPos.second);
	std::pair<int, int> const		deltaNext(selfPos.first - nextPos.first,
											  selfPos.second - nextPos.second);
	std::pair<float, float> const	topLeft(
		_topLeftCell.first + _cellSize * selfPos.first,
		_topLeftCell.second + _cellSize * selfPos.second);
	
	(void)selfPos;
	(void)prevPos;
	(void)entryAngle;
	(void)nextPos;
	(void)exitAngle;

	glLoadIdentity();
	glColor3f(0.5f, 0.57f, 0.f);
	
	glTranslatef(
		topLeft.first,
		topLeft.second + _cellSize / 2.f, -0.0f);

	
	float ratio = fmod(glfwGetTime(), 5.f) / 5.f;
	(void)ratio;
	// glRotatef(, 0, 1, 0);	
	// glRotatef(ratio * 360.f, 0, 1, 0);	


	glBegin(GL_TRIANGLE_STRIP);
	{
		glColor3f(0.9f, 0.0f, 0.0f);
		glVertex3f(-_cellSize / 2,	-_cellSize / 2, 0.f);
		glColor3f(0.0f, 0.9f, 0.0f);
		glVertex3f(-_cellSize / 2,	_cellSize / 2, 0.f);
		glColor3f(0.0f, 0.0f, 0.9f);
		glVertex3f(-5.f,			-_cellSize / 2 , 0.f);
		glColor3f(0.9f, 0.0f, 0.0f);
		glVertex3f(-5.f,			_cellSize / 2, 0.f);
		glColor3f(0.0f, 0.9f, 0.0f);
		glVertex3f(5.f,				-_cellSize / 2 , 0.f);
		glColor3f(0.0f, 0.0f, 0.9f);
		glVertex3f(5.f,				_cellSize / 2 , 0.f);
		glColor3f(0.9f, 0.0f, 0.0f);
		glVertex3f(_cellSize / 2,	-_cellSize / 2, 0.f);
		glColor3f(0.0f, 0.9f, 0.0f);
		glVertex3f(_cellSize / 2,	_cellSize / 2, 0.f);
		
		// glVertex3f(size.first, -size.second / 2.f, point2Z);
	}
	glEnd();

	
//	putSquarePoints(std::make_pair(_cellSize / 3, _cellSize),
//					Window::e_alignement::left, 25.f, 20.f);
	glEnd();

	return ; 
	if ((deltaPrev.first != 0) != (deltaNext.first != 0))
	{
		//angle
		return ;
	}
	else if (deltaPrev.first != 0)
	{
		//
		return ;
	}
	
	
	
	return ;
}
