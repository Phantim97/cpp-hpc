#include <pair>
#include <tuple>
#include <iostream>

void pair_ex()
{
	std::pair<int, int> v = std::minmax({ 4,3,2,4,5,1 });
	std::cout << v.first << v.second << '\n';
}

void tuple_ex()
{
	std::tuple<int, std::string, bool> t;
	t = { 0, std::string{}, false };

	std::tuple<int, std::string, bool> t2 = std::make_tuple(42, "", true);

	int a = std::get<0>(t);
	std::string b = std::get<1>(t);
	bool c = std::get<2>(t);

	//Iterating
	for (const auto& v : t)
	{
		std::cout << v << " ";
	}

	
}

template<size_t Index, typename Tuple, typename Func>
void tuple_at(const Tuple& t, Func f)
{
	const auto& v = std::get<Index>(t);
	std::invoke(f, v);
}

void tuple_lambda_impl()
{
	std::tuple<int, std::string, bool> t = std::make_tuple(42, "sample", true);
	auto f = [](const auto& v) { std::cout << v << " "; };
	tuple_at<0>(t, f);
	tuple_at<1>(t, f);
	tuple_at<2>(t, f);
}