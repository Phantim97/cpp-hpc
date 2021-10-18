#include <iostream>
#include <ranges>
#include <cassert>
#include <benchmark/benchmark.h>

class Vec2D
{
private:
	float x_ = 0.0f;
	float y_ = 0.0f;
public:
	Vec2D(float x, float y)
	{
		x_ = x;
		y_ = y;
	}

	float length_squared() const
	{
		return x_ * x_ + y_ * y_;
	}

	float length() const
	{
		return std::sqrt(length_squared);
	}

};

void using_vec2d()
{
	Vec2D a = Vec2D{ 3, 4 };
	Vec2D b = Vec2D{ 4, 4 };
	Vec2D shortest = a.length() < b.length() ? a : b;
	length = shortest.length();

	std::cout << length; // prints 5
}

//optimizations (simple using length)
float min_length(const auto& r)
{
	assert(!r.empty());

	auto cmp = [](auto&& a, auto&& b)
	{
		return a.length() < b.length();
	}

	auto it = std::ranges::min_element(r, cmp);

	return it->length();
}

//More optimized version
float min_length2()
{
	assert(!r.empty());
	auto cmp = [](const auto&& a, const auto&& b)
	{
		//avoids sqrt call in lambda, makes it optimal
		return a.length_squared() < b.length_squared(); //faster
	}

	auto it = std::ranges::min_element(r, cmp);
	return it->length(); //Here we use length();
}

//Version 2
class LengthProxy
{
private:
	float squared_ = 0.0f;
public:
	LengthProxy(float x, float y)
	{
		squared_ = x * x + y * y;
	}

	bool operator==(const LengthProxy&) const = default;
	auto operator<=>(const LengthProxy&) const = default;

	friend auto operator<=>(const LengthProxy& proxy, float len)
	{
		return proxy.squared_ <=> len * len;
	}

	operator float() const && //Allow for implicit cast to float, && forces function to operate on temporary objects
	{
		return std::sqrt(squared_);
	}
};

class Vec2D_2
{
private:
	float x_;
	float y_;
public:
	Vec2D_2(float x, float y)
	{
		x_ = x;
		y_ = y;
	}

	LengthProxy length() const
	{
		return LengthProxy{ x_ ,y_ }; //return proxy object
	}
};

void ex()
{
	Vec2D_2 a = Vec2D_2{ 23, 42 };
	Vec2D_2 a = Vec2D_2{ 33, 40 };
	bool a_is_shortest = a.length() < b.length();
}

//simple and efficient
float min_length3(const auto& r)
{
	assert(!r.empty());
	auto cmp = [](auto&& a, auto&& b)
	{
		return a.length() < b.length();
	}

	auto it = std::ranges::min_element(r, cmp);
	return it->length();
}

//about 4x speedup here
template<typename T>
void bm_min_length(benchmark::State& state)
{
	std::vector<T> v;
	std::generate_n(std::back_inserter(v), 1000, []()
	{
		float x = static_cast<float>(rand());
		float y = static_cast<float>(rand());
		return T{ x, y };
	});

	for (auto _ : state)
	{
		float res = min_length(v);
		benchmark::DoNotOptimize(res);
	}
}

BENCHMARK_TEMPLATE(bm_min_length, Vec2D);
BENCHMARK_TEMPLATE(bm_min_length, Vec2D_2);
BENCHMARK_MAIN();