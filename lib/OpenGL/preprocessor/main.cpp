
#include "Vertex.class.hpp"
#include "Array.class.hpp"
#include "CornerPoints.class.hpp"

#define ARRAY_CUSTOM_SIZE										\
ftce::Array<CornerPoints<S1,S2,S3,S4,S5,S6>, NUM_PRECALC_POINTS>

#define ARRAY_DEFAULT_SIZE										\
ftce::Array<CornerPoints<>, NUM_PRECALC_POINTS>

template <size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6>
constexpr ARRAY_CUSTOM_SIZE			buildPointsArray(bool sinistro)
{
	ARRAY_CUSTOM_SIZE		points{};
	float					phase(0.f);

	for (int i = 0; i < points.size(); i++, phase += 1 / NUM_PRECALC_POINTS)
		points[i].init(phase, sinistro);
	return points;
}


constexpr ftce::Array<size_t, 6>	calcPointsArraySize(bool sinistro)
{
	ftce::Array<size_t, 6>	ret;
	ARRAY_DEFAULT_SIZE		points{};
	float					phase(0.f);

	for (int i = 0; i < points.size(); i++, phase += 1 / NUM_PRECALC_POINTS)
	{
		points[i].init(phase, sinistro);
		ret[0] = ftce::max(points[i].leftStrip1.getLastIndex() + 1, ret[0]);
		ret[1] = ftce::max(points[i].leftFan.getLastIndex() + 1, ret[1]);
		ret[2] = ftce::max(points[i].leftStrip2.getLastIndex() + 1, ret[2]);
		ret[3] = ftce::max(points[i].rightStrip1.getLastIndex() + 1, ret[3]);
		ret[4] = ftce::max(points[i].rightFan.getLastIndex() + 1, ret[4]);
		ret[5] = ftce::max(points[i].rightStrip2.getLastIndex() + 1, ret[5]);
	}
	return (ret);
}

#undef ARRAY_CUSTOM_SIZE
#undef ARRAY_DEFAULT_SIZE

# include "ConstexprMathTest.hpp"

int									main(void)
{
	ftce::test_floorceil<float>();
	// ftce::test_sqrt<float>();
	// ftce::test_cos<float>();
	return (0);
	// Calculating 'sinPoints' array's size in 'sinSize'	//
	constexpr ftce::Array<size_t, 6>	sinSize(calcPointsArraySize(true));
	// Creating 'sinPoints' with 'sinSize' size				//
#define TEMPLATE_SIZE(S) S[0], S[1], S[2], S[3], S[4], S[5]
	constexpr ftce::Array<CornerPoints<TEMPLATE_SIZE(sinSize)>, NUM_PRECALC_POINTS>
		sinPoints(buildPointsArray<TEMPLATE_SIZE(sinSize)>(true));
	
	std::cout << "size of CornerPoints<>: " << sizeof(CornerPoints<>) << std::endl;
	std::cout << "size of CornerPoints<TEMPLATE_SIZE(sinSize)>: " << sizeof(CornerPoints<TEMPLATE_SIZE(sinSize)>) << std::endl;
	std::cout << "size of ftce::Array<CornerPoints<>, NUM_PRECALC_POINTS>: " << sizeof(ftce::Array<CornerPoints<>, NUM_PRECALC_POINTS>) << std::endl;
	std::cout << "size of ftce::Array<CornerPoints<TEMPLATE_SIZE(sinSize)>, NUM_PRECALC_POINTS>: " << sizeof(ftce::Array<CornerPoints<TEMPLATE_SIZE(sinSize)>, NUM_PRECALC_POINTS>) << std::endl;
#undef TEMPLATE_SIZE
	
#define PRINT(i)\
	std::cout << #i << ": " << sinSize[i] << std::endl;
	PRINT(0)
	PRINT(1)
	PRINT(2)
	PRINT(3)
	PRINT(4)
	PRINT(5)
#undef PRINT
	
	static_assert(sinPoints[0], "test");
	static_assert(sinPoints[0].leftStrip1[0].x != -5.f, "test");
	
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