

// * CONSTRUCTORS *********************************************************** //
constexpr FtVertex::FtVertex() :
	x(0.f),
	y(0.f)
{}

constexpr FtVertex::FtVertex(float x, float y) :
	x(x),
	y(y)
{
	return ;
}

constexpr FtVertex::FtVertex(FtVertex const &src) :
	x(src.x),
	y(src.y)
{
	return ;
}

// * OPERATORS ************************************************************** //
constexpr FtVertex			&FtVertex::operator=(FtVertex const &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return (*this);
}

std::ostream					&operator<<(std::ostream &o, FtVertex const &rhs)
{
	return (o << "(" << rhs.x << "/" << rhs.y << ")");
}
