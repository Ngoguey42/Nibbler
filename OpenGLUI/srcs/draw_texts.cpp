// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   draw_texts.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/01 13:31:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/06/01 14:22:05 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "OpenGLUI.class.hpp"
#include <string>


void                        OpenGLUI::_putTexts(IGame const &game)
{
	int const		fontSize(_winSize.first / 19);
	double const	padding(static_cast<double>(_winSize.first) / 19.);
	double const	timeWidth(static_cast<double>(_winSize.first) / 19. * 8.);
	double const	pausePadding(
		(static_cast<double>(_winSize.first) -
		 static_cast<double>(_winSize.first) / 19. * 4.) / 2.);

	this->_font.FaceSize(fontSize);
	this->_font.Render(
		(std::string("Score: ") += std::to_string(game.getScore())).c_str(),
		-1, FTPoint(padding, padding));
	this->_font.Render(
		(std::string("Played: ")
		 += std::to_string(game.getPlayTime() / 60)
		 += std::string(":")
		 += std::string(game.getPlayTime() % 60 > 9 ? "" : "0")
		 += std::to_string(game.getPlayTime() % 60)).c_str(),
		-1, FTPoint(static_cast<double>(_winSize.first) - timeWidth - padding,
					padding));
	if (game.isPaused())
	{
		this->_font.Render(
			std::string("Paused").c_str(), -1,
			FTPoint(pausePadding, static_cast<double>(_winSize.second) / 2.));
	}



	return ;
}
