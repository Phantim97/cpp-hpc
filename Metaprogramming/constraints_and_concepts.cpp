#include <concepts>
#include <type_traits>

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<typename T>
concept Number = FloatingPoint<T> || std::is_integral_v<T>;

//A range is something that we can pass to std::ranges::begin() and std::ranges::end()
template<typename T>
concept range = requires(T& t)
{
	std::ranges::begin(t);
	std::ranges::end(t);
}

template<typename T>
requires std::integral<T>
T mod(T v, T n)
{
	return v % n;
}

//Constraining types
template<typename T>
requires std::integral<T>
struct Foo
{
	T value;
};

template <std::integral T>
T mod2(T v, T n)
{
	return v % n;
}

//Function Overloading
template<typename T>
T generic_mod(T v, T n)
{
	if constexpr (std::is_floating_point_v<T>)
	{
		return std::fmod(v, n);
	}
	else
	{
		return v % n;
	}
}

//Constraints to a class
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
class Point2D
{
private:
	T x_{};
	T y_{};
public:
	Point2D(T x, T y)
	{
		x_ = x;
		y_ = y;
	}

	T x() const
	{
		return x_;
	}

	T y() const
	{
		return  y_;
	}
};