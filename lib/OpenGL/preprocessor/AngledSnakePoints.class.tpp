// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AngledSnakePoints.class.cpp                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/11 08:57:38 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/11 14:34:40 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AngledSnakePoints.class.hpp"

// * CONSTRUCTORS *********************************************************** //
constexpr AngledSnakePoints::AngledSnakePoints() :
	leftBranchIntersection(),
	leftBranchInPoints(),
	leftBranchInLastIndex(0),
	leftBranchOutPoints(),
	leftBranchOutLastIndex(0),

	middleBranchIntersection(),
	middleBranchInPoints(),
	middleBranchInLastIndex(0),
	middleBranchOutPoints(),
	middleBranchOutLastIndex(0),

	rightBranchIntersection(),
	rightBranchInPoints(),
	rightBranchInLastIndex(0),
	rightBranchOutPoints(),
	rightBranchOutLastIndex(0)
{
	return ;
}

// * MEMBER FUNCTIONS / METHODS ********************************************* //
constexpr int				AngledSnakePoints::init(float const initRatio)
{
	float	curphase(ftce::fmod(initRatio, 1.f));
	
	// Setting this->leftBranchInPoints		//
	// curphase = ;
	for (int j = 0; j < MAX_POINTS_BEFORE_ANGLE; j++)
	{
		this->leftBranchInPoints[j] = t_vertexf(
			(ftce::cos((0.5f + curphase) * M_PI * 2.f) + 1.f) /
			2.f * SNAKE_WIDTH_INV + SNAKE_WIDTH,
			j * (TRIANGLES_DISTANCE / CHUNK_SIZEF));
		this->rightBranchInPoints[j] = t_vertexf(
			this->leftBranchInPoints[j].x - SNAKE_WIDTH,
			this->leftBranchInPoints[j].y);
		this->middleBranchInPoints[j] = t_vertexf(
			this->leftBranchInPoints[j].x - SNAKE_WIDTH_HALF,
			this->leftBranchInPoints[j].y);
		curphase = ftce::fmod(curphase + PHASE_PER_TRIANGLE, 1.f);
	}
	// Setting this->leftBranchOutPoints		//
	curphase = ftce::fmod(initRatio + PHASE_PER_CHUNK, 1.f);
	for (int j = 0; j < MAX_POINTS_BEFORE_ANGLE; j++)
	{
		this->leftBranchOutPoints[j] = t_vertexf(
			1.f - j * (TRIANGLES_DISTANCE / CHUNK_SIZEF),
			SNAKE_WIDTH_INV - (ftce::cos((0.5f + curphase) * M_PI * 2.f) + 1.f) /
			2.f * SNAKE_WIDTH_INV);
		this->rightBranchOutPoints[j] = t_vertexf(
			this->leftBranchOutPoints[j].x,
			this->leftBranchOutPoints[j].y + SNAKE_WIDTH);
		this->middleBranchOutPoints[j] = t_vertexf(
			this->leftBranchOutPoints[j].x,
			this->leftBranchOutPoints[j].y + SNAKE_WIDTH_HALF);
		curphase = ftce::fmod(curphase - PHASE_PER_TRIANGLE, 1.f);
	}
	for (int i = 0; i <= this->leftBranchInPoints.getLastIndex(); i++)
		this->leftBranchInPoints[i] *= CHUNK_SIZEF;
	for (int i = 0; i <= this->leftBranchOutPoints.getLastIndex(); i++)
		this->leftBranchOutPoints[i] *= CHUNK_SIZEF;
	for (int i = 0; i <= this->middleBranchInPoints.getLastIndex(); i++)
		this->middleBranchInPoints[i] *= CHUNK_SIZEF;
	for (int i = 0; i <= this->middleBranchOutPoints.getLastIndex(); i++)
		this->middleBranchOutPoints[i] *= CHUNK_SIZEF;
	for (int i = 0; i <= this->rightBranchInPoints.getLastIndex(); i++)
		this->rightBranchInPoints[i] *= CHUNK_SIZEF;
	for (int i = 0; i <= this->rightBranchOutPoints.getLastIndex(); i++)
		this->rightBranchOutPoints[i] *= CHUNK_SIZEF;
	this->leftBranchIntersection = this->calcIntersection(
		this->leftBranchInPoints, this->leftBranchOutPoints,
		this->leftBranchInLastIndex, this->leftBranchOutLastIndex);
	this->rightBranchIntersection = this->calcIntersection(
		this->rightBranchInPoints, this->rightBranchOutPoints,
		this->rightBranchInLastIndex, this->rightBranchOutLastIndex);
	this->middleBranchIntersection = this->calcIntersection(
		this->middleBranchInPoints, this->middleBranchOutPoints,
		this->middleBranchInLastIndex, this->middleBranchOutLastIndex);
	return (0);
}

constexpr AngledSnakePoints::t_vertexf				AngledSnakePoints::calcIntersection(
	t_snakepoints const &inPoints, t_snakepoints const &outPoints,
	size_t &inLastIndex, size_t &outLastIndex)
{
	float	bestDistance = CHUNK_SIZEF;
	// int		i = 0, j = 0;

	// for (auto const &w : inPoints)
	for (int i = 0; i <= inPoints.getLastIndex(); i++)
	{
		auto const &w = inPoints[i];
		// j = 0;
		// for (auto const &x : outPoints)
		for (int j = 0; j <= outPoints.getLastIndex(); j++)
		{
			auto const &x = outPoints[j];
			float const	dx = w.x - x.x;
			float const	dy = w.y - x.y;
			float const	distance = sqrtf(dx * dx + dy * dy);
			
			if (bestDistance > distance)
			{
				bestDistance = distance;
				inLastIndex = i;
				outLastIndex = j;
			}
			// j++;
		}
		// i++;
	}
	return (setBranchIntersection(inPoints[inLastIndex],
								  outPoints[outLastIndex]));
}

constexpr AngledSnakePoints::t_vertexf				AngledSnakePoints::setBranchIntersection(
	t_vertexf const &a, t_vertexf const &b)
{
	return (t_vertexf(
		b.x + (a.x - b.x) / 2,
		b.y + (a.y - b.y) / 2));
}
