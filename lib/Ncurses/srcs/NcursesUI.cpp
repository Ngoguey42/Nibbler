/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesUI.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 20:58:30 by juloo             #+#    #+#             */
/*   Updated: 2015/05/06 19:49:39 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "NcursesUI.hpp"
#include "Game.hpp"
#include "IBonus.hpp"

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
	init_color(17, 125, 125, 125);
	init_color(18, 110, 110, 110);
	init_color(19, 95, 95, 95);
	init_color(30, 140, 140, 140);
	init_pair(1, COLOR_WHITE, 30);
	init_pair(2, COLOR_RED, COLOR_RED);
	init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(13, 17, 17);
	init_pair(14, 18, 18);
	init_pair(15, 19, 19);
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
	int				color = 0;

	erase();
	// Draw background
	for (int x = _gameSize.first - 1; x >= 0; --x)
		for (int y = _gameSize.second - 1; y >= 0; --y)
			_drawChunk(x, y, (color = (x + y) % 3) + 13, '.');
	// Draw bonus
	for (auto it = game.bonus.begin();
		it != game.bonus.end();
		++it)
		_drawChunk((*it)->getX(), (*it)->getY(), 3, '+');
	// Draw snake
	for (auto it = game.snake.chunks.begin();
		it != game.snake.chunks.end();
		++it)
		_drawChunk(it->first, it->second, 2, 'X');
	// Draw UI
	for (int x = _gameSize.first - 1; x >= 0; --x)
		_drawChunk(x, -1, 1, ' ');
	_startText(1, -1);
	printw("Score: %-3d Length: %d", game.score, game.snake.chunks.size());
	if (game.snake.die)
		printw("  [[ DIE ]]");
	else if (game.paused)
		printw("  [[ PAUSE ]]");
	refresh();
}

void			NcursesUI::_startText(int x, int y)
{
	x = x * _chunkWidth + _offset.first ;//+ (_chunkWidth / 2);
	y = y * _chunkHeight + _offset.second ;//+ (_chunkHeight / 2);
	move(x, y);
	attron(COLOR_PAIR(1));
}

void			NcursesUI::_drawChunk(int x, int y, int color, char c)
{
	x = x * _chunkWidth + _offset.first;
	y = y * _chunkHeight + _offset.second;
	attron(COLOR_PAIR(color));
	for (int w = _chunkWidth + x - 1; w >= x; --w)
		for (int h = _chunkHeight + y - 1; h >= y; --h)
			mvaddch(h, w, c);
}

void			NcursesUI::_updateSize(void)
{
	int				width;
	int				height;

	getmaxyx(stdscr, height, width);
	_winSize.first = width;
	_winSize.second = height;
	_chunkWidth = std::max(2, std::min(width / _gameSize.first,
		height / (_gameSize.second + 1) * 2));
	_chunkHeight = _chunkWidth / 2;
	_offset = std::make_pair((width - (_chunkWidth * _gameSize.first)) / 2,
		(height - (_chunkHeight * _gameSize.second)) / 2 + 1);
}

bool			NcursesUI::windowShouldClose(void) const
{
	return (_shouldClose);
}
