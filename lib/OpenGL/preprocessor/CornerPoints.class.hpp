
#ifndef CORNERPOINTS_CLASS_HPP
# define CORNERPOINTS_CLASS_HPP

//# include <string>
//# include <iostream>
//# include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>
#include <vector>

# include "utils.hpp"
# include "FtVertex.class.hpp"
# include "FtArray.class.hpp"

// # include "OpenGLLib.h"


template <size_t S1 = MAX_POINTS_PER_GROUP,	\
size_t S2 = MAX_POINTS_PER_GROUP,			\
size_t S3 = MAX_POINTS_PER_GROUP,			\
size_t S4 = MAX_POINTS_PER_GROUP,			\
size_t S5 = MAX_POINTS_PER_GROUP,			\
size_t S6 = MAX_POINTS_PER_GROUP>
class CornerPoints
{
public:
	// constexpr CornerPoints(std::array<t_vertexf, N> leftStrip1);
	// void							describe(void) const;
	// constexpr CornerPoints(CornerPoints const &src);
	constexpr CornerPoints();
	constexpr CornerPoints			&operator=(CornerPoints const &rhs);
	
	constexpr float				init(float ratio, bool sinistro);
	
	constexpr operator bool() { return true; } //debug
	constexpr operator bool() const { return true; } //debug

	int i;
	FtArray<t_vertexf, S1>	leftStrip1;
	FtArray<t_vertexf, S2>	leftFan;
	FtArray<t_vertexf, S3>	leftStrip2;
	FtArray<t_vertexf, S4>	rightStrip1;
	FtArray<t_vertexf, S5>	rightFan;
	FtArray<t_vertexf, S6>	rightStrip2;
	
protected:
private:
	constexpr CornerPoints(CornerPoints const &src);

};
//std::ostream					&operator<<(std::ostream &o, CornerPoints const &rhs);

# include "CornerPoints.class.tpp"
#endif // *************************************** CORNERPOINTS_CLASS_HPP //
