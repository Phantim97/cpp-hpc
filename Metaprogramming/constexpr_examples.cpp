#include <type_traits>

struct Bear
{
	void roar() const
	{
		std::cout << "Roar";
	}
};

struct Duck
{
	void quack() const
	{
		std::cout << "Quack";
	}
};

template<typename Animal>
void speak(const Animal& a)
{
	if (std::is_same_v<Animal, Bear>)
	{
		a.roar();
	}
	else if (std::is_same_v<Animal, Duck>)
	{
		a.quack();
	}
}

template<typename Animal>
void speak_compile_time(const Animal& a)
{
	if constexpr(std::is_same_v<Animal, Bear>)
	{
		a.roar();
	}
	else if constexpr (std::is_same_v<Animal, Duck>)
	{
		a.quack();
	}
}