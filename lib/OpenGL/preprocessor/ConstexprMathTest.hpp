
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <tuple>
#include <functional>

namespace ftce //ft_ConstExpr
{
template<typename T>
void								test_sqrt(void)
{
#define STEP static_cast<T>(0.01f)
	typedef std::tuple<T, T, T, float>	t_result; //nbr, nbr mod2pi, realcos, mycos, 
	std::vector<t_result>					vect;

	for (T f = 0.1f;
		 f < 30000.f;
		 f += STEP)
	{
		T	his(std::sqrt(f));
		T	mine(ftce::sqrt<T>(f));
		vect.push_back(std::make_tuple(f, his, mine,
			fabs(his - mine)));
	}
	
	std::cout << "Greatest deltas in " << vect.size() << " samples" << std::endl;
	std::cout << "		   Value" <<
				 "		Ref Sqrt" <<
				 "		 My Sqrt" <<
				 "			Diff" <<
				 std::endl;
	
	float		maxdiff;
	t_result	*ptr;
		std::cout << std::fixed;		std::cout << std::setprecision(7);
		std::cout << std::showpos;
	for (int i = 1; i <= 20; i++)
	{
		maxdiff = 0.f;
		for (auto &v : vect)
		{
			if (std::get<3>(v) > maxdiff)
			{
				ptr = &v;
				maxdiff = std::get<3>(v);
			}
		}
		std::cout << std::setw(16);
		std::cout << std::get<0>(*ptr);
		std::cout << std::setw(16);
		std::cout << std::get<1>(*ptr);
		std::cout << std::setw(16);
		std::cout << std::get<2>(*ptr);
		std::cout << std::setw(16);
		std::cout << maxdiff << "(" << maxdiff / std::get<2>(*ptr) * 100 << "%)";
		std::cout << std::endl;
		std::get<3>(*ptr) = 0.f;
	}
#undef STEP
}

template<typename T>
void								test_cos(void)
{
#define STEP static_cast<T>(0.00001f)
	typedef std::tuple<T, T, T, T, float>	t_result; //nbr, nbr mod2pi, realcos, mycos, 
	std::vector<t_result>					vect;

	for (T f = -M_PI * 5.f - STEP * 10.f;
		 f < M_PI * 5.f + STEP * 10.f;
		 f += STEP)
	{
		T	f2(f);

		while (f2 > M_PI)
			f2 -= 2.f * M_PI;
		while (f2 < -M_PI)
			f2 += 2.f * M_PI;
		T	his(std::cos(f));
		T	mine(ftce::cos<T>(f));
		vect.push_back(std::make_tuple(f, f2, his, mine,
			fabs(his - mine)));
	}
	
	std::cout << "Greatest deltas in " << vect.size() << " samples" << std::endl;
	std::cout << "		   Value" <<
				 "   Value mod 2pi" <<
				 "	 Ref Cosinus" <<
				 "	  My Cosinus" <<
				 "			Diff" <<
				 std::endl;
	
	float		maxdiff;
	t_result	*ptr;
		std::cout << std::fixed;		std::cout << std::setprecision(7);
		std::cout << std::showpos;
	for (int i = 1; i <= 20; i++)
	{
		maxdiff = 0.f;
		for (auto &v : vect)
		{
			if (std::get<4>(v) > maxdiff)
			{
				ptr = &v;
				maxdiff = std::get<4>(v);
			}
		}
		std::cout << std::setw(16);
		std::cout << std::get<0>(*ptr);
		std::cout << std::setw(16);
		std::cout << std::get<1>(*ptr);
		std::cout << std::setw(16);
		std::cout << std::get<2>(*ptr);
		std::cout << std::setw(16);
		std::cout << std::get<3>(*ptr);
		std::cout << std::setw(16);
		std::cout << maxdiff << "(" << maxdiff / std::get<2>(*ptr) * 100 << "%)";
		std::cout << std::endl;
		std::get<4>(*ptr) = 0.f;
	}
#undef STEP
}
};

// int									main(void)
// {
	// ftce::test_cos<float>();
	// ftce::test_sqrt<float>();
	// return (0);
// }