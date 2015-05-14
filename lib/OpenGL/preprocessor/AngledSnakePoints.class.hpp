// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AngledSnakePoints.class.hpp                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/11 08:56:31 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/11 14:31:13 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ANGLEDSNAKEPOINTS_CLASS_HPP
# define ANGLEDSNAKEPOINTS_CLASS_HPP

//# include <string>
//# include <iostream>
//# include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>

# include "utils.hpp"
# include "Vertex.class.hpp"
# include "Array.class.hpp"

class AngledSnakePoints
{
public:
	constexpr AngledSnakePoints();
	constexpr AngledSnakePoints(AngledSnakePoints const &src);
	constexpr AngledSnakePoints			&operator=(AngledSnakePoints const &rhs);
	constexpr operator bool() { return true; } //debug
	constexpr operator bool() const { return true; } //debug
	
	
	// typedef std::pair<float, float>                         t_vertexf;
	// typedef std::array<t_vertexf, MAX_POINTS_BEFORE_ANGLE>  t_snakepoints;

	constexpr int		init(float const initRatio);

	typedef ftce::Vertex                        t_vertexf;
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

# include "AngledSnakePoints.class.tpp"

#endif // *************************************** ANGLEDSNAKEPOINTS_CLASS_HPP //
