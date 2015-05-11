// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AngledSnakePoints.class.cpp                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/11 08:57:38 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/11 10:37:34 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//#include <iostream>
#include "AngledSnakePoints.class.hpp"

// * STATICS **************************************************************** //
// * CONSTRUCTORS *********************************************************** //
AngledSnakePoints::AngledSnakePoints()
{
	// std::cout << "[AngledSnakePoints]() Ctor called" << std::endl;
	return ;
}

// * DESTRUCTORS ************************************************************ //
AngledSnakePoints::~AngledSnakePoints()
{
	// std::cout << "[AngledSnakePoints]() Dtor called" << std::endl;
	return ;
}

// * OPERATORS ************************************************************** //
// * GETTERS **************************************************************** //
// * SETTERS **************************************************************** //
// * MEMBER FUNCTIONS / METHODS ********************************************* //

void				AngledSnakePoints::init(float const initRatio)
{
	float	curphase;
	// int		i, j;
	
	// Setting this->leftBranchInPoints		//
	curphase = fmodf(initRatio, 1.f);
	for (int j = 0; j < MAX_POINTS_BEFORE_ANGLE; j++)
	{
		this->leftBranchInPoints[j] = std::make_pair(
			(cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) /
			2.f * SNAKE_WIDTH_INV + SNAKE_WIDTH,
			j * (TRIANGLES_DISTANCE / CHUNK_SIZEF));
		std::cout << "(" << this->leftBranchInPoints[j].first << "/" << this->leftBranchInPoints[j].second << ") ";
		this->rightBranchInPoints[j] = std::make_pair(
			this->leftBranchInPoints[j].first - SNAKE_WIDTH,
			this->leftBranchInPoints[j].second);
		this->middleBranchInPoints[j] = std::make_pair(
			this->leftBranchInPoints[j].first - SNAKE_WIDTH_HALF,
			this->leftBranchInPoints[j].second);
		curphase = fmodf(curphase + PHASE_PER_TRIANGLE, 1.f);
	}
	std::cout << std::endl;
	// Setting this->leftBranchOutPoints		//
	curphase = fmodf(initRatio + PHASE_PER_CHUNK, 1.f);
	for (int j = 0; j < MAX_POINTS_BEFORE_ANGLE; j++)
	{
		this->leftBranchOutPoints[j] = std::make_pair(
			1.f - j * (TRIANGLES_DISTANCE / CHUNK_SIZEF),
			SNAKE_WIDTH_INV - (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) /
			2.f * SNAKE_WIDTH_INV);
		std::cout << "(" << this->leftBranchOutPoints[j].first << "/" << this->leftBranchOutPoints[j].second << ") ";
		this->rightBranchOutPoints[j] = std::make_pair(
			this->leftBranchOutPoints[j].first,
			this->leftBranchOutPoints[j].second + SNAKE_WIDTH);
		this->middleBranchOutPoints[j] = std::make_pair(
			this->leftBranchOutPoints[j].first,
			this->leftBranchOutPoints[j].second + SNAKE_WIDTH_HALF);
		curphase = fmodf(curphase - PHASE_PER_TRIANGLE + 1.f, 1.f);
	}
	for (auto &v : this->leftBranchInPoints)
	{v.first *= CHUNK_SIZEF; v.second *= CHUNK_SIZEF;}
	for (auto &v : this->leftBranchOutPoints)
	{v.first *= CHUNK_SIZEF; v.second *= CHUNK_SIZEF;}
	for (auto &v : this->middleBranchInPoints)
	{v.first *= CHUNK_SIZEF; v.second *= CHUNK_SIZEF;}
	for (auto &v : this->middleBranchOutPoints)
	{v.first *= CHUNK_SIZEF; v.second *= CHUNK_SIZEF;}
	for (auto &v : this->rightBranchInPoints)
	{v.first *= CHUNK_SIZEF; v.second *= CHUNK_SIZEF;}
	for (auto &v : this->rightBranchOutPoints)
	{v.first *= CHUNK_SIZEF; v.second *= CHUNK_SIZEF;}
	std::cout << std::endl;
	this->calcIntersection(
		this->leftBranchInPoints, this->leftBranchOutPoints,
		this->leftBranchInLastIndex, this->leftBranchOutLastIndex,
		this->leftBranchIntersection);
	this->calcIntersection(
		this->rightBranchInPoints, this->rightBranchOutPoints,
		this->rightBranchInLastIndex, this->rightBranchOutLastIndex,
		this->rightBranchIntersection);
	this->calcIntersection(
		this->middleBranchInPoints, this->middleBranchOutPoints,
		this->middleBranchInLastIndex, this->middleBranchOutLastIndex,
		this->middleBranchIntersection);
	// Setting this->leftBranchInLastIndex		//
	// Setting this->leftBranchOutLastIndex	//
	// bestDistance = 2.f;
	// i = 0;
	// for (auto const &w : this->leftBranchInPoints)
	// {
	// j = 0;
	// for (auto const &x : this->leftBranchOutPoints)
	// {
	// float const	dx = w.first - x.first;
	// float const	dy = w.second - x.second;
	// float const	distance = sqrtf(dx * dx + dy * dy);
			
	// if (bestDistance > distance)
	// {
	// bestDistance = distance;
	// this->leftBranchInLastIndex = i;
	// this->leftBranchOutLastIndex = j;
	// }
	// j++;
	// }
	// i++;
	// }
	// Setting this->leftBranchIntersection		//
	// this->setBranchIntersection(this->leftBranchInPoints[this->leftBranchInLastIndex],
	// this->leftBranchOutPoints[this->leftBranchOutLastIndex]);
	
	return ;
}

void				AngledSnakePoints::calcIntersection(t_snakepoints const &inPoints,
														t_snakepoints const &outPoints,
														size_t &inLastIndex,
														size_t &outLastIndex,
														t_vertexf &intersection)
{
	float	bestDistance = CHUNK_SIZEF;
	int		i = 0, j;

	for (auto const &w : inPoints)
	{
		j = 0;
		for (auto const &x : outPoints)
		{
			float const	dx = w.first - x.first;
			float const	dy = w.second - x.second;
			float const	distance = sqrtf(dx * dx + dy * dy);
			
			if (bestDistance > distance)
			{
				bestDistance = distance;
				inLastIndex = i;
				outLastIndex = j;
			}
			j++;
		}
		i++;
	}
	this->setBranchIntersection(intersection,
								inPoints[inLastIndex],
								outPoints[outLastIndex]);
	return ;
}

void				AngledSnakePoints::setBranchIntersection(
	t_vertexf &intersection, t_vertexf const &a, t_vertexf const &b)
{
	intersection = std::make_pair(
		b.first + (a.first - b.first) / 2,
		b.second + (a.second - b.second) / 2);
	return ;
}

void				AngledSnakePoints::describe(void)
{
	std::cout << "Left i/o(" << leftBranchInLastIndex << "-";
	std::cout << "" << leftBranchOutLastIndex << ") ";
	std::cout << "i(" << leftBranchIntersection.first << "/"
			  << leftBranchIntersection.second << ")  ";
	std::cout << "Middle i/o(" << middleBranchInLastIndex << "-";
	std::cout << "" << middleBranchOutLastIndex << ") ";
	std::cout << "i(" << middleBranchIntersection.first << "/"
			  << middleBranchIntersection.second << ")  ";
	std::cout << "Right i/o(" << rightBranchInLastIndex << "-";
	std::cout << "" << rightBranchOutLastIndex << ") ";
	std::cout << "i(" << rightBranchIntersection.first << "/"
			  << rightBranchIntersection.second << ")  ";
		
	std::cout << std::endl;
	return ;
}
void				AngledSnakePoints::describePoints(void)
{
	std::cout << "x	y		x	y		x	y" << std::endl;
	for (size_t i = 0; i < this->leftBranchInPoints.size(); i++)
	{
		{
			auto const &v = this->leftBranchInPoints[i];
			std::cout << v.first << "\t-" << v.second << "\t\t";
		}
		{
			auto const &v = this->rightBranchInPoints[i];
			std::cout << v.first << "\t-" << v.second << "\t\t";
		}
		{
			auto const &v = this->middleBranchInPoints[i];
			std::cout << v.first << "\t-" << v.second << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "x	y		x	y		x	y" << std::endl;
	for (size_t i = 0; i < this->leftBranchInPoints.size(); i++)
	{
		{
			auto const &v = this->leftBranchOutPoints[i];
			std::cout << v.first << "\t-" << v.second << "\t\t";
		}
		{
			auto const &v = this->rightBranchOutPoints[i];
			std::cout << v.first << "\t-" << v.second << "\t\t";
		}
		{
			auto const &v = this->middleBranchOutPoints[i];
			std::cout << v.first << "\t-" << v.second << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "x	y" << std::endl;
	{
		auto const &v = this->rightBranchIntersection;
		std::cout << v.first << "\t-" << v.second << std::endl;
	}
	{
		auto const &v = this->middleBranchIntersection;
		std::cout << v.first << "\t-" << v.second << std::endl;
	}
	{
		auto const &v = this->leftBranchIntersection;
		std::cout << v.first << "\t-" << v.second << std::endl;
	}
	return ;
	for (auto const &v : this->leftBranchInPoints)
		std::cout << v.first << std::endl;
	std::cout << std::endl;
	for (auto const &v : this->leftBranchInPoints)
		std::cout << v.second << std::endl;
	std::cout << std::endl;
	for (auto const &v : this->leftBranchOutPoints)
		std::cout << v.first << std::endl;
	std::cout << std::endl;
	for (auto const &v : this->leftBranchOutPoints)
		std::cout << v.second << std::endl;
	return ;
}
