

// * CONSTRUCTORS *********************************************************** //
constexpr Vertex::Vertex() :
	x(0.f),
	y(0.f),
	z(0.f)
{
	return ;
}

constexpr Vertex::Vertex(float x, float y) :
	x(x),
	y(y),
	z(0.f)
{
	return ;
}

constexpr Vertex::Vertex(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{
	return ;
}

constexpr Vertex::Vertex(Vertex const &src) :
	x(src.x),
	y(src.y),
	z(src.z)
{
	return ;
}

// * OPERATORS ************************************************************** //
constexpr Vertex			&Vertex::operator=(Vertex const &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return (*this);
}
constexpr Vertex			&Vertex::operator*=(float m)
{
	this->x *= m;
	this->y *= m;
	this->z *= m;
	return (*this);
}

std::ostream					&operator<<(std::ostream &o, Vertex const &rhs)
{
	return (o << "(" << rhs.x << "/" << rhs.y << ")");
}


constexpr Vertex			&Vertex::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return (*this);
}