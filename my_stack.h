/*
*	Copyright (c) 2021 Enes AYGUN
*	@file		my_stack.h
*	@details	The Stack template class is a container adapter that gives the programmer the functionality of a stack - specifically,
				a LIFO (last-in, first-out) data structure.
*	@author		Enes AYGUN, aygun.enes@outlook.com

*	@note		This implementation not a proffesional but this helpfully understand the stack interface.
				Please contact with me for improvements or anything.
*/

/*include guard*/
#ifndef MY_STACK_H
#define MY_STACK_H

/*Libraries*/
#include <deque>	// For wrapped underlying container

template<typename T, typename C = std::deque<T>>
class Stack;

template<typename T, typename C>
bool operator==(const Stack<T, C>& lhs, const Stack<T, C>& rhs)
{
	return lhs == rhs;
}

template<typename T, typename C>
bool operator!=(const Stack<T, C>& lhs, const Stack<T, C>& rhs)
{
	return lhs != rhs;
}

template<typename T, typename C>
bool operator<(const Stack<T, C>& lhs, const Stack<T, C>& rhs)
{
	return lhs < rhs;
}

template<typename T, typename C>
bool operator<=(const Stack<T, C>& lhs, const Stack<T, C>& rhs)
{
	return lhs <= rhs;
}

template<typename T, typename C>
bool operator>(const Stack<T, C>& lhs, const Stack<T, C>& rhs)
{
	return lhs > rhs;
}

template<typename T, typename C>
bool operator>=(const Stack<T, C>& lhs, const Stack<T, C>& rhs)
{
	return lhs >= rhs;
}


template<typename T , typename C = std::deque<T>>
class Stack {
public:

	/* Type Alias */
	using container_type  = C;
	using value_type      = typename C::value_type;
	using size_type       = typename C::size_type;
	using reference       = typename C::reference;
	using const_reference = typename C::const_reference;
	
	/* Constructors */
	Stack() = default;
	
	explicit Stack(const C& cont) : c(cont) {} 

	explicit Stack(C&& cont) : c(std::move(cont)) {} 

	Stack(const Stack& other) : c(other.c) {}

	Stack(Stack&& other) : c(std::move(other.c)) {}

	template <typename Alloc, std::enable_if_t<std::uses_allocator_v<C, Alloc>, int> = 0>
	explicit Stack (const Alloc& alloc)  : c(alloc) {}

	template <typename Alloc, std::enable_if_t<std::uses_allocator_v<C, Alloc>, int> = 0>
	Stack(const C& cont, const Alloc& alloc) : c(cont, alloc) {}

	template <typename Alloc, std::enable_if_t<std::uses_allocator_v<C, Alloc>, int> = 0>
	Stack(C&& cont, const Alloc& alloc) : c(std::move(cont) , alloc) {}

	template <typename Alloc, std::enable_if_t<std::uses_allocator_v<C, Alloc>, int> = 0>
	Stack(const Stack& other, const Alloc& alloc) : c(other.c, alloc) {}

	template <typename Alloc, std::enable_if_t<std::uses_allocator_v<C, Alloc>, int> = 0>
	Stack(Stack&& other, const Alloc& alloc) : c(std::move(other.c), alloc) {}


	/* Element Access*/
	reference top()
	{
		return c.back();
	}

	const_reference top()const
	{
		return c.back();
	}
	
	/* Capacity */
	bool empty()const
	{
		return c.empty();
	}

	size_type size()const
	{
		return c.size();
	}

	/* Modifiers */
	void push(const T& val)
	{
		c.push_back(val);
	}

	void push(T&& val)
	{
		c.push_back(std::move(val));
	}

	template<typename ...Args>
	decltype(auto) emplace(Args&&...args)
	{
		return c.emplace_back(std::forward<Args>(args)...);
	}

	void pop()
	{
		c.pop_back();
	}

	void swap(Stack& other)
	{
		std::swap(c, other.c);
	}

	/* Operator Overloading */
	friend bool operator== <>(const Stack&, const Stack&);
	friend bool operator!= <>(const Stack&, const Stack&);
	friend bool operator<  <>(const Stack&, const Stack&);
	friend bool operator>  <>(const Stack&, const Stack&);
	friend bool operator<= <>(const Stack&, const Stack&);
	friend bool operator>= <>(const Stack&, const Stack&);

protected:
	C c{};

};

template<typename T, typename C>
void swap(Stack<T, C>& lhs, Stack <T, C> rhs) noexcept(noexcept(lhs.swap(rhs)))
{
	lhs.swap(rhs);
}

template< typename T, typename C, typename Alloc>
struct std::uses_allocator<Stack<T, C>, Alloc> : std::uses_allocator<C, Alloc>::type { };

#endif // !STACK_H

