


// template<std::size_t N>
// constexpr CornerPoints<N>::CornerPoints(std::array<t_vertexf, N> leftStrip1) :
	// _leftStrip1(leftStrip1)
// {
// }

// template<>

// template <size_t S1>
constexpr CornerPoints::CornerPoints() :
	i(),
	leftStrip1(),
	leftFan(),
	leftStrip2(),
	rightStrip1(),
	rightFan(),
	rightStrip2()
	{}
	
// template <size_t S1>
constexpr CornerPoints		&CornerPoints::operator=(CornerPoints const &rhs)
{
	// for (int i = 0; i <= this->leftStrip1.getLastIndex(); i++)
	this->leftStrip1 = rhs.leftStrip1;
	this->leftFan = rhs.leftFan;
	this->leftStrip2 = rhs.leftStrip2;
	this->rightStrip1 = rhs.rightStrip1;
	this->rightFan = rhs.rightFan;
	this->rightStrip2 = rhs.rightStrip2;
	// this->_data = rhs._data;
	return (*this);
}

// template<std::size_t N>
// constexpr CornerPoints<N>::CornerPoints(CornerPoints<N> const &src) :
	// _leftStrip1(src._leftStrip1)
// {
// }

// template<std::size_t N>
// void						CornerPoints<N>::describe(void) const
// {
	// std::cout << "Size: " << N << std::endl;
	// for (int i = 0; i < N; i++)
	// {
		// std::cout << this->_leftStrip1[i] << std::endl;
	// }
	// return ;
// }
