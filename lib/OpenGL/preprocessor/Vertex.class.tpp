

// * CONSTRUCTORS *********************************************************** //
constexpr Vertex::Vertex() :
	x(0.f),
	y(0.f)
{
	return ;
}

constexpr Vertex::Vertex(float x, float y) :
	x(x),
	y(y)
{
	return ;
}

constexpr Vertex::Vertex(Vertex const &src) :
	x(src.x),
	y(src.y)
{
	return ;
}

// * OPERATORS ************************************************************** //
constexpr Vertex			&Vertex::operator=(Vertex const &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return (*this);
}

std::ostream					&operator<<(std::ostream &o, Vertex const &rhs)
{
	return (o << "(" << rhs.x << "/" << rhs.y << ")");
}
