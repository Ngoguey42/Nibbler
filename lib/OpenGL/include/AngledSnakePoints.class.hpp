// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AngledSnakePoints.class.hpp                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/11 08:56:31 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/11 10:37:41 by ngoguey          ###   ########.fr       //
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

# include "OpenGLLib.h"

class AngledSnakePoints
{
public:
	AngledSnakePoints();	
	virtual ~AngledSnakePoints();

    void                init(float const initRatio);
	void                describe(void);
	void                describePoints(void);

	typedef std::pair<float, float>                         t_vertexf;
	typedef std::array<t_vertexf, MAX_POINTS_BEFORE_ANGLE>  t_snakepoints;

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
	AngledSnakePoints(AngledSnakePoints const &src);
	AngledSnakePoints			&operator=(AngledSnakePoints const &rhs);

	void                setBranchIntersection(
		t_vertexf &intersection, t_vertexf const &a, t_vertexf const &b);
	void                calcIntersection(t_snakepoints const &inPoints,
										 t_snakepoints const &outPoints,
										 size_t &inLastIndex,
										 size_t &outLastIndex,
										 t_vertexf &intersection);
	
};
//std::ostream					&operator<<(std::ostream &o, AngledSnakePoints const &rhs);

#endif // *************************************** ANGLEDSNAKEPOINTS_CLASS_HPP //
