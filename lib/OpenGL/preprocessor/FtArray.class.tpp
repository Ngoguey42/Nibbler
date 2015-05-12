
template<typename T, size_t S>
constexpr FtArray<T, S>::FtArray() :
	_data(),
	_lastIndex(0)
{
	return ;
}

// template<typename T, size_t S>
// FtArray<T, S>::~FtArray()
// {
	// return ;
// }

template<typename T, size_t S>
constexpr  FtArray<T, S>::FtArray(FtArray<T, S> const &src) :
	// _data(src._data),
	_data(),
	_lastIndex(src._lastIndex)
{
	// operator=(src);
	// for (int i = 0; i <= src._lastIndex; i++)
		// this->_data[i] = src._data[i];
	for (int i = 0; i < S; i++)
		this->_data[i] = src._data[i];
	return ;
}

template<typename T, size_t S>
constexpr FtArray<T, S>		&FtArray<T, S>::operator=(FtArray<T, S> const &rhs)
{
	this->_lastIndex = rhs._lastIndex;
	// for (int i = 0; i <= rhs._lastIndex; i++)
		// this->_data[i] = rhs._data[i];
	for (int i = 0; i < S; i++)
		this->_data[i] = rhs._data[i];
	// this->_data = rhs._data;
	return (*this);
}

template<typename T, size_t S>
constexpr T					&FtArray<T, S>::operator[](size_t s)
{
	//check overflow?
	if (s > this->_lastIndex)
		this->_lastIndex = s;
	return (this->_data[s]);
}

template<typename T, size_t S>
constexpr T const			&FtArray<T, S>::operator[](size_t s) const
{
	//check overflow?
	// if (s > this->_lastIndex)
		// this->_lastIndex = s;
	return (this->_data[s]);
}

// * MEMBER FUNCTIONS / METHODS ********************************************* //
template<typename T, size_t S>
typename FtArray<T, S>::iterator	FtArray<T, S>::begin(void) const
{
	typename FtArray<T, S>::iterator	it;

	it.setPtr(&this->_data[0]);
	return (it);
}
template<typename T, size_t S>
typename FtArray<T, S>::iterator	FtArray<T, S>::end(void) const
{
	typename FtArray<T, S>::iterator	it;

	it.setPtr(&this->_data[this->_lastIndex + 1]);
	return (it);	
}

template<typename T, size_t S>
constexpr size_t			FtArray<T, S>::getLastIndex(void) const
{
	return (this->_lastIndex);
}

template<typename T, size_t S>
constexpr size_t			FtArray<T, S>::size(void) const
{
	// return (this->_lastIndex);
	return (S);
}


// * NESTED_CLASSES ********************************************************* //

// * CTORS / DTORS ************** //
template<typename T, size_t S>
FtArray<T, S>::iterator::iterator()
{
	return ;
}
template<typename T, size_t S>
FtArray<T, S>::iterator::~iterator()
{
	return ;
}
template<typename T, size_t S>
FtArray<T, S>::iterator::iterator(
	typename FtArray<T, S>::iterator const &src)
{
	iterator::operator=(src);
	return ;
}
	// * OPERATORS ****************** //
template<typename T, size_t S>
typename FtArray<T, S>::iterator	&FtArray<T, S>::iterator::operator=(
	typename FtArray<T, S>::iterator const &rhs)
{
	// std::iterator<std::bidirectional_iterator_tag, T>::operator=(rhs);
	_ptr = rhs._ptr;
	return (*this);
}
template<typename T, size_t S>
bool						FtArray<T, S>::iterator::operator!=(
	typename FtArray<T, S>::iterator const &rhs)
{
	return (_ptr != rhs._ptr);
}
template<typename T, size_t S>
typename FtArray<T, S>::iterator	&FtArray<T, S>::iterator::operator++(
	void)
{
	_ptr++;
	return (*this);
}
// template<typename T, size_t S>
// typename FtArray<T, S>::iterator	FtArray<T, S>::iterator::operator++(
	// int)
// {
	// typename FtArray<T, S>::iterator	cpy(*this);

	// ++cpy;
	// return (cpy);
// }
// template<typename T, size_t S>
// typename FtArray<T, S>::iterator	&FtArray<T, S>::iterator::operator--(
	// void)
// {
	// _ptr--;
	// return (*this);
// }
// template<typename T, size_t S>
// typename FtArray<T, S>::iterator	FtArray<T, S>::iterator::operator--(
	// int)
// {
	// typename FtArray<T, S>::iterator	cpy(*this);

	// --cpy;
	// return (cpy);
// }
// template<typename T, size_t S>
// T							&FtArray<T, S>::iterator::operator*(void)
// {
	// return (*_ptr);
// }

template<typename T, size_t S>
T const						&FtArray<T, S>::iterator::operator*(void) const
{
	return (*_ptr);
}
	// * MEMBER FUNCTIONS / METHODS * //
template<typename T, size_t S>
void						FtArray<T, S>::iterator::setPtr(T const *ptr)
{
	this->_ptr = ptr;
	return ;
}
// template<typename T, size_t S>
// void						FtArray<T, S>::iterator::printAdress(void)
// {
	// std::cout << (void*)_ptr << std::endl;
	// return ;
// }