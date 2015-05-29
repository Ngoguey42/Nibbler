// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   draw_items.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/22 14:52:05 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/29 15:33:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "OpenGLUI.class.hpp"
#include <cmath>

// * C-STYLE FUNCTIONS ****************************************************** //
static constexpr t_appleStrip		buildAppleStrip(
	float bottomZ, float bottomRadius, float bottomStartAngle,
	float topZ, float topRadius, float topStartAngle,
	float bottomXDeviation = 0.f, float bottomYDeviation = 0.f,
	float topXDeviation = 0.f, float topYDeviation = 0.f)
{
	t_appleStrip	strip;

	for (int i = 0; i <= NUM_POINTS_PER_APPLE_SLICE; i++)
	{
		strip[i * 2] = ftce::Vertex<>(
			ftce::cos(bottomStartAngle) * bottomRadius + bottomXDeviation,
			ftce::sin(bottomStartAngle) * bottomRadius + bottomYDeviation,
			bottomZ);
		strip[i * 2 + 1] = ftce::Vertex<>(
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

static inline void			putColor(IBlock::Type type, unsigned int &seed)
{
	auto const it = OpenGLUI::blocksSchemes.find(type);

	if (it != OpenGLUI::blocksSchemes.end())
	{
		auto const &scheme = OpenGLUI::blocksSchemes.find(type)->second;
		glColor3ub(
			rand_r(&seed) % scheme[0] * scheme[1] + scheme[2],
			rand_r(&seed) % scheme[3] * scheme[4] + scheme[5],
			rand_r(&seed) % scheme[6] * scheme[7] + scheme[8]);
	}
	return ;
}

static inline void			putApple(std::pair<int, int> const &topLeft,
									 IBlock::Type type)
{
	constexpr t_apple	apple(buildApple());
	constexpr t_apple	stem(buildStem());

	glRotatef(
		getPhaseLoop() * 360.f *
		(-1.f + 2.f * static_cast<float>((topLeft.first + topLeft.second) % 2)),
		0, 0, 1);
	glTranslatef(
		0.f, 0.f,
		getPhase(3.f, static_cast<float>(topLeft.first + topLeft.second)) * 0.45f
		);
	glScalef(0.9f, 0.9f, 0.9f);
	for (auto const &w : apple)
	{
		unsigned int seed = topLeft.first * topLeft.second;

		glBegin(GL_TRIANGLE_STRIP);
		for (auto const &v : w)
		{
			putColor(type, seed);
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
	return ;
}

// * MEMBER FUNCTIONS / METHODS ********************************************* //
void                        OpenGLUI::_put_block(std::pair<int, int> const &topLeft,
												 IBlock::Type type) const
{
	glLoadIdentity();
	glTranslatef(topLeft.first * CHUNK_SIZEF + SCREEN_PADDINGF
				 , topLeft.second * CHUNK_SIZEF + SCREEN_PADDINGF
				 , -0.0f);
	glScalef(CHUNK_SIZEF, CHUNK_SIZEF, CHUNK_SIZEF);
	// glScalef(5.f, 5.f, 5.f);
	glTranslatef(0.5f, 0.5f, 0.f);
	if (type == IBlock::WALL)
	{
		glBegin(GL_TRIANGLE_STRIP);
		glColor3ub(200, 200, 200);
		glVertex3f(0.f, -0.5f, 0.f);
		glVertex3f(-0.5f, 0.5f, 0.f);
		glVertex3f(0.f, 0.f, 1.f);
		glVertex3f(0.5f, 0.5f, 0.f);
		glVertex3f(0.f, -0.5f, 0.f);
		glEnd();
	}
	else
	{
		putApple(topLeft, type);
	}
	return ;
}
