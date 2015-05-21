// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.draw.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/30 08:24:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/21 19:22:52 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Window.class.hpp"
#include <cmath>
#include <cfenv>

// * C-STYLE FUNCTIONS ****************************************************** //
static void					rotateChunk(std::pair<int, int> const &prevDelta)
{
	if (prevDelta.first != 0)
	{	// x changes
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
	{	// y changes
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

std::pair<int, int>	buildDelta(std::pair<int, int> const &a,
							   std::pair<int, int> const &b)
{
	std::pair<int, int>	delta(b.first - a.first,
							  b.second - a.second);

	if (delta.first > 1)
		delta.first = -1;
	else if (delta.first < -1)
		delta.first = 1;
	if (delta.second > 1)
		delta.second = -1;
	else if (delta.second < -1)
		delta.second = 1;
	return (delta);
}

#define COL1 glColor3f(244.f / 256.f ,164.f / 256.f ,96.f / 256.f)
#define COLOR1 std::make_tuple(244.f / 256.f, 164.f / 256.f, 96.f / 256.f)
#define COL2 glColor3f(139.f / 256.f,69.f / 256.f,19.f / 256.f)
#define COLOR2 std::make_tuple(139.f / 256.f, 69.f / 256.f, 19.f / 256.f)
#define COL3 glColor3f(165.f / 256.f,42.f / 256.f,42.f / 256.f)
#define COLOR3 std::make_tuple(165.f / 256.f, 42.f / 256.f, 42.f / 256.f)

inline void					_straightSnake(float const phase,
										   float const frontThickness,
										   float const rearThickness)
{
	float		x;
	float		y = 0.f;
	float		narrow = rearThickness;
	float const	deltaNarrow = (frontThickness - rearThickness) / POINTS_PER_SIDEF;
	float		curphase = phase;

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= POINTS_PER_SIDE; i++)
	{
		x = (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV
			+ SNAKE_WIDTH / 2.f * (1.f - narrow);
		COL1;
		glVertex3f(x * CHUNK_SIZE, y, 0.f);
		COL2;
		glVertex3f((x + SNAKE_WIDTH_HALF * narrow) * CHUNK_SIZE, y,
				   SNAKE_HEIGHT * narrow);

		y += TRIANGLES_DISTANCE;
		curphase = ftce::fmod(curphase + PHASE_PER_TRIANGLE, 1.f);
		// if (frontThickness)
		narrow += deltaNarrow;
		// narrow -= 1.f / POINTS_PER_SIDEF * 0.55f;
	}
	glEnd();

	curphase = phase;
	y = 0.f;
	narrow = rearThickness;
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= POINTS_PER_SIDE; i++)
	{
		x = (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV
			+ SNAKE_WIDTH / 2.f * (1.f - narrow);
		COL3;
		glVertex3f((x + SNAKE_WIDTH * narrow) * CHUNK_SIZE, y, 0.f);
		COL2;
		glVertex3f((x + SNAKE_WIDTH_HALF * narrow) * CHUNK_SIZE, y,
				   SNAKE_HEIGHT * narrow);
		
		y += TRIANGLES_DISTANCE;
		curphase = ftce::fmod(curphase + PHASE_PER_TRIANGLE, 1.f);
		// if (frontThickness)
		narrow += deltaNarrow;
		// narrow -= 1.f / POINTS_PER_SIDEF * 0.55f;
	}	
	glEnd();	
	return ;
	(void)deltaNarrow;
	(void)narrow;
	(void)frontThickness;
	(void)rearThickness;
}

template<typename T>
void				putVertices(
	T const &array, decltype(GL_TRIANGLE_STRIP) type, t_color const &color)
{
	glBegin(type);
	for (auto const &v : array)
	{
		if (v.z < .5f)
			glColor3f(std::get<0>(color),
					  std::get<1>(color),
					  std::get<2>(color));
		else
			COL2;
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	return ;
}

// * MEMBER FUNCTIONS / METHODS ********************************************* //
void						Window::_putSnakeChunk(
	std::pair<int, int> const &selfPos,
	std::pair<int, int> const &prevPos,
	std::pair<int, int> const &nextPos,
	float phase, float frontThickness /*= 1.f*/, float rearThickness /*= 1.f*/
	) const
{
	std::pair<int, int> prevDelta(buildDelta(prevPos, selfPos));
	std::pair<int, int> nextDelta(buildDelta(selfPos, nextPos));

	glLoadIdentity();
	glTranslatef(_topLeftCell.first + CHUNK_SIZEF * selfPos.first,
				 _topLeftCell.second + CHUNK_SIZEF * selfPos.second, -0.0f);
	rotateChunk(prevDelta);
	if ((prevDelta.first != 0) != (nextDelta.first != 0))	// Angles
	{
		std::fesetround(FE_TONEAREST);
		if ((prevDelta.second > 0 && nextDelta.first > 0) ||
			(prevDelta.second < 0 && nextDelta.first < 0) ||
			(prevDelta.first > 0 && nextDelta.second < 0) ||
			(prevDelta.first < 0 && nextDelta.second > 0))
		{	// Sinistro
			auto const	&points = Window::sinPoints[
				std::lrint(
					ftce::fmod(phase, 1.f) * NUM_PRECALC_POINTSF - 0.5f)];

			putVertices(points.leftStrip1, GL_TRIANGLE_STRIP, COLOR3);
			putVertices(points.leftFan, GL_TRIANGLE_FAN, COLOR3);
			putVertices(points.leftStrip2, GL_TRIANGLE_STRIP, COLOR3);
			putVertices(points.rightStrip1, GL_TRIANGLE_STRIP, COLOR1);
			putVertices(points.rightFan, GL_TRIANGLE_FAN, COLOR1);
			putVertices(points.rightStrip2, GL_TRIANGLE_STRIP, COLOR1);			
		}
		else
		{	// Dextro
			auto const	&points = Window::dexPoints[
				std::lrint(
					ftce::fmod(phase, 1.f) * NUM_PRECALC_POINTSF - 0.5f)];
	
			putVertices(points.leftStrip1, GL_TRIANGLE_STRIP, COLOR3);
			putVertices(points.leftFan, GL_TRIANGLE_FAN, COLOR3);
			putVertices(points.leftStrip2, GL_TRIANGLE_STRIP, COLOR3);
			putVertices(points.rightStrip1, GL_TRIANGLE_STRIP, COLOR1);
			putVertices(points.rightFan, GL_TRIANGLE_FAN, COLOR1);
			putVertices(points.rightStrip2, GL_TRIANGLE_STRIP, COLOR1);			
		}
	}
	else
		_straightSnake(phase, frontThickness, rearThickness);
	return ;
}

static constexpr t_appleStrip		buildAppleStrip(
	float bottomZ, float bottomRadius, float bottomStartAngle,
	float topZ, float topRadius, float topStartAngle,
	float bottomXDeviation = 0.f, float bottomYDeviation = 0.f,
	float topXDeviation = 0.f, float topYDeviation = 0.f)
{
	t_appleStrip	strip;

	for (int i = 0; i <= NUM_POINTS_PER_APPLE_SLICE; i++)
	{
		strip[i * 2] = ftce::Vertex(
			ftce::cos(bottomStartAngle) * bottomRadius + bottomXDeviation,
			ftce::sin(bottomStartAngle) * bottomRadius + bottomYDeviation,
			bottomZ);
		strip[i * 2 + 1] = ftce::Vertex(
			ftce::cos(topStartAngle) * topRadius + topXDeviation,
			ftce::sin(topStartAngle) * topRadius + topYDeviation,
			topZ);
		bottomStartAngle += APPLE_POINTS_DELTA_RAD;
		topStartAngle += APPLE_POINTS_DELTA_RAD;
	}
	return (strip);
}

static constexpr t_apple			buildApple(void)
{
	t_apple		apple;
	float		phase = 0.f;

#define APPLE_ROTATION (APPLE_POINTS_DELTA_RAD / 3.f)
#define HA0 0.03f
#define HA1 (HA0 + 0.29f)
#define HA2 (HA1 + 0.29f)
#define HA3 (HA2 + 0.26f)
#define HA4 (HA3 + 0.04f)
#define HA5 (HA4 - 0.03f)
#define HA6 (HA5 - 0.1f)
	apple[0] = buildAppleStrip(
		HA0, 0.64f / 2.f, phase,
		HA1, 0.99f / 2.f, phase + APPLE_ROTATION);
	phase += APPLE_ROTATION;
	apple[1] = buildAppleStrip(
		HA1, 0.99f / 2.f, phase,
		HA2, 0.99f / 2.f, phase + APPLE_ROTATION);
	phase += APPLE_ROTATION;
	apple[2] = buildAppleStrip(
		HA2, 0.99f / 2.f, phase,
		HA3, 0.60f / 2.f, phase + APPLE_ROTATION);
	phase += APPLE_ROTATION;
	apple[3] = buildAppleStrip(
		HA3, 0.60f / 2.f, phase,
		HA4, 0.37f / 2.f, phase + APPLE_ROTATION);
	phase += APPLE_ROTATION;
	apple[4] = buildAppleStrip(
		HA4, 0.37f / 2.f, phase,
		HA5, 0.27f / 2.f, phase + APPLE_ROTATION);
	phase += APPLE_ROTATION;
	apple[5] = buildAppleStrip(
		HA5, 0.27f / 2.f, phase,
		HA6, 0.f / 2.f, phase + APPLE_ROTATION);
	phase += APPLE_ROTATION;
	return (apple);
}

static constexpr t_apple			buildStem(void)
{
	t_apple		stem;
	float		phase = 0.f;

#define STEM_ROTATION (APPLE_POINTS_DELTA_RAD / 2.f)
#define HS0 (HA6)
#define HS1 (HS0 + 0.29f)
#define HS2 (HS1 + 0.29f)
	stem[0] = buildAppleStrip(
		HS0, 0.05f / 2.f, phase,
		HS1, 0.10f / 2.f, phase + APPLE_ROTATION,
		0.f, 0.f, 0.05f, -0.05f);
	phase += STEM_ROTATION;
	stem[1] = buildAppleStrip(
		HS1, 0.10f / 2.f, phase,
		HS2, 0.14f / 2.f, phase + APPLE_ROTATION,
		0.05f, -0.05f, 0.1f, -0.1f);
	phase += STEM_ROTATION;
#undef STEM_ROTATION
	return (stem);
}

void                        Window::_put_block(std::pair<int, int> const &topLeft,
											   IBlock::Type type) const
{
	constexpr t_apple	apple(buildApple());
	constexpr t_apple	stem(buildStem());
	
	glLoadIdentity();
	glTranslatef(topLeft.first * CHUNK_SIZEF + SCREEN_PADDINGF
				 , topLeft.second * CHUNK_SIZEF + SCREEN_PADDINGF
				 , -0.0f);
	glScalef(CHUNK_SIZEF, CHUNK_SIZEF, CHUNK_SIZEF);
	// glScalef(5.f, 5.f, 5.f);
	glTranslatef(0.5f, 0.5f, 0.f);
	glRotatef(glfwGetTime() * 40.f *
			  (-1.f + 2.f * static_cast<float>(topLeft.first * topLeft.second % 2)),
			  0, 0, 1);
	for (auto const &w : apple)
	{
		unsigned int seed = topLeft.first * topLeft.second;
		
		glBegin(GL_TRIANGLE_STRIP);
		for (auto const &v : w)
		{
			if (type == IBlock::GROW)
				glColor3f(static_cast<float>(rand_r(&seed) % 4 * 15 + 200) /
						  256.f, 0.f, 0.f);
			else if (type == IBlock::BONUS)
				glColor3f(static_cast<float>(rand_r(&seed) % 8 * 25 + 5) /
						  256.f, 0.f, 0.f);
			glVertex3f(v.x, v.y, v.z);
		}
		glEnd();
	}	
	glColor3f(87.f / 256.f, 45.f / 256.f, 9.f / 256.f);
	for (auto const &w : stem)
	{		
		glBegin(GL_TRIANGLE_STRIP);
		for (auto const &v : w)
		{
			glVertex3f(v.x, v.y, v.z);
		}
		glEnd();
	}	

	// glVertex3f(0.5f * CHUNK_SIZEF, 0.f * CHUNK_SIZEF, 0.f);
	// glColor3f(std::get<0>(c) * 0.8f, std::get<1>(c) * 0.8f, std::get<2>(c) * 0.8f);
	// glVertex3f(0.f * CHUNK_SIZEF, 1.f * CHUNK_SIZEF, 0.f);
	// glColor3f(std::get<0>(c) * 0.6f, std::get<1>(c) * 0.6f, std::get<2>(c) * 0.6f);
	// glVertex3f(0.5f * CHUNK_SIZEF, 0.5f * CHUNK_SIZEF, CHUNK_SIZEF);
	// glColor3f(std::get<0>(c) * 0.4f, std::get<1>(c) * 0.4f, std::get<2>(c) * 0.4f);
	// glVertex3f(1.f * CHUNK_SIZEF, 1.f * CHUNK_SIZEF, 0.f);
	// glColor3f(std::get<0>(c) * 1.f, std::get<1>(c) * 1.f, std::get<2>(c) * 1.f);
	// glVertex3f(0.5f * CHUNK_SIZEF, 0.f * CHUNK_SIZEF, 0.f);
	return ;
}


void                 Window::_put_head(
	std::pair<int, int> const &selfPos,
	std::pair<int, int> const &prevPos,
	float phase, float ratio) const
{
	std::pair<int, int> prevDelta(buildDelta(prevPos, selfPos));
	std::pair<float, float> const	topLeft(
		_topLeftCell.first + CHUNK_SIZEF * selfPos.first,
		_topLeftCell.second + CHUNK_SIZEF * selfPos.second);

	glLoadIdentity();
	glTranslatef(_topLeftCell.first + CHUNK_SIZEF * selfPos.first,
				 _topLeftCell.second + CHUNK_SIZEF * selfPos.second, -0.0f);
	rotateChunk(prevDelta);	
	glScalef(CHUNK_SIZEF, CHUNK_SIZEF, SNAKE_HEIGHT);

	ratio -= 0.65f;
	phase = ftce::fmod(phase + PHASE_PER_CHUNK * ratio, 1.f);	
	(void)ratio;
	glTranslatef(
		(cosf((0.5f + phase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV -
		SNAKE_WIDTH_INV / 2.f,
		ratio, -0.5f);
	// Head Top
	glBegin(GL_TRIANGLE_FAN);
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
	// Right eye
#define SCALE_FACTOR 4.f	
	glScalef(1 / SCALE_FACTOR, 1 / SCALE_FACTOR, 1 / SCALE_FACTOR);
	glTranslatef(0.15f * SCALE_FACTOR, 0.25f * SCALE_FACTOR, SCALE_FACTOR);
	glColor3f(0.95f, 0.05f, 0.f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);
	glVertex3f(1.f, 1.f, 1.f);	
	glEnd();
	// Left eye
	glTranslatef(0.4f * SCALE_FACTOR, .0f, .0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(1.f, 0.f, 0.f);
	glVertex3f(1.f, 1.f, 0.f);
	glVertex3f(0.f, 1.f, 1.f);	
	glEnd();
	return ;
}
