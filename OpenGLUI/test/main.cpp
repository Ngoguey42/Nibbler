#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>

#ifndef M_PI
# define M_PI 3.14159265358979323846f
#endif

//	==================================	//
#define CHUNK_SIZE 35					// Pixels integer
#define SNAKE_WAVELENGTH 105.f			// Pixels float
// #define SNAKE_WAVELENGTH 70.f			// Pixels float
#define SNAKE_WIDTH 0.66f				// Percent of CHUNK_SIZE
// #define SNAKE_WIDTH 0.5f				// Percent of CHUNK_SIZE
#define POINTS_PER_SIDE 9				// 
// #define POINTS_PER_SIDE 10				// 
#define PRECALC_POINTS_DELTA 1.f		// Density of pre-calculated points
//	==================================	//

//are all those macro evaluated preprocessor?
#define CHUNK_SIZEF static_cast<float>(CHUNK_SIZE)
#define POINTS_PER_SIDEF static_cast<float>(POINTS_PER_SIDE)

#define SNAKE_WIDTH_ABSOLUTE (SNAKE_WIDTH * CHUNK_SIZEF)
#define SNAKE_WIDTH_INV (1.f - SNAKE_WIDTH)
#define SNAKE_WIDTH_HALF (SNAKE_WIDTH / 2.f)
#define PHASE_PER_CHUNK (CHUNK_SIZEF / SNAKE_WAVELENGTH)
#define PHASE_PER_TRIANGLE (PHASE_PER_CHUNK / POINTS_PER_SIDEF)
#define TRIANGLES_DISTANCE (CHUNK_SIZEF / POINTS_PER_SIDEF)

//	Points pre-calculation macros ====	//
//		Number of pixels				//
#define PHASE_MAX_DELTA (CHUNK_SIZEF * (1 - SNAKE_WIDTH))
//		Number of points float			//
#define NUM_PRECALC_POINTSF ceilf(PHASE_MAX_DELTA / PRECALC_POINTS_DELTA)
//		Number of points integer		//
#define NUM_PRECALC_POINTS static_cast<int>(NUM_PRECALC_POINTSF)
//	==================================	//

#define MAX_POINTS_BEFORE_ANGLEF floorf(POINTS_PER_SIDEF * SNAKE_WIDTH_INV + 1.f)
// #define MAX_POINTS_BEFORE_ANGLE static_cast<int>(MAX_POINTS_BEFORE_ANGLEF)
#define MAX_POINTS_BEFORE_ANGLE (POINTS_PER_SIDE + 1)

class AngledSnakePoints
{//ctors dtor needed
public:
	AngledSnakePoints(){};
	virtual ~AngledSnakePoints(){};
	
	void				init(float const initRatio);
	void				describe(void);
	void				describePoints(void);
	
	typedef std::pair<float, float>							t_vertexf;
	typedef std::array<t_vertexf, MAX_POINTS_BEFORE_ANGLE>	t_snakepoints;

	t_vertexf			leftBranchIntersection;
	t_snakepoints		leftBranchInPoints;
	size_t				leftBranchInLastIndex;
	t_snakepoints		leftBranchOutPoints;
	size_t				leftBranchOutLastIndex;

	t_vertexf			middleBranchIntersection;
	t_snakepoints		middleBranchInPoints;
	size_t				middleBranchInLastIndex;
	t_snakepoints		middleBranchOutPoints;
	size_t				middleBranchOutLastIndex;

	t_vertexf			rightBranchIntersection;
	t_snakepoints		rightBranchInPoints;
	size_t				rightBranchInLastIndex;
	t_snakepoints		rightBranchOutPoints;
	size_t				rightBranchOutLastIndex;
	
private:
	AngledSnakePoints(AngledSnakePoints const &src);
	AngledSnakePoints const &operator=(AngledSnakePoints const &rhs);
	
	void				setBranchIntersection(
		t_vertexf &intersection, t_vertexf const &a, t_vertexf const &b);
	void				calcIntersection(t_snakepoints const &inPoints,
														   t_snakepoints const &outPoints,
														   size_t &inLastIndex,
														   size_t &outLastIndex,
														   t_vertexf &intersection);
};

void				AngledSnakePoints::init(float const initRatio)
{
	float	curphase, bestDistance;
	// int		i, j;
	
	// Setting this->leftBranchInPoints		//
	curphase = fmodf(initRatio, 1.f);
	for (int j = 0; j < MAX_POINTS_BEFORE_ANGLE; j++)
	{
		this->leftBranchInPoints[j] = std::make_pair(
			(cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) /
				2.f * SNAKE_WIDTH_INV + SNAKE_WIDTH,
			j * (TRIANGLES_DISTANCE / CHUNK_SIZEF));
		std::cout << "(" << this->leftBranchInPoints[j].first << "/" << this->leftBranchInPoints[j].second << ") ";
		this->rightBranchInPoints[j] = std::make_pair(
			this->leftBranchInPoints[j].first - SNAKE_WIDTH,
			this->leftBranchInPoints[j].second);
		this->middleBranchInPoints[j] = std::make_pair(
			this->leftBranchInPoints[j].first - SNAKE_WIDTH_HALF,
			this->leftBranchInPoints[j].second);
		curphase = fmodf(curphase + PHASE_PER_TRIANGLE, 1.f);
	}
	std::cout << std::endl;
	// Setting this->leftBranchOutPoints		//
	curphase = fmodf(initRatio + PHASE_PER_CHUNK, 1.f);
	for (int j = 0; j < MAX_POINTS_BEFORE_ANGLE; j++)
	{
		this->leftBranchOutPoints[j] = std::make_pair(
			1.f - j * (TRIANGLES_DISTANCE / CHUNK_SIZEF),
			SNAKE_WIDTH_INV - (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) /
			2.f * SNAKE_WIDTH_INV);
		std::cout << "(" << this->leftBranchOutPoints[j].first << "/" << this->leftBranchOutPoints[j].second << ") ";
		this->rightBranchOutPoints[j] = std::make_pair(
			this->leftBranchOutPoints[j].first,
			this->leftBranchOutPoints[j].second + SNAKE_WIDTH);
		this->middleBranchOutPoints[j] = std::make_pair(
			this->leftBranchOutPoints[j].first,
			this->leftBranchOutPoints[j].second + SNAKE_WIDTH_HALF);
		curphase = fmodf(curphase - PHASE_PER_TRIANGLE + 1.f, 1.f);
	}
	std::cout << std::endl;
	this->calcIntersection(
		this->leftBranchInPoints, this->leftBranchOutPoints,
		this->leftBranchInLastIndex, this->leftBranchOutLastIndex,
		this->leftBranchIntersection);
	this->calcIntersection(
		this->rightBranchInPoints, this->rightBranchOutPoints,
		this->rightBranchInLastIndex, this->rightBranchOutLastIndex,
		this->rightBranchIntersection);
	this->calcIntersection(
		this->middleBranchInPoints, this->middleBranchOutPoints,
		this->middleBranchInLastIndex, this->middleBranchOutLastIndex,
		this->middleBranchIntersection);
	// Setting this->leftBranchInLastIndex		//
	// Setting this->leftBranchOutLastIndex	//
	// bestDistance = 2.f;
	// i = 0;
	// for (auto const &w : this->leftBranchInPoints)
	// {
		// j = 0;
		// for (auto const &x : this->leftBranchOutPoints)
		// {
			// float const	dx = w.first - x.first;
			// float const	dy = w.second - x.second;
			// float const	distance = sqrtf(dx * dx + dy * dy);
			
			// if (bestDistance > distance)
			// {
				// bestDistance = distance;
				// this->leftBranchInLastIndex = i;
				// this->leftBranchOutLastIndex = j;
			// }
			// j++;
		// }
		// i++;
	// }
	// Setting this->leftBranchIntersection		//
	// this->setBranchIntersection(this->leftBranchInPoints[this->leftBranchInLastIndex],
						  // this->leftBranchOutPoints[this->leftBranchOutLastIndex]);
	
	return ;
}

void				AngledSnakePoints::calcIntersection(t_snakepoints const &inPoints,
													   t_snakepoints const &outPoints,
													   size_t &inLastIndex,
													   size_t &outLastIndex,
													   t_vertexf &intersection)
{
	float	bestDistance = 2.f;
	int		i = 0, j;

	for (auto const &w : inPoints)
	{
		j = 0;
		for (auto const &x : outPoints)
		{
			float const	dx = w.first - x.first;
			float const	dy = w.second - x.second;
			float const	distance = sqrtf(dx * dx + dy * dy);
			
			if (bestDistance > distance)
			{
				bestDistance = distance;
				inLastIndex = i;
				outLastIndex = j;
			}
			j++;
		}
		i++;
	}
	this->setBranchIntersection(intersection,
								inPoints[inLastIndex],
								outPoints[outLastIndex]);
	return ;
}

void				AngledSnakePoints::setBranchIntersection(
	t_vertexf &intersection, t_vertexf const &a, t_vertexf const &b)
{
	intersection = std::make_pair(
		b.first + (a.first - b.first) / 2,
		b.second + (a.second - b.second) / 2);
	return ;
}

void				AngledSnakePoints::describe(void)
{
	std::cout << "Left i/o(" << leftBranchInLastIndex << "-";
	std::cout << "" << leftBranchOutLastIndex << ") ";
	std::cout << "i(" << leftBranchIntersection.first << "/"
		<< leftBranchIntersection.second << ")  ";
	std::cout << "Middle i/o(" << middleBranchInLastIndex << "-";
	std::cout << "" << middleBranchOutLastIndex << ") ";
	std::cout << "i(" << middleBranchIntersection.first << "/"
		<< middleBranchIntersection.second << ")  ";
	std::cout << "Right i/o(" << rightBranchInLastIndex << "-";
	std::cout << "" << rightBranchOutLastIndex << ") ";
	std::cout << "i(" << rightBranchIntersection.first << "/"
		<< rightBranchIntersection.second << ")  ";
		
	std::cout << std::endl;
	return ;
}
void				AngledSnakePoints::describePoints(void)
{
	std::cout << "x	y		x	y		x	y" << std::endl;
	for (int i = 0; i < this->leftBranchInPoints.size(); i++)
	{
		{
			auto const &v = this->leftBranchInPoints[i];
			std::cout << v.first << "\t-" << v.second << "\t\t";
		}
		{
			auto const &v = this->rightBranchInPoints[i];
			std::cout << v.first << "\t-" << v.second << "\t\t";
		}
		{
			auto const &v = this->middleBranchInPoints[i];
			std::cout << v.first << "\t-" << v.second << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "x	y		x	y		x	y" << std::endl;
	for (int i = 0; i < this->leftBranchInPoints.size(); i++)
	{
		{
			auto const &v = this->leftBranchOutPoints[i];
			std::cout << v.first << "\t-" << v.second << "\t\t";
		}
		{
			auto const &v = this->rightBranchOutPoints[i];
			std::cout << v.first << "\t-" << v.second << "\t\t";
		}
		{
			auto const &v = this->middleBranchOutPoints[i];
			std::cout << v.first << "\t-" << v.second << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "x	y" << std::endl;
	{
		auto const &v = this->rightBranchIntersection;
		std::cout << v.first << "\t-" << v.second << std::endl;
	}
	{
		auto const &v = this->middleBranchIntersection;
		std::cout << v.first << "\t-" << v.second << std::endl;
	}
	{
		auto const &v = this->leftBranchIntersection;
		std::cout << v.first << "\t-" << v.second << std::endl;
	}
	return ;
	for (auto const &v : this->leftBranchInPoints)
		std::cout << v.first << std::endl;
	std::cout << std::endl;
	for (auto const &v : this->leftBranchInPoints)
		std::cout << v.second << std::endl;
	std::cout << std::endl;
	for (auto const &v : this->leftBranchOutPoints)
		std::cout << v.first << std::endl;
	std::cout << std::endl;
	for (auto const &v : this->leftBranchOutPoints)
		std::cout << v.second << std::endl;
	return ;
}

int main() {
	std::cout << "PHASE_MAX_DELTA: " << PHASE_MAX_DELTA << std::endl;
	std::cout << "NUM_PRECALC_POINTS: " << NUM_PRECALC_POINTS << std::endl;
	std::cout << "sizeof(AngledSnakePoints): " << sizeof(AngledSnakePoints) << std::endl;
	std::cout << "sizeof(std::array<AngledSnakePoints, NUM_PRECALC_POINTS>): " <<
		sizeof(std::array<AngledSnakePoints, NUM_PRECALC_POINTS>) << std::endl;
	
	// std::cout << ": " <<  << std::endl;
	// std::cout << ": " <<  << std::endl;
	std::cout << std::fixed << std::setprecision(3);
	std::array<AngledSnakePoints, NUM_PRECALC_POINTS>	sinistroPoints;

	int i = 0;
	for (auto &v : sinistroPoints)
	{
		v.init(fmodf(i * (1.f / NUM_PRECALC_POINTS), 1.f));
	std::cout << std::endl;
		i++;
	}
	for (auto &v : sinistroPoints)
	{
		v.describe();
	}
	sinistroPoints[5].describePoints();
	return 0;
}
