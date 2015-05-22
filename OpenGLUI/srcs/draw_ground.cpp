// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   draw_ground.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/22 14:51:40 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/22 16:09:32 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "OpenGLUI.class.hpp"
#include <cmath>

// * C-STYLE FUNCTIONS ****************************************************** //
// * MEMBER FUNCTIONS / METHODS ********************************************* //
OpenGLUI::t_groundDatas			OpenGLUI::_buildGroundDatas(void) const
{
	OpenGLUI::t_groundDatas	ret(_winSize.second + 2);

	for (int i = 0; i <= _winSize.second + 1; i++)
	{
		OpenGLUI::t_groundDatas::value_type	tmp(_winSize.first + 2);

		for (int j = 0; j <= _winSize.first + 1; j++)
			// tmp[j] = {
			// 	randf() * 0.2f,
			// 	{0.0f, randf() * 0.66f + 0.33f, 0.f},
			// 	{randf() * 0.1f, randf() * 0.1f,
			// 	 randf() * 0.1f, randf() * 0.1f}
			// };
			tmp[j] = std::make_tuple(
				randf() * 0.3f - 0.1f,
				randf() * 0.3f - 0.1f,
				std::make_tuple(0.0f, randf() * 0.16f + 0.34f, 0.f),
				std::make_tuple(randf() * 0.18f, randf() * 0.18f,
								randf() * 0.18f, randf() * 0.18f)
				);
		ret[i] = std::move(tmp);
	}
	return (ret);
};

#define COLOR_WITH_OFFSET(I)					\
	glColor3f(std::get<0>(c),					\
			  std::get<1>(c) - std::get<I>(d),	\
			  std::get<2>(c));

void						OpenGLUI::_putGround(void) const
{	
	glLoadIdentity();
	glTranslatef(SCREEN_PADDINGF, SCREEN_PADDINGF, 0.0f);
	glScalef(CHUNK_SIZEF, CHUNK_SIZEF, CHUNK_SIZEF);
	glTranslatef(0.5f, 0.5f, 0.0f);
	for (int i = 0; i < _tmpGridSize.second; i++)
	{
		for (int j = 0; j < _tmpGridSize.first; j++)
		{
			auto const &homeLink = this->_groundDatas[i][j];
			auto const &c = std::get<2>(homeLink);
			auto const &d = std::get<3>(homeLink);
			(void)d;
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(std::get<0>(c), std::get<1>(c), std::get<2>(c));
			glVertex3f(0.f, 0.f, std::get<1>(homeLink));
			COLOR_WITH_OFFSET(0);
			glVertex3f(-0.5f, -0.5f, std::get<0>(homeLink));
			COLOR_WITH_OFFSET(1);
			glVertex3f(+0.5f, -0.5f, std::get<0>(this->_groundDatas[i + 0][j + 1]));
			COLOR_WITH_OFFSET(2);
			glVertex3f(+0.5f, +0.5f, std::get<0>(this->_groundDatas[i + 1][j + 1]));
			COLOR_WITH_OFFSET(3);
			glVertex3f(-0.5f, +0.5f, std::get<0>(this->_groundDatas[i + 1][j + 0]));
			COLOR_WITH_OFFSET(0);
			glVertex3f(-0.5f, -0.5f, std::get<0>(homeLink));
			glEnd();
			glTranslatef(1.f, 0.f, 0.f);
		}
		glTranslatef(0.f, 1.f, 0.f);
		glTranslatef(static_cast<float>(-_tmpGridSize.first), 0.f, 0.f);
	}
	return ;
}
