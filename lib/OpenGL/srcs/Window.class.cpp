// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/30 10:55:52 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/01 12:11:53 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Window.class.hpp"
#include <cmath>

#define TMP_PADDING ((int)10)

extern "C" Window	*init(std::pair<int, int> gridSize, float cellSize)
{
	std::cout << "init from OpenGL" << std::endl;
	
	return (new Window(gridSize, cellSize));
}

// * STATICS **************************************************************** //
// * CONSTRUCTORS *********************************************************** //
static void error_callback(int error, const char* description)
{
	std::cout << description << "(" << error << ")" << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int, int action, int)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

Window::Window(std::pair<int, int> gridSize, float cellSize) :
	_tmpGridSize(gridSize),
	_cellSize(cellSize),
	_winSize(
		std::make_pair(
			static_cast<int>(std::ceilf(
								 static_cast<float>(gridSize.first) *
								 cellSize)) + TMP_PADDING * 2,
			static_cast<int>(std::ceilf(
								 static_cast<float>(gridSize.second) *
								 cellSize)) + TMP_PADDING * 2
			)),
	_topLeftCell(std::make_pair(static_cast<float>(TMP_PADDING),
								static_cast<float>(TMP_PADDING)))
{
	if (cellSize < 3.f || gridSize.first < 1 || gridSize.second < 1)
		throw std::invalid_argument("Grid attributes invalid");
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		throw std::runtime_error("Could not init glfw");
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	_win = glfwCreateWindow(_winSize.first, _winSize.second, "Nibbler",
							NULL, NULL);
	if (!_win)
	{
		glfwTerminate();
		throw std::runtime_error("Could not create glfw window");
	}
	// glfwMakeContextCurrent(_win); //useless?
	// glfwSwapInterval(1); //useless?
	glfwSetKeyCallback(_win, key_callback);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(.0f, static_cast<float>(_winSize.first),
			static_cast<float>(_winSize.second), .0f,
			-cellSize, cellSize);
	glEnable(GL_DEPTH_TEST);
	// gluLookAt(3,3,3,0,0,0,0,0,1); // to test	
	std::cout << "[Window](std::pair<int, int>,float) Ctor called" << std::endl;
	return ;
}

// * DESTRUCTORS ************************************************************ //
Window::~Window()
{
	glfwDestroyWindow(_win);
	glfwTerminate();
	std::cout << "[Window]() Dtor called" << std::endl;
	return ;
}

// * OPERATORS ************************************************************** //
// * GETTERS **************************************************************** //
// * SETTERS **************************************************************** //
// * MEMBER FUNCTIONS / METHODS ********************************************* //
void						Window::_put_grid(void) const
{
	int		i;

	glBegin(GL_LINES);
	glColor3f(1.f, 0.f, 0.f);
	i = 0;
	for (float y = _topLeftCell.second; i <= _tmpGridSize.second;
		 i++, y += _cellSize)
	{
		glVertex3f(_topLeftCell.first, y, 0.f);
		glVertex3f(_winSize.first - _topLeftCell.first, y, 0.f);
	}
	i = 0;
	for (float x = _topLeftCell.first; i <= _tmpGridSize.first;
		 i++, x += _cellSize)
	{
		glVertex3f(x, _topLeftCell.second, 0.f);
		glVertex3f(x, _winSize.second - _topLeftCell.second, 0.f);		
	}	
	glEnd();
	return ;
}

static float				getRandRange(float selfDelta = 0.f)
{
	float randRange = fmod(glfwGetTime() + selfDelta, 3.f) / 1.5f;

	if (randRange < 1.f)
		return (randRange - 0.5f);
	return (1.f - randRange + 0.5f);
}

void						Window::draw(void) const
{
	// float randRange; //useless?
	// int width, height; //useless?

	// glfwGetFramebufferSize(_win, &width, &height); //useless?
	// randRange = width / static_cast<float>(height); //useless?
	// glViewport(0, 0, width, height); //useless?
	// GLKMatrix4MakePerspective(70,(double)640/480,1,1000);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	glMatrixMode(GL_MODELVIEW); //useless?
	glLoadIdentity();
	// _put_grid();

	static float rangesDelta[] = {
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f,
		static_cast<float>(std::rand() % 200) / 100.f
	};
	for (int i = 1; i < 10 ; i++)
	{
		_putSnakeChunk(
			std::make_pair(1, i),
			std::make_pair(1, i - 1), 65.f + 20.f * getRandRange(rangesDelta[i - 1]),
			std::make_pair(1, i + 1), 65.f + 20.f * getRandRange(rangesDelta[i])
			);
		i++;
		_putSnakeChunk(
			std::make_pair(1, i),
			std::make_pair(1, i - 1), 65.f + 20.f * getRandRange(rangesDelta[i - 1]),
			std::make_pair(1, i + 1), 65.f + 20.f * getRandRange(rangesDelta[i]),
			std::make_tuple(0.f, 0.f, 1.f), std::make_tuple(0.f, 1.f, 0.f)
			);
	}
	int i = 5;
	_putSnakeChunk(
		std::make_pair(4, i),
		std::make_pair(4, i + 1), 65.f + 20.f * getRandRange(rangesDelta[i + 1]),
		std::make_pair(4, i - 1), 65.f + 20.f * getRandRange(rangesDelta[i])
		);
	i--;
	_putSnakeChunk(
		std::make_pair(4, i),
		std::make_pair(4, i + 1), 65.f + 20.f * getRandRange(rangesDelta[i + 1]),
		std::make_pair(4, i - 1), 65.f + 20.f * getRandRange(rangesDelta[i]),
		std::make_tuple(0.f, 0.f, 1.f), std::make_tuple(0.f, 1.f, 0.f)
		);

	i = 5;
	_putSnakeChunk(
		std::make_pair(i, 1),
		std::make_pair(i + 1, 1), 65.f + 20.f * getRandRange(rangesDelta[i + 1]),
		std::make_pair(i - 1, 1), 65.f + 20.f * getRandRange(rangesDelta[i])
		);
	i--;
	_putSnakeChunk(
		std::make_pair(i, 1),
		std::make_pair(i + 1, 1), 65.f + 20.f * getRandRange(rangesDelta[i + 1]),
		std::make_pair(i - 1, 1), 65.f + 20.f * getRandRange(rangesDelta[i]),
		std::make_tuple(0.f, 0.f, 1.f), std::make_tuple(0.f, 1.f, 0.f)
		);

	i = 7;
	_putSnakeChunk(
		std::make_pair(i, 3),
		std::make_pair(i - 1, 3), 65.f + 20.f * getRandRange(rangesDelta[i - 1]),
		std::make_pair(i + 1, 3), 65.f + 20.f * getRandRange(rangesDelta[i])
		);
	i++;
	_putSnakeChunk(
		std::make_pair(i, 3),
		std::make_pair(i - 1, 3), 65.f + 20.f * getRandRange(rangesDelta[i - 1]),
		std::make_pair(i + 1, 3), 65.f + 20.f * getRandRange(rangesDelta[i]),
		std::make_tuple(0.f, 0.f, 1.f), std::make_tuple(0.f, 1.f, 0.f)
		);


	glFlush(); //remove ?
	glfwSwapBuffers(_win);
	glfwPollEvents();
	return ;
}
bool						Window::windowShouldClose(void) const
{
	return (glfwWindowShouldClose(_win));
}

// * NESTED_CLASSES ********************************************************* //
