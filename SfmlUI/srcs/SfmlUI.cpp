/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SfmlUI.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:49:28 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/20 16:51:47 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SfmlUI.hpp"
#include "IGame.hpp"
#include "ISnake.hpp"

SfmlUI::SfmlUI(std::pair<int, int> gameSize, sf::Texture &sprites, sf::Font &font)
	: sf::RenderWindow(_getWindowSize(gameSize, _chunkSize), WINDOW_TITLE, sf::Style::Close),
	_gameSize(gameSize),
	_snakeHeadSprite(sprites, sf::IntRect(192, 0, SPRITES_SIZE, SPRITES_SIZE)),
	_snakeBodySprite(sprites, sf::IntRect(128, 0, SPRITES_SIZE, SPRITES_SIZE)),
	_snakeCornerSprite(sprites, sf::IntRect(64, 0, SPRITES_SIZE, SPRITES_SIZE)),
	_snakeTailSprite(sprites, sf::IntRect(0, 0, SPRITES_SIZE, SPRITES_SIZE)),
	_backgroundSprite(sprites, sf::IntRect(0, 64, SPRITES_SIZE, SPRITES_SIZE)),
	_blockSprites{
		sf::Sprite(sprites, sf::IntRect(128, 64, SPRITES_SIZE, SPRITES_SIZE)),
		sf::Sprite(sprites, sf::IntRect(64, 64, SPRITES_SIZE, SPRITES_SIZE)),
		sf::Sprite(sprites, sf::IntRect(64, 64, SPRITES_SIZE, SPRITES_SIZE)),
		sf::Sprite(sprites, sf::IntRect(192, 64, SPRITES_SIZE, SPRITES_SIZE))
	},
	_font(font)
{
	// Scale sprites
	float scale = static_cast<float>(_chunkSize) / SPRITES_SIZE;
	_snakeHeadSprite.setScale(scale, scale);
	_snakeBodySprite.setScale(scale, scale);
	_snakeCornerSprite.setScale(scale, scale);
	_snakeTailSprite.setScale(scale, scale);
	_backgroundSprite.setScale(scale, scale);
	for (int i = 0; i < IBlock::NOPE; ++i)
		_blockSprites[i].setScale(scale, scale);
	// Setup sprites
	float center = SPRITES_SIZE / 2;
	_snakeHeadSprite.setOrigin(center, center);
	_snakeBodySprite.setOrigin(center, center);
	_snakeCornerSprite.setOrigin(center, center);
	_snakeTailSprite.setOrigin(center, center);
	// Init event map
	_events[sf::Keyboard::Up] = EVENT_UP;
	_events[sf::Keyboard::Right] = EVENT_RIGHT;
	_events[sf::Keyboard::Down] = EVENT_DOWN;
	_events[sf::Keyboard::Left] = EVENT_LEFT;
	_events[sf::Keyboard::Space] = EVENT_SPACE;
	_events[sf::Keyboard::R] = EVENT_R;
	_events[sf::Keyboard::Num1] = EVENT_1;
	_events[sf::Keyboard::Num2] = EVENT_2;
	_events[sf::Keyboard::Num3] = EVENT_3;
	_events[sf::Keyboard::Num4] = EVENT_4;
	_events[sf::Keyboard::Num5] = EVENT_5;
	_events[sf::Keyboard::Num6] = EVENT_6;
	_events[sf::Keyboard::Num7] = EVENT_7;
}

SfmlUI::~SfmlUI(void)
{
}

EventType			SfmlUI::getEvent(void)
{
	sf::Event		event;

	pollEvent(event);
	if (event.type == sf::Event::Closed)
		close();
	else if (event.type == sf::Event::KeyPressed)
	{
		if (_events.find(event.key.code) != _events.end())
			return (_events[event.key.code]);
		if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Escape)
			close();
	}
	return (EVENT_NOPE);
}

void				SfmlUI::draw(IGame const &game)
{
	clear();
	// Draw background
	_drawBackground();
	// Draw blocks
	for (auto *b : game.getBlocks())
		_drawBlock(*b);
	// Draw snake
	_drawSnake(game.getSnake());
	// Draw UI
	_drawText(1, 0.2,
		std::string("Score: ") += std::to_string(game.getScore()), _chunkSize / 2);
	_drawText(5, 0.35,
		std::string("Time: ") += std::to_string(game.getPlayTime()), _chunkSize / 3);
	_drawText(1, _gameSize.second + 1.3,
		std::string("FPS: ") += std::to_string(game.getFPS()), _chunkSize / 4);
	if (game.getSnake().isDie())
		_drawOverlay("Game over");
	else if (game.isPaused())
		_drawOverlay("Pause");
	display();
}

bool				SfmlUI::windowShouldClose(void) const
{
	return (!isOpen());
}

void				SfmlUI::_drawBackground(void)
{
	for (int x = (_gameSize.first - 1) * _chunkSize; x >= 0; x -= _chunkSize)
		for (int y = (_gameSize.second - 1) * _chunkSize; y >= 0; y -= _chunkSize)
		{
			_backgroundSprite.setPosition(x + _chunkSize, y + _chunkSize);
			sf::RenderWindow::draw(_backgroundSprite);
		}
}

void				SfmlUI::_drawBlock(IBlock const &block)
{
	if (block.getType() < 0 || block.getType() >= IBlock::NOPE)
		return ;
	sf::Sprite &sprite = _blockSprites[block.getType()];
	sprite.setPosition(block.getX() * _chunkSize + _chunkSize,
		block.getY() * _chunkSize + _chunkSize);
	sf::RenderWindow::draw(sprite);
}

inline int			getRotation(ISnake::Chunk const &c, ISnake::Chunk const &next)
{
	if (c.second == next.second)
		return ((c.first - next.first) * 90 - 90);
	if (c.first == next.first)
		return ((c.second - next.second) * 90);
	return (0);
}

#define DRAW_SNAKE_CHUNK(chunk, sprite, rotation) \
	sprite.setRotation(rotation); \
	sprite.setPosition(((chunk).first + 1) * _chunkSize + (_chunkSize / 2.f), \
		((chunk).second + 1) * _chunkSize + (_chunkSize / 2.f)); \
	sf::RenderWindow::draw(sprite);

#define BUILD_DELTA(delta, a, b) \
	ISnake::Chunk delta((b).first - (a).first, (b).second - (a).second); \
	if (delta.first > 1) \
		delta.first = -1; \
	else if (delta.first < -1) \
		delta.first = 1; \
	if (delta.second > 1) \
		delta.second = -1; \
	else if (delta.second < -1) \
		delta.second = 1;

void				SfmlUI::_drawSnake(ISnake const &snake)
{
	auto				prev = snake.getChunks().rbegin();
	auto				it = prev + 1;
	auto				end = --(snake.getChunks().rend());

	DRAW_SNAKE_CHUNK(*prev, _snakeTailSprite, getRotation(*it, *prev));
	for (auto next = it + 1; it != end; ++it, ++next)
	{
		if (prev->first == next->first || prev->second == next->second)
		{
			DRAW_SNAKE_CHUNK(*it, _snakeBodySprite, getRotation(*it, *next));
		}
		else
		{
			BUILD_DELTA(deltaPrev, *prev, *it);
			BUILD_DELTA(deltaNext, *it, *next);
			if ((deltaPrev.second > 0 && deltaNext.first > 0) ||
				(deltaPrev.second < 0 && deltaNext.first < 0) ||
				(deltaPrev.first > 0 && deltaNext.second < 0) ||
				(deltaPrev.first < 0 && deltaNext.second > 0))
			{
				DRAW_SNAKE_CHUNK(*it, _snakeCornerSprite, getRotation(*it, *next) + 90);
			}
			else
			{
				DRAW_SNAKE_CHUNK(*it, _snakeCornerSprite, getRotation(*prev, *it) - 90);
			}
		}
		++prev;
	}
	DRAW_SNAKE_CHUNK(*end, _snakeHeadSprite, getRotation(*end, *prev));
}

void				SfmlUI::_drawOverlay(std::string const &text)
{
	static sf::Text				textDraw("", _font);
	static sf::RectangleShape	rect(sf::Vector2f(_chunkSize * (_gameSize.first + 2),
		_chunkSize * (_gameSize.second + 2)));

	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color(GRID_COLOR, 30));
	sf::RenderWindow::draw(rect);
	textDraw.setString(text);
	textDraw.setCharacterSize(_chunkSize * 2);
	sf::FloatRect bounds = textDraw.getLocalBounds();
	textDraw.setPosition(((_chunkSize * _gameSize.first + _chunkSize) - bounds.width) / 2,
		((_chunkSize * _gameSize.second) - bounds.height + _chunkSize) / 2);
	sf::RenderWindow::draw(textDraw);
}

void				SfmlUI::_drawText(float x, float y, std::string const &text, unsigned int size)
{
	static sf::Text		textDraw("", _font);

	textDraw.setString(text);
	textDraw.setCharacterSize(size);
	textDraw.setPosition(x * _chunkSize, y * _chunkSize);
	sf::RenderWindow::draw(textDraw);
}

sf::VideoMode		SfmlUI::_getWindowSize(std::pair<int, int> gameSize, int &chunkSize)
{
	sf::VideoMode		mode = sf::VideoMode::getDesktopMode();

	gameSize.first += 2;
	gameSize.second += 2;
	mode.width -= 100;
	mode.height -= 100;
	chunkSize = std::min(mode.width / gameSize.first, mode.height / gameSize.second);
	chunkSize = std::min(chunkSize - (chunkSize % 2), MAX_CHUNK_SIZE);
	mode.width = chunkSize * gameSize.first;
	mode.height = chunkSize * gameSize.second;
	return (mode);
}
