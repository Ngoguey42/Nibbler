
namespace ftce //ft_ConstExpr
{
template<typename T>
constexpr T			pow(T x, int p)
{
	T	ret(static_cast<T>(1));

	if (p > 0)
		for (int i = 0; i < p; i++)
			ret *= x;
	else if (p < 0)
		for (int i = 0; i < -p; i++)
			ret /= x;
	return (ret);
}

template<typename T>
constexpr T			factorial(T x)
{
	T	ret(x);

	while ((x -= static_cast<T>(1)) > static_cast<T>(0))
		ret *= x;
	return (ret);
}

template<typename T>
constexpr T			sqrt(T z)
{
	const T		pow10[] = {1, 10, 100, 1000, 10000, 100000};
	const T		powm10[] = {1, 0.1, 0.01, 0.001, 0.0001, 0.00001};
	T		ret = 0.0;
	T		j = 1.0;

	for(int i = 4 ; i > 0 ; i--)
	{
		T const		ip10 = pow10[i];
		T const		ip10square = ip10 * ip10;
		T const		ret2 = static_cast<T>(2.f) * ret;
		T const		ip10ret2 = ip10 * ret2;

		if (z - j * j * ip10square - j * ip10ret2 >= 0)
		{
			while(z - j * j * ip10square - j * ip10ret2 >= 0)
			{
				j++;
				if (j >= 10)
					break;
			}
			j--;
			z -= j * j * ip10square + j * ip10ret2;
			ret += j * ip10;
			j = 1.0;
		}
	}
	for(int i = 0 ; i >= -4 ; i--)
	{
		T const		ip10 =  powm10[-i];
		T const		ret2 = static_cast<T>(2.f) * ret;
		T const		ip10square = ip10 * ip10;
		T const		ip10ret2 = ip10 * ret2;
		
		if (z - j * j * ip10square - j * ip10ret2 >= 0)
		{
			while(z - j * j * ip10square - j * ip10ret2 >= 0)
				j++;
			j--;
			z -= j * j * ip10square + j * ip10ret2;
			ret += j * ip10;
			j = 1.0;
		}
	}
	return (ret);
}

template<typename T>
constexpr T			cos(T x)
{
	while (x > M_PI)
		x -= 2.f * M_PI;
	while (x < -M_PI)
		x += 2.f * M_PI;
	return (static_cast<T>(1)
		- (ftce::pow(x, 2) / 2.f)
		+ (ftce::pow(x, 4) / 24.f)
		- (ftce::pow(x, 6) / 720.f)
		+ (ftce::pow(x, 8) / 40320.f)	// MaxError: +0.0239781(-2.3978114%)
		- (ftce::pow(x, 10) / 3628800.f)	// MaxError: +0.0018293(-0.1829267%)
		+ (ftce::pow(x, 12) / 479001600.f)	// MaxError: +0.0001009(-0.0100911%)
		// - (ftce::pow(x, 14) / ftce::factorial(14))	// MaxError: +0.0070322(-0.7032156%)
		// + (ftce::pow(x, 16) / ftce::factorial(16))	// MaxError: +0.0378902(-3.7890196%)
		);
}

template<typename T>
constexpr T			ceil(T x)
{
	const T		r = static_cast<T>(static_cast<int>(x));

	return ((r == x) ? r : (x > static_cast<T>(0)) ? r + static_cast<T>(1) : r); //A VERIFIER !!
}

template<typename T>
constexpr T			floor(T x)
{
	const T		r = static_cast<T>(static_cast<int>(x));

	return ((r == x) ? r : (x > static_cast<T>(0)) ? r : r - static_cast<T>(1)); //A VERIFIER !!
}

template<typename T>
constexpr T const	&max(T const &x, T const &y)
{
	if (x > y)
		return (x);
	return (y);
}

template<typename T>
constexpr T			fmod(T x, T y)
{
	while(x < static_cast<T>(0))
		x += y;
	while(x > y)
		x -= y;
	return (x);
}
};
