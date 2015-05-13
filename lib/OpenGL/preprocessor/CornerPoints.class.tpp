
#define DY_CLASS CornerPoints<S1,S2,S3,S4,S5,S6>
#define TEMPLATE_ARGS														\
template <size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6>

// * CONSTRUCTORS *********************************************************** //
TEMPLATE_ARGS
constexpr DY_CLASS::CornerPoints() :
	leftStrip1(),
	leftFan(),
	leftStrip2(),
	rightStrip1(),
	rightFan(),
	rightStrip2()
	{}

// * OPERATORS ************************************************************** //
TEMPLATE_ARGS
constexpr DY_CLASS		&DY_CLASS::operator=(DY_CLASS const &rhs)
{
	this->leftStrip1 = rhs.leftStrip1;
	this->leftFan = rhs.leftFan;
	this->leftStrip2 = rhs.leftStrip2;
	this->rightStrip1 = rhs.rightStrip1;
	this->rightFan = rhs.rightFan;
	this->rightStrip2 = rhs.rightStrip2;
	return (*this);
}

// * MEMBER FUNCTIONS / METHODS ********************************************* //
TEMPLATE_ARGS
constexpr float				DY_CLASS::init(float ratio, bool sinistro)
{
	this->leftStrip1[0].x = 2.f;
	this->leftStrip1[0].y = 3.f;
	this->leftStrip2[0].x = 42.f;
	this->leftStrip2[1].x = 42.f;
	return (ratio);
}

#undef DY_CLASS
#undef TEMPLATE_ARGS
