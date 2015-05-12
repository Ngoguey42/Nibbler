
#ifndef FTVERTEX_CLASS_HPP
# define FTVERTEX_CLASS_HPP

//# include <string>
# include <iostream>
//# include <stdexcept>
// #include <iostream>
// #include <iomanip>
// #include <cmath>
// #include <array>
// #include <vector>

// # include "OpenGLLib.h"

class FtVertex
{
public:
	constexpr FtVertex();
	constexpr FtVertex(float x, float y);
	constexpr FtVertex(FtVertex const &src);
	constexpr FtVertex			&operator=(FtVertex const &rhs);

	float						x;
	float						y;
protected:
private:
};
std::ostream					&operator<<(std::ostream &o, FtVertex const &rhs);

#include "FtVertex.class.tpp"

#endif // *************************************** FTVERTEX_CLASS_HPP //
