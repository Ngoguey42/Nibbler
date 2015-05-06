/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesUI.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 20:58:30 by juloo             #+#    #+#             */
/*   Updated: 2015/05/06 16:40:11 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "NcursesUI.hpp"
#include "Game.hpp"

NcursesUI::NcursesUI(std::pair<int, int> gameSize)
	: _gameSize(gameSize), _shouldClose(false)
{
	initscr();
	cbreak();
	timeout(0);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	start_color();
	init_color(17, 200, 200, 200);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, 17);
	init_pair(3, COLOR_RED, COLOR_RED);
	_events['1'] = Event::EVENT_1;
	_events['2'] = Event::EVENT_2;
	_events['3'] = Event::EVENT_3;
	_events['4'] = Event::EVENT_4;
	_events['5'] = Event::EVENT_5;
	_events['6'] = Event::EVENT_6;
	_events['7'] = Event::EVENT_7;
	_events[' '] = Event::EVENT_SPACE;
	_events[KEY_UP] = Event::EVENT_UP;
	_events[KEY_RIGHT] = Event::EVENT_RIGHT;
	_events[KEY_DOWN] = Event::EVENT_DOWN;
	_events[KEY_LEFT] = Event::EVENT_LEFT;
	_updateSize();
}

NcursesUI::~NcursesUI(void)
{
	erase();
	refresh();
	endwin();
}

Event::Type		NcursesUI::getEvent(void)
{
	int				c;

	c = getch();
	if (c == 'q')
		_shouldClose = true;
	else if (c != ERR && _events.find(c) != _events.end())
		return (_events[c]);
	_updateSize();
	return (Event::NOPE);
}

void			NcursesUI::draw(Game const &game)
{
	erase();
	attron(COLOR_PAIR(2));
	for (int h = _gameSize.second * _chunkHeight - 1; h >= 0; --h)
	{
		for (int w = _gameSize.first * _chunkWidth - 1; w >= 0; --w)
		{
			move(h + _offset.second, w + _offset.first);
			printw(" ");
		}
	}
	attron(COLOR_PAIR(3));
	for (auto it = game.snake.chunks.begin();
		it != game.snake.chunks.end();
		++it)
	{
		for (int h = 0; h < _chunkHeight; ++h)
		{
			for (int w = 0; w < _chunkWidth; ++w)
			{
				move(it->second * _chunkHeight + h + _offset.second,
					it->first * _chunkWidth + w + _offset.first);
				printw("X");
			}
		}
	}
	if (game.snake.die)
	{
		attron(COLOR_PAIR(1));
		move(_offset.second, _offset.first);
		printw("[[ DIE ]]");
	}
	refresh();
}

void			NcursesUI::_updateSize(void)
{
	int				width;
	int				height;

	getmaxyx(stdscr, height, width);
	_winSize.first = width;
	_winSize.second = height;
	_chunkWidth = std::min(width / _gameSize.first,
		height / _gameSize.second * 2);
	_chunkHeight = _chunkWidth / 2;
	_offset = std::make_pair((width - (_chunkWidth * _gameSize.first)) / 2,
		(height - (_chunkHeight * _gameSize.second)) / 2);
}

bool			NcursesUI::windowShouldClose(void) const
{
	return (_shouldClose);
}
