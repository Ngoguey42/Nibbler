
#ifndef VERTEX_CLASS_HPP
# define VERTEX_CLASS_HPP

# include <iostream>

namespace ftce //ft_ConstExpr
{
class Vertex
{
public:
	// * CTORS / DTORS ************** //
	constexpr Vertex();
	constexpr Vertex(float x, float y);
	constexpr Vertex(float x, float y, float z);
	constexpr Vertex(Vertex const &src);
	
	// * OPERATORS ****************** //
	constexpr Vertex			&operator=(Vertex const &rhs);
	constexpr Vertex			&operator*=(float m);
	
	constexpr Vertex			&set(float x, float y, float z);
	
	// * ATTRIBUTES ***************** //
	float						x;
	float						y;
	float						z;
protected:
private:
};

#include "Vertex.class.tpp"
};
/*
std::ostream					&operator<<(std::ostream &o, ftce::Vertex const &rhs)
{
	return (o << "(" << rhs.x << "/" << rhs.y << ")");
}
*/

#endif // *************************************** VERTEX_CLASS_HPP //
