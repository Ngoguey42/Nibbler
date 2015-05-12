
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
// template<>
class CornerPoints
{
public:
	// constexpr CornerPoints(std::array<t_vertexf, N> leftStrip1);
	// void							describe(void) const;
	// constexpr CornerPoints(CornerPoints const &src);
	constexpr CornerPoints();
	constexpr CornerPoints			&operator=(CornerPoints const &rhs);
	
	constexpr int				test(int i)
	{
		// this->_leftStrip1[0] = p;
		this->i = i;
		return 0;
	}
	
	constexpr float				init(float ratio, bool sinistro)
	{
		// this->leftStrip2[0].first = 42.f;
		// static_assert(this->leftStrip1[0].x == 0.f, "test1");
		this->leftStrip1[0].x = 2.f;
		this->leftStrip1[0].y = 3.f;
		this->leftStrip2[0].x = 42.f;
		this->leftStrip2[1].x = 42.f;
		// this->leftStrip2[0] = std::make_pair(12.f, 42.f);
		return (ratio);
	}
	
	constexpr operator bool() { return true; }
	constexpr operator bool() const { return true; }

	int i;
	FtArray<t_vertexf, MAX_POINTS_PER_POLYGON>	leftStrip1;
	FtArray<t_vertexf, MAX_POINTS_PER_POLYGON>	leftFan;
	FtArray<t_vertexf, MAX_POINTS_PER_POLYGON>	leftStrip2;
	FtArray<t_vertexf, MAX_POINTS_PER_POLYGON>	rightStrip1;
	FtArray<t_vertexf, MAX_POINTS_PER_POLYGON>	rightFan;
	FtArray<t_vertexf, MAX_POINTS_PER_POLYGON>	rightStrip2;
	
protected:
private:
	constexpr CornerPoints(CornerPoints const &src);

};
//std::ostream					&operator<<(std::ostream &o, CornerPoints const &rhs);

#include "CornerPoints.class.tpp"

#endif // *************************************** CORNERPOINTS_CLASS_HPP //
