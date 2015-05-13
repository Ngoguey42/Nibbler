
#ifndef CORNERPOINTS_CLASS_HPP
# define CORNERPOINTS_CLASS_HPP

//# include <string>
//# include <iostream>
//# include <stdexcept>
#include <iostream>

# include "utils.hpp"
# include "Vertex.class.hpp"
# include "Array.class.hpp"
// # include "AngledSnakePoints.class.hpp"

// # include "OpenGLLib.h"

template <size_t S1 = MAX_POINTS_PER_GROUP,
size_t S2 = MAX_POINTS_PER_GROUP,
size_t S3 = MAX_POINTS_PER_GROUP,
size_t S4 = MAX_POINTS_PER_GROUP,
size_t S5 = MAX_POINTS_PER_GROUP,
size_t S6 = MAX_POINTS_PER_GROUP>
class CornerPoints
{
public:
	// * CTORS / DTORS ************** //
	constexpr CornerPoints();
	
	// * OPERATORS ****************** //
	constexpr CornerPoints			&operator=(CornerPoints const &rhs);
	constexpr operator bool() { return true; } //debug
	constexpr operator bool() const { return true; } //debug
	
	// * MEMBER FUNCTIONS / METHODS * //
	constexpr float				init(float ratio, bool sinistro);
	
	// * ATTRIBUTES ***************** //
	ftce::Array<ftce::Vertex, S1>	leftStrip1;
	ftce::Array<ftce::Vertex, S2>	leftFan;
	ftce::Array<ftce::Vertex, S3>	leftStrip2;
	ftce::Array<ftce::Vertex, S4>	rightStrip1;
	ftce::Array<ftce::Vertex, S5>	rightFan;
	ftce::Array<ftce::Vertex, S6>	rightStrip2;
	
protected:
private:
	constexpr CornerPoints(CornerPoints const &src);

};
//std::ostream					&operator<<(std::ostream &o, CornerPoints const &rhs);

# include "CornerPoints.class.tpp"

#endif // *************************************** CORNERPOINTS_CLASS_HPP //
