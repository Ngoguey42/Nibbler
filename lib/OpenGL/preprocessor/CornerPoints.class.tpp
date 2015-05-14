
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
{
	return ;
}

// TEMPLATE_ARGS
// constexpr DY_CLASS::CornerPoints(float ratio) :
	// leftStrip1(),
	// leftFan(),
	// leftStrip2(),
	// rightStrip1(),
	// rightFan(),
	// rightStrip2()
// {
	// this->init(ratio);
	// return ;
// }

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
	AngledSnakePoints		points;
	int						index(0);
	int i(0);
	float z(20.f);

	points.init(ratio);
#define SAVE_POINT this->leftStrip1[index++].set
	if (points.leftBranchInLastIndex > 0)
	{
		// 
		SAVE_POINT(points.middleBranchInPoints[0].x,
				   points.middleBranchInPoints[0].y, z);

		while(i < points.leftBranchInLastIndex)
		{					
			SAVE_POINT(points.leftBranchInPoints[i].x,
					   points.leftBranchInPoints[i].y, 0.f);
			i++;
			SAVE_POINT(points.middleBranchInPoints[i].x,
					   points.middleBranchInPoints[i].y, z);
		}
		SAVE_POINT(points.leftBranchIntersection.x,
				   points.leftBranchIntersection.y, 0.f);
	}
#undef SAVE_POINT
	index = 0;
#define SAVE_POINT this->leftFan[index++].set
	SAVE_POINT(points.leftBranchIntersection.x,
			   points.leftBranchIntersection.y, 0.f);
	for (size_t j = i; j < points.middleBranchInLastIndex; j++)
	{
		SAVE_POINT(points.middleBranchInPoints[j].x,
				   points.middleBranchInPoints[j].y, z);
	}
	
	SAVE_POINT(points.middleBranchIntersection.x,
			   points.middleBranchIntersection.y, 0.f);
	i = points.leftBranchOutLastIndex;
	
	for (int j = points.middleBranchOutLastIndex - 1;
		 j >= static_cast<int>(i); j--)
	{
		SAVE_POINT(points.middleBranchOutPoints[j].x,
				   points.middleBranchOutPoints[j].y, z);
	}
#undef SAVE_POINT
	index = 0;
#define SAVE_POINT this->leftStrip2[index++].set
	if (points.leftBranchOutLastIndex > 0)
	{
		SAVE_POINT(points.leftBranchIntersection.x,
				   points.leftBranchIntersection.y, 0.f);
		for (i = points.leftBranchOutLastIndex;;i--)
		{
			SAVE_POINT(points.middleBranchOutPoints[i].x,
					   points.middleBranchOutPoints[i].y, z);
			SAVE_POINT(points.leftBranchOutPoints[i].x,
					   points.leftBranchOutPoints[i].y, 0.f);
			if (i == 0)
				break ;
		}
	}
#undef SAVE_POINT
	index = 0;
#define SAVE_POINT this->rightStrip1[index++].set
	if (points.middleBranchInLastIndex > 0)
	{

		SAVE_POINT(points.rightBranchInPoints[0].x,
				   points.rightBranchInPoints[0].y, z);

		while(i < points.middleBranchInLastIndex)
		{					
			SAVE_POINT(points.middleBranchInPoints[i].x,
					   points.middleBranchInPoints[i].y, 0.f);
			i++;
			SAVE_POINT(points.rightBranchInPoints[i].x,
					   points.rightBranchInPoints[i].y, z);
		}
		SAVE_POINT(points.middleBranchIntersection.x,
				   points.middleBranchIntersection.y, 0.f);
	}
	// FAN
#undef SAVE_POINT
	index = 0;
#define SAVE_POINT this->rightFan[index++].set
	SAVE_POINT(points.middleBranchIntersection.x,
			   points.middleBranchIntersection.y, 0.f);
	for (size_t j = i; j < points.rightBranchInLastIndex; j++)
	{
		SAVE_POINT(points.rightBranchInPoints[j].x,
				   points.rightBranchInPoints[j].y, z);
	}
	
	SAVE_POINT(points.rightBranchIntersection.x,
			   points.rightBranchIntersection.y, 0.f);
	i = points.middleBranchOutLastIndex;
	
	for (int j = points.rightBranchOutLastIndex - 1;
		 j >= static_cast<int>(i); j--)
	{
		SAVE_POINT(points.rightBranchOutPoints[j].x,
				   points.rightBranchOutPoints[j].y, z);
	}
#undef SAVE_POINT
	index = 0;
#define SAVE_POINT this->rightStrip2[index++].set
	if (points.middleBranchOutLastIndex > 0)
	{
		SAVE_POINT(points.middleBranchIntersection.x,
				   points.middleBranchIntersection.y, 0.f);
		for (i = points.middleBranchOutLastIndex;;i--)
		{
			SAVE_POINT(points.rightBranchOutPoints[i].x,
					   points.rightBranchOutPoints[i].y, z);
			SAVE_POINT(points.middleBranchOutPoints[i].x,
					   points.middleBranchOutPoints[i].y, 0.f);
			if (i == 0)
				break ;
		}
	}
#undef SAVE_POINT
	return (ratio);
}

#undef DY_CLASS
#undef TEMPLATE_ARGS
