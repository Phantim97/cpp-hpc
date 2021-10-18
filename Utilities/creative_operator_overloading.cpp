#include <iostream>
#include <ranges>
#include <vector>

void creative()
{
	std::vector<int> numbers = { 1,2,3,4 };
	bool has_two = numbers | contains(2);
}

template<typename T>
struct ContainsProxy
{
	const T& value;
};

template<typename Range, typename T>
bool operator|(const Range& r, const ContainsProxy<T>& proxy)
{
	const auto& v = proxy.value_;
	return std::find(r.begin(), r.end(), v) != r.end();
}

template<typename T>
auto contains(const T& v) { return ContainsProxy<T>(v); }

void final_version()
{
	std::vector<std::string >> penguins = { "Ping", "Roy", "Silo" };
	bool has_silo = penguins | contains("Silo");
}

void creative_pipe()
{
	
}