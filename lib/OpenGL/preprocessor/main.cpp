
#include "FtVertex.class.hpp"
#include "FtArray.class.hpp"
#include "CornerPoints.class.hpp"
#include <cmath>

typedef FtArray<CornerPoints, NUM_PRECALC_POINTS>		t_phasePointsArray;

class CornerPointsSize
{
public:
	constexpr CornerPointsSize() :
		s1(0), s2(0), s3(0), s4(0), s5(0), s6(0)
		{}
	constexpr CornerPointsSize(CornerPointsSize const &src) :
		s1(src.s1), s2(src.s2), s3(src.s3), s4(src.s4), s5(src.s5), s6(src.s6)
		{}

	size_t					s1;
	size_t					s2;
	size_t					s3;
	size_t					s4;
	size_t					s5;
	size_t					s6;
private:
	CornerPointsSize const	&operator=(CornerPointsSize const &rhs);
};

template <size_t S1 = MAX_POINTS_PER_GROUP,
size_t S2 = MAX_POINTS_PER_GROUP,
size_t S3 = MAX_POINTS_PER_GROUP,
size_t S4 = MAX_POINTS_PER_GROUP,
size_t S5 = MAX_POINTS_PER_GROUP,
size_t S6 = MAX_POINTS_PER_GROUP>
constexpr t_phasePointsArray		buildPointsArray(bool sinistro)
{
	t_phasePointsArray		points{};
	float					phase(0.f);
	
	for (int i = 0; i < points.size(); i++, phase += 1 / NUM_PRECALC_POINTS)
		points[i].init(phase, sinistro);
	return points;
}

constexpr CornerPointsSize			calcPointsArraySize(bool sinistro)
{
	CornerPointsSize		ret;
	t_phasePointsArray		points{};
	float					phase(0.f);

	for (int i = 0; i < points.size(); i++, phase += 1 / NUM_PRECALC_POINTS)
	{
		points[i].init(phase, sinistro);
		if (points[i].leftStrip1.getLastIndex() >= ret.s1)
			ret.s1 = points[i].leftStrip1.getLastIndex() + 1;
		if (points[i].leftFan.getLastIndex() >= ret.s2)
			ret.s2 = points[i].leftFan.getLastIndex() + 1;
		if (points[i].leftStrip2.getLastIndex() >= ret.s3)
			ret.s3 = points[i].leftStrip2.getLastIndex() + 1;
		if (points[i].rightStrip1.getLastIndex() >= ret.s4)
			ret.s4 = points[i].rightStrip1.getLastIndex() + 1;
		if (points[i].rightFan.getLastIndex() >= ret.s5)
			ret.s5 = points[i].rightFan.getLastIndex() + 1;
		if (points[i].rightStrip2.getLastIndex() >= ret.s6)
			ret.s6 = points[i].rightStrip2.getLastIndex() + 1;
	}
	
	return (ret);
}


int main(void)
{
	CornerPoints	state;

	constexpr t_phasePointsArray	sinPoints(buildPointsArray(true));
	constexpr CornerPointsSize		classSize(calcPointsArraySize(true));
	
#define PRINT(i)\
	std::cout << #i << ": " << classSize. i << std::endl;
	PRINT(s1)
	PRINT(s2)
	PRINT(s3)
	PRINT(s4)
	PRINT(s5)
	PRINT(s6)
#undef PRINT
	state.test(12);
	
	static_assert(state, "test");
	static_assert(sinPoints[0], "test");
	// static_assert(sinPoints[0].leftStrip1[0].first == 0.f, "test");
	static_assert(sinPoints[0].leftStrip1[0].x != -5.f, "test");
	static_assert(ft_ceil(1.f) == 1, "test");
	// static_assert(state == false, "test");

	
#define PRINT(array)\
	for (auto const & v : sinPoints[0]. array)\
		std::cout << #array << "[] = " << v << std::endl;
	PRINT(leftStrip1)
	PRINT(leftFan)
	PRINT(leftStrip2)
	PRINT(rightStrip1)
	PRINT(rightFan)
	PRINT(rightStrip2)
#undef PRINT

	return 0;
}