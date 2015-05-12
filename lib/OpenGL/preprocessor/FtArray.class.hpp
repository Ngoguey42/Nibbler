
#ifndef FTARRAY_CLASS_HPP
# define FTARRAY_CLASS_HPP

//# include <string>
//# include <iostream>
//# include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>
#include <vector>

# include "utils.hpp"
// # include "OpenGLLib.h"

template<typename T, size_t S>
class FtArray
{
public:

	// * NESTED OBJECTS ************* //
	class iterator
	{
	public:
		iterator();
		iterator(iterator const &src);
		~iterator();
		iterator				&operator=(iterator const &rhs);
		bool					operator!=(iterator const &rhs);

		// T						&operator*(void);
		T const					&operator*(void) const;
		iterator				&operator++(void);
		// iterator				operator++(int);
		// iterator				&operator--(void);
		// iterator				operator--(int);
		void					setPtr(T const *ptr);
		// void					printAdress(void);
		
	private:
		T const					*_ptr;
		
	};

	constexpr FtArray();
	// virtual ~FtArray();
	constexpr FtArray(FtArray const &src);
	constexpr FtArray			&operator=(FtArray const &rhs);
	constexpr T					&operator[](size_t s);
	constexpr T const			&operator[](size_t s) const;
	

	// * MEMBER FUNCTIONS / METHODS * //
	constexpr size_t			getLastIndex(void) const;
	constexpr size_t			size(void) const;
	iterator					begin(void) const;
	iterator					end(void) const;
	
protected:
private:
	T							_data[S];
	size_t						_lastIndex;
};
//std::ostream					&operator<<(std::ostream &o, CornerPoints const &rhs);

#include "FtArray.class.tpp"

#endif // *************************************** FTARRAY_CLASS_HPP //
