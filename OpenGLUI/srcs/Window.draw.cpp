// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.draw.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/30 08:24:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/19 12:42:11 by ngoguey          ###   ########.fr       //
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
	std::pair<int, int> prevPos,
	std::pair<int, int> nextPos,
	float phase, bool narrowFront
	) const
{
	std::pair<int, int> prevDelta =
		std::make_pair<int, int>(selfPos.first - prevPos.first,
								 selfPos.second - prevPos.second);
	std::pair<int, int> nextDelta =
		std::make_pair<int, int>(nextPos.first - selfPos.first,
								 nextPos.second - selfPos.second);
	if (prevDelta.first > 1)
		prevDelta.first = -1;
	else if (prevDelta.first < -1)
		prevDelta.first = 1;
	if (prevDelta.second > 1)
		prevDelta.second = -1;
	else if (prevDelta.second < -1)
		prevDelta.second = 1;
	if (nextDelta.first > 1)
		nextDelta.first = -1;
	else if (nextDelta.first < -1)
		nextDelta.first = 1;
	if (nextDelta.second > 1)
		nextDelta.second = -1;
	else if (nextDelta.second < -1)
		nextDelta.second = 1;

	std::pair<float, float> const	topLeft(
		_topLeftCell.first + CHUNK_SIZEF * selfPos.first,
		_topLeftCell.second + CHUNK_SIZEF * selfPos.second);
	float ratio = fmod(glfwGetTime(), 5.f) / 5.f; //debug
	(void)ratio;
	
	glLoadIdentity();
	glTranslatef(topLeft.first, topLeft.second, -0.0f);
	rotateChunk(prevDelta, nextDelta);
	
	// glRotatef(ratio * 360.f, 0, 1, 0);
	// glRotatef(0.f, 0, 1, 0);	

	float curphase = phase;

	float z = SNAKE_HEIGHT;
	float r = 0.f, g = 0.33f, b = .66f;
	(void)r;
	(void)g;
	(void)b;
	
	// float z = SNAKE_HEIGHT;
	float x, y = 0.f;

	float narrow(0.0f);
	
	if ((prevDelta.first != 0) != (nextDelta.first != 0))
	{
		if ((prevDelta.second > 0 && nextDelta.first > 0) ||
			(prevDelta.second < 0 && nextDelta.first < 0) ||
			(prevDelta.first > 0 && nextDelta.second < 0) ||
			(prevDelta.first < 0 && nextDelta.second > 0)) //sinistro
		{
			auto const	&points = Window::sinPoints[
				static_cast<int>(std::round(phase * NUM_PRECALC_POINTSF - 0.5f))];

			
#define COL1 glColor3f(244.f / 256.f ,164.f / 256.f ,96.f / 256.f )
#define COL2 glColor3f(139.f / 256.f,69.f / 256.f,19.f / 256.f)
#define COL3 glColor3f(165.f / 256.f,42.f / 256.f,42.f / 256.f)

#define PUTCOLOR								\
			if (v.z < 0.5f)						\
				COL3;							\
			else								\
				COL2;
			
#define PUTCOLOR2								\
			if (v.z < 0.5f)						\
				COL1;							\
			else								\
				COL2;							\
			
//glColor3f(fmod(r += 0.33f, 1.f), fmod(g += 0.33f, 1.f), fmod(b += 0.33f, 1.f));	
			
			glBegin(GL_TRIANGLE_STRIP);
			// glColor3f(.5f, 0.0f, 0.0f);
			
			for (auto const &v : points.leftStrip1)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(.0f, 0.5f, 0.0f);				
			for (auto const &v : points.leftFan)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.0f, 0.0f, 0.5f);				
			for (auto const &v : points.leftStrip2)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();

			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.5f, 0.5f, 0.0f);				
			for (auto const &v : points.rightStrip1)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(.5f, 0.0f, 0.0f);				
			for (auto const &v : points.rightFan)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.0f, 5.0f, 0.f);				
			for (auto const &v : points.rightStrip2)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
		}
		else
		{
			auto const	&points = Window::dexPoints[
				static_cast<int>(std::round(phase * NUM_PRECALC_POINTSF - 0.5f))];

			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.5f, 0.0f, 0.0f);
			for (auto const &v : points.leftStrip1)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(.0f, 0.5f, 0.0f);
			for (auto const &v : points.leftFan)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.0f, 0.0f, 0.5f);
			for (auto const &v : points.leftStrip2)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.5f, 0.5f, 0.0f);
			for (auto const &v : points.rightStrip1)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(.5f, 0.0f, 0.0f);
			for (auto const &v : points.rightFan)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.0f, 5.0f, 0.f);
			for (auto const &v : points.rightStrip2)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
		}
	}
	else
	{
		glBegin(GL_TRIANGLE_STRIP);
		narrow = 0.f;
		narrow = 1.f;
		for (int i = 0; i <= POINTS_PER_SIDE; i++)
		{
			x = (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV;

			x += SNAKE_WIDTH / 2.f * (1.f - narrow);
			COL1;
			glVertex3f(x * CHUNK_SIZE, y, 0.f);
			COL2;
			glVertex3f((x + SNAKE_WIDTH_HALF
						* narrow
						   ) * CHUNK_SIZE, y, z
					   * narrow
				);

			y += TRIANGLES_DISTANCE;
			// y += TRIANGLES_DISTANCE;
			curphase += PHASE_PER_TRIANGLE;
				(void)narrowFront;
			if (narrowFront)
				narrow -= 1.f / POINTS_PER_SIDEF * 0.55f;
		}
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
		curphase = phase;	
		y = 0.f;
		narrow = 1.f;
		for (int i = 0; i <= POINTS_PER_SIDE; i++)
		{
			x = (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV;

			
			x += SNAKE_WIDTH / 2.f * (1.f - narrow);
			COL3;
			glVertex3f((x + SNAKE_WIDTH
						* narrow
						
						   ) * CHUNK_SIZE, y, 0.f);
			COL2;
			glVertex3f((x + SNAKE_WIDTH_HALF
						* narrow
						// * (1.f - narrow)
						
						   ) * CHUNK_SIZE, y, z
					   * narrow
				);
				
			y += TRIANGLES_DISTANCE;
			curphase += PHASE_PER_TRIANGLE;
			if (narrowFront)
			narrow -= 1.f / POINTS_PER_SIDEF * 0.55f;
		}	
		glEnd();
	}
	return ;
}

void                        Window::_put_block(std::pair<int, int> const &topLeft,
											   std::tuple<float, float, float> c) const
{
	glLoadIdentity();
	glTranslatef(topLeft.first * CHUNK_SIZEF + 10
				 , topLeft.second * CHUNK_SIZEF + 10
				 , -0.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(std::get<0>(c) * 1.f, std::get<1>(c) * 1.f, std::get<2>(c) * 1.f);
	glVertex3f(0.5f * CHUNK_SIZEF, 0.f * CHUNK_SIZEF, 0.f);
	glColor3f(std::get<0>(c) * 0.8f, std::get<1>(c) * 0.8f, std::get<2>(c) * 0.8f);
	glVertex3f(0.f * CHUNK_SIZEF, 1.f * CHUNK_SIZEF, 0.f);
	glColor3f(std::get<0>(c) * 0.6f, std::get<1>(c) * 0.6f, std::get<2>(c) * 0.6f);
	glVertex3f(0.5f * CHUNK_SIZEF, 0.5f * CHUNK_SIZEF, CHUNK_SIZEF);
	glColor3f(std::get<0>(c) * 0.4f, std::get<1>(c) * 0.4f, std::get<2>(c) * 0.4f);
	glVertex3f(1.f * CHUNK_SIZEF, 1.f * CHUNK_SIZEF, 0.f);
	glColor3f(std::get<0>(c) * 1.f, std::get<1>(c) * 1.f, std::get<2>(c) * 1.f);
	glVertex3f(0.5f * CHUNK_SIZEF, 0.f * CHUNK_SIZEF, 0.f);
	glEnd();
	return ;
}


void                 Window::_put_head(
	std::pair<int, int> const &selfPos,
	std::pair<int, int> const &prevPos,
	float phase, float ratio) const
{
	std::pair<int, int> prevDelta =
		std::make_pair<int, int>(selfPos.first - prevPos.first,
								 selfPos.second - prevPos.second);
	std::pair<float, float> const	topLeft(
		_topLeftCell.first + CHUNK_SIZEF * selfPos.first,
		_topLeftCell.second + CHUNK_SIZEF * selfPos.second);

	if (prevDelta.first > 1)
		prevDelta.first = -1;
	else if (prevDelta.first < -1)
		prevDelta.first = 1;
	if (prevDelta.second > 1)
		prevDelta.second = -1;
	else if (prevDelta.second < -1)
		prevDelta.second = 1;
	(void)ratio;
	
	glLoadIdentity();
	glTranslatef(topLeft.first, topLeft.second, 0.f);
	rotateChunk(prevDelta, prevDelta);

	glScalef(CHUNK_SIZEF, CHUNK_SIZEF, SNAKE_HEIGHT);


#define TRUC (ratio - 0.65f)
	// phase += PHASE_PER_CHUNK * (ratio - 0.65f);
	phase += PHASE_PER_CHUNK * TRUC;
	std::fmod(phase + 1.f, 1.f);
	
	float x = (cosf((0.5f + phase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV;

	glTranslatef(x - SNAKE_WIDTH_INV / 2.f, 0.f, 0.f);
	glTranslatef(0.f, TRUC, 0.f);
	glTranslatef(0.f, 0.f, -0.5f);	
#define HEIGHT1 0.60f
#define FRONT_INSETS_1 0.15f
	/*
	  glBegin(GL_TRIANGLE_FAN);
	  glColor3f(0.95f, 0.05f, 0.f);
	  glVertex3f(0.5f, 0.5f, 0.0f);
	  glColor3f(1.f, 0.0f, 0.f);
	  glVertex3f(0.f, 0.f, 0.f);	
	  glVertex3f(1.f, 0.f, 0.f);
 	  glVertex3f(1.f - FRONT_INSETS_1, 1.f - FRONT_INSETS_1, HEIGHT1);
	  glVertex3f(0.f + FRONT_INSETS_1, 1.f - FRONT_INSETS_1, HEIGHT1);
	  glVertex3f(0.f, 0.f, HEIGHT1);
	  glEnd();
	*/
	glBegin(GL_TRIANGLE_FAN);
	// glColor3f(0.5f, 0.25f, 0.f);
	COL3;
	glVertex3f(0.5f, 0.25f, 1.25f);
#define HEIGHT2 0.60f
#define FRONT_INSETS_2 0.15f
	glColor3f(0.5f, 0.5f, 0.f);
	COL2;
	glVertex3f(0.f, 0.f, HEIGHT2);	
	glVertex3f(0.5f, -0.5f, 1.35f);	
	glVertex3f(1.f, 0.f, HEIGHT2);
	COL1;
	glVertex3f(1.f - FRONT_INSETS_2, 1.f - FRONT_INSETS_2, HEIGHT2);
 	glVertex3f(0.f + FRONT_INSETS_2, 1.f - FRONT_INSETS_2, HEIGHT2);
	COL2;
	glVertex3f(0.f, 0.f, HEIGHT2);
	glEnd();
	
#define SCALE_FACTOR 4.f	
	glScalef(1 / SCALE_FACTOR, 1 / SCALE_FACTOR, 1 / SCALE_FACTOR);
	glTranslatef(0.15f * SCALE_FACTOR, 0.25f * SCALE_FACTOR, SCALE_FACTOR);
	// glColor3f(148.f / 256.f, 67.f / 256.f, 157.f / 256.f);
	glColor3f(0.95f, 0.05f, 0.f);
	
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);
	glVertex3f(1.f, 1.f, 1.f);	
	glEnd();


	glTranslatef(0.4f * SCALE_FACTOR, .0f, .0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(1.f, 0.f, 0.f);
	glVertex3f(1.f, 1.f, 0.f);
	glVertex3f(0.f, 1.f, 1.f);	
	glEnd();

	(void)phase;
	(void)prevDelta;

	
	
	
	return ;
}
