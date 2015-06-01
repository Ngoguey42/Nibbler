/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AngledSnakePoints.class.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 08:56:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/01 15:31:14 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANGLEDSNAKEPOINTS_CLASS_HPP
# define ANGLEDSNAKEPOINTS_CLASS_HPP

//# include <string>
//# include <iostream>
//# include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>

# include "OpenGLLib.h"
# include "ftconstexpr/Vertex.hpp"
# include "ftconstexpr/Array.hpp"

#define ARRAY_CUSTOM_SIZE												\
	ftce::Array<CornerPoints<S1,S2,S3,S4,S5,S6>, NUM_PRECALC_POINTS>
#define ARRAY_DEFAULT_SIZE							\
	ftce::Array<CornerPoints<>, NUM_PRECALC_POINTS>

class AngledSnakePoints
{
public:
	// * STATICS ******************** //
	static constexpr ftce::Array<size_t, 6>	calcPointsArraySize(bool sinistro);
	template <size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6>
	static constexpr ARRAY_CUSTOM_SIZE		buildPointsArray(bool sinistro);
	
	// * CTORS / DTORS ************** //
	constexpr AngledSnakePoints();
	constexpr AngledSnakePoints(AngledSnakePoints const &src);
	constexpr AngledSnakePoints			&operator=(AngledSnakePoints const &rhs);
	constexpr operator bool() { return true; } //debug
	constexpr operator bool() const { return true; } //debug
	~AngledSnakePoints(void) = default;
	
	
	// typedef std::pair<float, float>                         t_vertexf;
	// typedef std::array<t_vertexf, MAX_POINTS_BEFORE_ANGLE>  t_snakepoints;

	constexpr int		init(float const initRatio, bool sinistro);

	typedef ftce::Vertex<>                        t_vertexf;
	typedef ftce::Array<t_vertexf, MAX_POINTS_BEFORE_ANGLE>  t_snakepoints;

	t_vertexf           leftBranchIntersection;
	t_snakepoints       leftBranchInPoints;
	size_t              leftBranchInLastIndex;
	t_snakepoints       leftBranchOutPoints;
	size_t              leftBranchOutLastIndex;

	t_vertexf           middleBranchIntersection;
	t_snakepoints       middleBranchInPoints;
	size_t              middleBranchInLastIndex;
	t_snakepoints       middleBranchOutPoints;
	size_t              middleBranchOutLastIndex;

	t_vertexf           rightBranchIntersection;
	t_snakepoints       rightBranchInPoints;
	size_t              rightBranchInLastIndex;
	t_snakepoints       rightBranchOutPoints;
	size_t              rightBranchOutLastIndex;
	
protected:
private:

	constexpr t_vertexf				setBranchIntersection(t_vertexf const &a,
														  t_vertexf const &b);
	constexpr t_vertexf				calcIntersection(
		t_snakepoints const &inPoints, t_snakepoints const &outPoints,
		size_t &inLastIndex, size_t &outLastIndex);
	
};

# include "CornerPoints.class.hpp"
# include "AngledSnakePoints.class.tpp"

# undef ARRAY_CUSTOM_SIZE
# undef ARRAY_DEFAULT_SIZE

#endif // *************************************** ANGLEDSNAKEPOINTS_CLASS_HPP //
