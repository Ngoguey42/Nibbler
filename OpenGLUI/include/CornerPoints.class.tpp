// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   CornerPoints.class.tpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/15 09:07:00 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/29 15:33:20 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#define DY_CLASS CornerPoints<S1,S2,S3,S4,S5,S6>
#define TEMPLATE_ARGS													\
	template <size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6>

// * CONSTRUCTORS *********************************************************** //
TEMPLATE_ARGS
constexpr DY_CLASS::CornerPoints() :
	leftStrip1(),
	leftFan(),
	leftStrip2(),
	rightStrip1(),
	rightFan(),
	rightStrip2()
{
	return ;
}

// * OPERATORS ************************************************************** //
TEMPLATE_ARGS
constexpr DY_CLASS		&DY_CLASS::operator=(DY_CLASS const &rhs)
{
	this->leftStrip1 = rhs.leftStrip1;
	this->leftFan = rhs.leftFan;
	this->leftStrip2 = rhs.leftStrip2;
	this->rightStrip1 = rhs.rightStrip1;
	this->rightFan = rhs.rightFan;
	this->rightStrip2 = rhs.rightStrip2;
	return (*this);
}

// * MEMBER FUNCTIONS / METHODS ********************************************* //

template <size_t S>
static constexpr int		savePoints(
	size_t limiterIndex, ftce::Vertex<> intersection, float z1, float z2,
	ftce::Array<ftce::Vertex<>, S>		&dest,
	AngledSnakePoints::t_snakepoints	const &array1,
	AngledSnakePoints::t_snakepoints	const &array2
	)
{
	int	index = 0;

	if (limiterIndex > 0)
	{
		dest[index++].set(array1[0].x, array1[0].y, z1);
		for (size_t i = 0; i < limiterIndex;)
		{					
			dest[index++].set(array2[i].x, array2[i].y, z2);
			i++;
			dest[index++].set(array1[i].x, array1[i].y, z1);
		}
		dest[index++].set(intersection.x, intersection.y, z2);
	}	
	return (0);
}

template <size_t S>
static constexpr int		savePoints(
	size_t limiterIndex, bool, ftce::Vertex<> intersection, float z1, float z2,
	ftce::Array<ftce::Vertex<>, S>		&dest,
	AngledSnakePoints::t_snakepoints	const &array1,
	AngledSnakePoints::t_snakepoints	const &array2
	)
{
	int	index = 0;

	if (limiterIndex > 0)
	{
		dest[index++].set(intersection.x, intersection.y, z1);
		for (size_t i = limiterIndex;;i--)
		{
			dest[index++].set(array1[i].x, array1[i].y, z2);
			dest[index++].set(array2[i].x, array2[i].y, z1);
			if (i == 0)
				break ;
		}
	}
	return (0);
}

template <size_t S>
static constexpr int		savePoints(
	ftce::Array<ftce::Vertex<>, S>		&dest,
	size_t startIndex1, size_t limiterIndex1, ftce::Vertex<> intersection1,
	float z1, AngledSnakePoints::t_snakepoints	const &array1,
	size_t startIndex2, int limiterIndex2, ftce::Vertex<> intersection2,
	float z2, AngledSnakePoints::t_snakepoints	const &array2
	)
{
	int	index = 0;

	dest[index++].set(intersection1.x, intersection1.y, z1);
	for (size_t j = startIndex1; j < limiterIndex1; j++)
		dest[index++].set(array1[j].x, array1[j].y, z2);
	dest[index++].set(intersection2.x, intersection2.y, z2);
	for (int j = startIndex2 - 1; j >= limiterIndex2; j--)
		dest[index++].set(array2[j].x, array2[j].y, z2);
	return (0);
}

TEMPLATE_ARGS
constexpr float				DY_CLASS::init(float ratio, bool sinistro)
{
	AngledSnakePoints		points;
	float					z(SNAKE_HEIGHT);

	points.init(ratio, sinistro);
	if (sinistro)
	{
		savePoints<S1>(points.leftBranchInLastIndex,
					   points.leftBranchIntersection, z, 0.f,
					   this->leftStrip1,
					   points.middleBranchInPoints,
					   points.leftBranchInPoints);
		savePoints<S2>(
			this->leftFan,
			points.leftBranchInLastIndex, points.middleBranchInLastIndex,
			points.leftBranchIntersection, 0.f, points.middleBranchInPoints,
			points.middleBranchOutLastIndex, points.leftBranchOutLastIndex,
			points.middleBranchIntersection, z, points.middleBranchOutPoints);
		savePoints<S3>(points.leftBranchOutLastIndex, true,
					   points.leftBranchIntersection, 0.f, z,
					   this->leftStrip2,
					   points.middleBranchOutPoints,
					   points.leftBranchOutPoints);
		savePoints<S4>(points.middleBranchInLastIndex,
					   points.middleBranchIntersection, 0.f, z,
					   this->rightStrip1,
					   points.rightBranchInPoints,
					   points.middleBranchInPoints);
		savePoints<S5>(
			this->rightFan,
			points.middleBranchInLastIndex, points.rightBranchInLastIndex,
			points.middleBranchIntersection, z, points.rightBranchInPoints,
			points.rightBranchOutLastIndex, points.middleBranchOutLastIndex,
			points.rightBranchIntersection, 0.f, points.rightBranchOutPoints);
		savePoints<S6>(points.middleBranchOutLastIndex, true,
					   points.middleBranchIntersection, z, 0.f,
					   this->rightStrip2,
					   points.rightBranchOutPoints,
					   points.middleBranchOutPoints);
	}
	else
	{
		savePoints<S1>(points.middleBranchInLastIndex,
					   points.middleBranchIntersection, 0.f, z,
					   this->leftStrip1,
					   points.leftBranchInPoints,
					   points.middleBranchInPoints);
		savePoints<S2>(
			this->leftFan,
			points.middleBranchInLastIndex, points.leftBranchInLastIndex,
			points.middleBranchIntersection, z, points.leftBranchInPoints,
			points.leftBranchOutLastIndex, points.middleBranchOutLastIndex,
			points.leftBranchIntersection, 0.f, points.leftBranchOutPoints);
		savePoints<S3>(points.middleBranchOutLastIndex, true,
					   points.middleBranchIntersection, z, 0.f,
					   this->leftStrip2,
					   points.leftBranchOutPoints,
					   points.middleBranchOutPoints);
		// return (ratio);
		savePoints<S4>(points.rightBranchInLastIndex,
					   points.rightBranchIntersection, z, 0.f,
					   this->rightStrip1,
					   points.middleBranchInPoints,
					   points.rightBranchInPoints);
		savePoints<S5>(
			this->rightFan,
			points.rightBranchInLastIndex, points.middleBranchInLastIndex,
			points.rightBranchIntersection, 0.f, points.middleBranchInPoints,
			points.middleBranchOutLastIndex, points.rightBranchOutLastIndex,
			points.middleBranchIntersection, z, points.middleBranchOutPoints);
		savePoints<S6>(points.rightBranchOutLastIndex, true,
					   points.rightBranchIntersection, 0.f, z,
					   this->rightStrip2,
					   points.middleBranchOutPoints,
					   points.rightBranchOutPoints);
	}
	
	return (ratio);
}

#undef DY_CLASS
#undef TEMPLATE_ARGS
