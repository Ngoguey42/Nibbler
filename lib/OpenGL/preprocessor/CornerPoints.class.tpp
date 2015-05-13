
template <size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6>
constexpr CornerPoints<S1,S2,S3,S4,S5,S6>::CornerPoints() :
	i(),
	leftStrip1(),
	leftFan(),
	leftStrip2(),
	rightStrip1(),
	rightFan(),
	rightStrip2()
	{}
	
template <size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6>
constexpr CornerPoints<S1,S2,S3,S4,S5,S6>		&CornerPoints<S1,S2,S3,S4,S5,S6>::operator=(CornerPoints<S1,S2,S3,S4,S5,S6> const &rhs)
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


template <size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6>
constexpr float				CornerPoints<S1,S2,S3,S4,S5,S6>::init(float ratio, bool sinistro)
{
	this->leftStrip1[0].x = 2.f;
	this->leftStrip1[0].y = 3.f;
	this->leftStrip2[0].x = 42.f;
	this->leftStrip2[1].x = 42.f;
	return (ratio);
}