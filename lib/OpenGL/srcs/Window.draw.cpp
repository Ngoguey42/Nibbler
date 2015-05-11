// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.draw.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/30 08:24:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/11 15:18:15 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//#include <iostream>
#include "Window.class.hpp"
#include <cmath>

// * MEMBER FUNCTIONS / METHODS ********************************************* //

static void					rotateChunk(
	std::pair<int, int> const &prevDelta, std::pair<int, int> const &nextDelta)
{
	(void)nextDelta;
	if (prevDelta.first != 0)
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
		std::make_pair<int, int>(nextPos.first - selfPos.first,
								 nextPos.second - selfPos.second);
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

	// float r, g, b;
	float r = 0.f, g = 0.33f, b = .66f;
	// #define TRUC 0.2f
	// float colorratio = std::fmod(phase, TRUC) / TRUC;


	// if (colorratio < 0.33f)
	// 	r = 0.f, g = 0.33f, b = .66f;
	// else if (colorratio > 0.33f)
	// 	r = 0.33f, g = 0.66f, b = .0f;
	// else
	// 	r = 0.66f, g = 0.00f, b = .33f;
		
	float z = 20.f;
	float x, y = 0.f;

	if ((prevDelta.first != 0) != (nextDelta.first != 0))
	{
		// //std::cout << prevDelta.second + prevDelta.first + nextDelta.first + nextDelta.second << std::endl;

		//std::cout << prevDelta.first << "/" << prevDelta.second << " " <<
//			nextDelta.first << "/" << nextDelta.second << std::endl;

		
		if ((prevDelta.second > 0 && nextDelta.first > 0) ||
			(prevDelta.second < 0 && nextDelta.first < 0) ||
			(prevDelta.first > 0 && nextDelta.second < 0) ||
			(prevDelta.first < 0 && nextDelta.second > 0)) //sinistro
		{
			auto const	&points = this->sinPoints[
				static_cast<int>(std::round(phase * NUM_PRECALC_POINTSF - 0.5f))];
			size_t		i = 0;
			

			/*std::cout << "[" <<
				static_cast<int>(std::round(phase * NUM_PRECALC_POINTSF - 0.5f)) <<
				"] "  << 
				"MidMaxIn(" << points.middleBranchInLastIndex << ")" <<
				"LeftMaxIn(" << points.leftBranchInLastIndex << ")" <<
				"MidMaxOut(" << points.middleBranchOutLastIndex << ")" <<
				"LeftMaxOut(" << points.leftBranchOutLastIndex << ") ";
			*/
			//PART1

			// STRIP 1
			if (points.leftBranchInLastIndex > 0)
			{
				glBegin(GL_TRIANGLE_STRIP);
				// glColor3f(.0f, 0.5f, 0.0f);

				glColor3f(.0f, 0.5f, 0.0f);
				glVertex3f(points.middleBranchInPoints[0].first,
						   points.middleBranchInPoints[0].second, z);

				while(i < points.leftBranchInLastIndex)
				{					
					glColor3f(.7f, 0.f, 0.0f);
					glVertex3f(points.leftBranchInPoints[i].first,
							   points.leftBranchInPoints[i].second, 0.f);
					i++;
					glColor3f(.0f, 0.5f, 0.0f);
					glVertex3f(points.middleBranchInPoints[i].first,
							   points.middleBranchInPoints[i].second, z);
				}
				glColor3f(.7f, 0.f, 0.0f);
				glVertex3f(points.leftBranchIntersection.first,
						   points.leftBranchIntersection.second, 0.f);
				glEnd();
			}
			// FAN
			glBegin(GL_TRIANGLE_FAN);
			// glColor3f(.0f, 0.f, 1.f);
			glColor3f(.7f, 0.f, 0.0f);
			glVertex3f(points.leftBranchIntersection.first,
					   points.leftBranchIntersection.second, 0.f);
			//std::cout << "[left]";
			//std::cout << "in[";
			glColor3f(.0f, 0.5f, 0.0f);
			for (size_t j = i; j < points.middleBranchInLastIndex; j++)
			{
				//std::cout << j << ",";
				
				glVertex3f(points.middleBranchInPoints[j].first,
						   points.middleBranchInPoints[j].second, z);
			}
			//std::cout << "][mid]";
			
			glVertex3f(points.middleBranchIntersection.first,
					   points.middleBranchIntersection.second, 0.f);
			// glColor3f(1.f, 0.f, 0.f);
			i = points.leftBranchOutLastIndex;
			//std::cout << "out[";
			
			for (int j = points.middleBranchOutLastIndex - 1;
				 j >= static_cast<int>(i); j--)
			{
				//std::cout << j << ",";
				glVertex3f(points.middleBranchOutPoints[j].first,
						   points.middleBranchOutPoints[j].second, z);
			}
			
			//std::cout << "]";
			//std::cout << "   ";
			
			glEnd();
			// STRIP2
			if (points.leftBranchOutLastIndex > 0)
			{
				glBegin(GL_TRIANGLE_STRIP);
				// glColor3f(0.f, 0.5f, 0.0f);
				//std::cout << "[left]";
				glColor3f(.7f, 0.f, 0.0f);
				glVertex3f(points.leftBranchIntersection.first,
						   points.leftBranchIntersection.second, 0.f);
				//std::cout << "mid/left[";
				for (i = points.leftBranchOutLastIndex;;i--)
				{
					//std::cout << i << ", ";
					
					glColor3f(.0f, 0.5f, 0.0f);
					glVertex3f(points.middleBranchOutPoints[i].first,
							   points.middleBranchOutPoints[i].second, z);
					glColor3f(.7f, 0.f, 0.0f);
					glVertex3f(points.leftBranchOutPoints[i].first,
							   points.leftBranchOutPoints[i].second, 0.f);
					if (i == 0)
						break ;
				}
				//std::cout << "]";
				glEnd();
			}
			//std::cout << "" << std::endl;

#define LOL glColor3f(fmod(r += 0.33f, 1.f), fmod(g += 0.33f, 1.f), fmod(b += 0.33f, 1.f));
#define LOL2 glColor3f(.0f, 0.5f, 0.0f);
			

			//PART2
			// STRIP 1
			if (points.middleBranchInLastIndex > 0)
			{
				glBegin(GL_TRIANGLE_STRIP);
				// LOL

				LOL
				glVertex3f(points.rightBranchInPoints[0].first,
						   points.rightBranchInPoints[0].second, z);

				while(i < points.middleBranchInLastIndex)
				{					
					LOL2
					glVertex3f(points.middleBranchInPoints[i].first,
							   points.middleBranchInPoints[i].second, 0.f);
					i++;
					LOL
					glVertex3f(points.rightBranchInPoints[i].first,
							   points.rightBranchInPoints[i].second, z);
				}
				LOL2
				glVertex3f(points.middleBranchIntersection.first,
						   points.middleBranchIntersection.second, 0.f);
				glEnd();
			}
			// FAN
			glBegin(GL_TRIANGLE_FAN);
			// glColor3f(.0f, 0.f, 1.f);
			LOL2
			glVertex3f(points.middleBranchIntersection.first,
					   points.middleBranchIntersection.second, 0.f);
			//std::cout << "[middle]";
			//std::cout << "in[";
			for (size_t j = i; j < points.rightBranchInLastIndex; j++)
			{
				//std::cout << j << ",";
				LOL
				
				glVertex3f(points.rightBranchInPoints[j].first,
						   points.rightBranchInPoints[j].second, z);
			}
			//std::cout << "][mid]";
			
				LOL
			glVertex3f(points.rightBranchIntersection.first,
					   points.rightBranchIntersection.second, 0.f);
			// glColor3f(1.f, 0.f, 0.f);
			i = points.middleBranchOutLastIndex;
			//std::cout << "out[";
			
			for (int j = points.rightBranchOutLastIndex - 1;
				 j >= static_cast<int>(i); j--)
			{
				//std::cout << j << ",";
				LOL
				glVertex3f(points.rightBranchOutPoints[j].first,
						   points.rightBranchOutPoints[j].second, z);
			}
			
			//std::cout << "]";
			//std::cout << "   ";
			
			glEnd();
			// STRIP2
			if (points.middleBranchOutLastIndex > 0)
			{
				glBegin(GL_TRIANGLE_STRIP);
				// glColor3f(0.f, 0.5f, 0.0f);
				//std::cout << "[middle]";
				LOL2
				glVertex3f(points.middleBranchIntersection.first,
						   points.middleBranchIntersection.second, 0.f);
				//std::cout << "mid/middle[";
				for (i = points.middleBranchOutLastIndex;;i--)
				{
					//std::cout << i << ", ";
					
					LOL
					glVertex3f(points.rightBranchOutPoints[i].first,
							   points.rightBranchOutPoints[i].second, z);
					LOL2
					glVertex3f(points.middleBranchOutPoints[i].first,
							   points.middleBranchOutPoints[i].second, 0.f);
					if (i == 0)
						break ;
				}
				//std::cout << "]";
				glEnd();
			}
			//std::cout << "" << std::endl;

			//fin
			
		}
		
	}
	else
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i <= POINTS_PER_SIDE; i++)
		{
			x = (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV;
				
			// LOL
			// glColor3f(fmod(r, 1.f), fmod(g, 1.f), fmod(b, 1.f));
			glColor3f(fmod(r += 0.33f, 1.f), fmod(g += 0.33f, 1.f), fmod(b += 0.33f, 1.f));
			
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
