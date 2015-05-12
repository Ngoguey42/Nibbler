
#include "FtVertex.class.hpp"
#include "FtArray.class.hpp"
#include "CornerPoints.class.hpp"
#include <cmath>

#define SIZE1 2


// typedef CornerPoints<SIZE1> t_phasePoints;



// typedef std::array<CornerPoints, NUM_PRECALC_POINTS>		t_phasePointsArray;
typedef FtArray<CornerPoints, NUM_PRECALC_POINTS>		t_phasePointsArray;


// typedef CornerPoints[NUM_PRECALC_POINTS]		t_phasePointsArray;
	
// constexpr t_phasePoints				buildPoints()
// {
	// std::array<t_vertexf, SIZE1>		a{std::make_pair(2.f, 1.f), std::make_pair(1.f, 5.f)};
	// t_phasePoints	t(a);
	
	// // size_t truc = fmax(1, 2);
	
	// return t_phasePoints(t);
// }

constexpr t_phasePointsArray		buildPointsArray(bool sinistro)
{
	t_phasePointsArray	points{};
	float				phase(0.f);
	
	for (int i = 0; i < points.size(); i++, phase += 1 / NUM_PRECALC_POINTS)
	{
		// points[i].test(42);
		points[i].init(phase, sinistro);
	}
	
	
	return points;
}




int main(void)
{
	
	// const std::array<t_vertexf, SIZE1>		a1{std::make_pair(1.f, 1.f), std::make_pair(1.f, 1.f)};
	
	// t_phasePoints	pts(a1);
	
	// t_phasePoints	pts(buildPoints());
	
	
	// CornerPoints<SIZE1>	pts(a1);

	// pts.describe();
	
	
	
	CornerPoints	state;

	constexpr t_phasePointsArray	sinPoints(buildPointsArray(true));

	
	state.test(12);
	
	static_assert(state, "test");
	static_assert(sinPoints[0], "test");
	// static_assert(sinPoints[0].leftStrip1[0].first == 0.f, "test");
	static_assert(sinPoints[0].leftStrip1[0].x != -5.f, "test");
	static_assert(ft_ceil(1.f) == 1, "test");
	// static_assert(state == false, "test");
	
	
	// std::cout << sinPoints[0].leftStrip1[0] << std::endl;
	
#define PRINT(array)\
	for (auto const & v : sinPoints[0]. array)\
		std::cout << #array << "[] = " << v << std::endl;
		
	PRINT(leftStrip1)
	PRINT(leftFan)
	PRINT(leftStrip2)
	PRINT(rightStrip1)
	PRINT(rightFan)
	PRINT(rightStrip2)
	return 0;
}