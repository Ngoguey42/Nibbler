
#ifndef FTVERTEX_CLASS_HPP
# define FTVERTEX_CLASS_HPP

# include <iostream>

class FtVertex
{
public:
	// * CTORS / DTORS ************** //
	constexpr FtVertex();
	constexpr FtVertex(float x, float y);
	constexpr FtVertex(FtVertex const &src);
	
	// * OPERATORS ****************** //
	constexpr FtVertex			&operator=(FtVertex const &rhs);
	
	// * ATTRIBUTES ***************** //
	float						x;
	float						y;
protected:
private:
};
std::ostream					&operator<<(std::ostream &o, FtVertex const &rhs);

#include "FtVertex.class.tpp"

#endif // *************************************** FTVERTEX_CLASS_HPP //
