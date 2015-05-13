
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
	constexpr Vertex(Vertex const &src);
	
	// * OPERATORS ****************** //
	constexpr Vertex			&operator=(Vertex const &rhs);
	
	// * ATTRIBUTES ***************** //
	float						x;
	float						y;
protected:
private:
};
std::ostream					&operator<<(std::ostream &o, Vertex const &rhs);

#include "Vertex.class.tpp"
};

#endif // *************************************** VERTEX_CLASS_HPP //
