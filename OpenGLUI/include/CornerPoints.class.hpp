// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   CornerPoints.class.hpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/15 09:07:05 by ngoguey           #+#    #+#             //
//   Updated: 2015/06/01 16:05:59 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CORNERPOINTS_CLASS_HPP
# define CORNERPOINTS_CLASS_HPP

//# include <string>
//# include <iostream>
//# include <stdexcept>
#include <iostream>

# include "OpenGLLib.h"
# include "ftconstexpr/Vertex.hpp"
# include "ftconstexpr/Array.hpp"
# include "AngledSnakePoints.class.hpp"

// template <size_t S1 = MAX_POINTS_PER_GROUP,
// size_t S2 = MAX_POINTS_PER_GROUP,
// size_t S3 = MAX_POINTS_PER_GROUP,
// size_t S4 = MAX_POINTS_PER_GROUP,
// size_t S5 = MAX_POINTS_PER_GROUP,
// size_t S6 = MAX_POINTS_PER_GROUP>

template <size_t S1,
size_t S2,
size_t S3,
size_t S4,
size_t S5,
size_t S6>
class CornerPoints
{
public:
	// * STATICS ******************** //
	// * CTORS / DTORS ************** //
	constexpr CornerPoints();
	~CornerPoints() = default;
	
	// * OPERATORS ****************** //
	constexpr CornerPoints			&operator=(CornerPoints const &rhs);
	constexpr operator bool() { return true; } //debug
	constexpr operator bool() const { return true; } //debug
	
	// * MEMBER FUNCTIONS / METHODS * //
	constexpr float				init(float ratio, bool sinistro);
	
	// * ATTRIBUTES ***************** //
	ftce::Array<ftce::Vertex<>, S1>	leftStrip1;
	ftce::Array<ftce::Vertex<>, S2>	leftFan;
	ftce::Array<ftce::Vertex<>, S3>	leftStrip2;
	ftce::Array<ftce::Vertex<>, S4>	rightStrip1;
	ftce::Array<ftce::Vertex<>, S5>	rightFan;
	ftce::Array<ftce::Vertex<>, S6>	rightStrip2;
	
protected:
private:
	constexpr CornerPoints(CornerPoints const &src);

};
//std::ostream					&operator<<(std::ostream &o, CornerPoints const &rhs);

# include "CornerPoints.class.tpp"

#endif // *************************************** CORNERPOINTS_CLASS_HPP //
