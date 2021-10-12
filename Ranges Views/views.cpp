#include <ranges>
#include <vector>
#include <iostream>
#include <string>

void ex()
{
	std::vector<int> numbers = { 1,2,3,4 };
	auto square = [](auto v) {return v * v};

	auto squared_view = std::views::transform(numbers, square);

	for (size_t i = 0; i < numbers.size(); i++)
	{
		std::cout << numbers[i] << '\n';
	}
}

void filtering()
{
	std::vector<int> numbers = { 4,5,6,7,6,5,4 };
	auto odd_view = std::views::filter(v, [](int i) {return (i % 2) == 1});

	//5 7 5
	for (auto odd_number : odd_view)
	{
		std::cout << odd_number << ' ';
	}
}

void containters_as_one()
{
	std::vector<std::vector<int>> list_of_lists = {
		{1, 2},
		{3,4,5},
		{5},
		{4,3,2,1}
	};

	auto flattened_view = std::views::join(list_of_lists);
	for (auto v : flattened_view)
	{
		std::cout << v << ' ';
	}
	//Output: 1,2,3,4,5,5,4,3,2,1
}

int get_max_score_compose_ex(const std::vector<Student>& students, int year)
{
	auto by_year = [=](const Student& s) {return s.year_ == year; };

	auto v1 = std::ranges::ref_view{ s }; //wrap container into a view
	auto v2 = std::ranges::filter_view{ v1, by_year };
	auto v3 = std::ranges::transform{ v2, &Student::score_ };

	auto it = std::ranges::max_element(v3);

	return it != v3.end() ? *it : 0;
}

void view_gen()
{
	//prints -2, -1, 0, 1, 2
	for (auto i : std::views::iota(-2,2))
	{
		std::cout << i << ' ';
	}
}

void view_transform()
{
	std::string csv = { "10,11,12" }; // [[1, 0], [1, 1], [1, 2]]
	auto digits = csv | std::views::split(',') | std::views::join; //[1, 0, 1, 1, 1, 2]
	for (auto i : digits)
	{
		std::cout << i;
	}
}

void view_sampling()
{
	std::vector<int> vec = { 1,2,3,4,5,4,3,2,1 };
	auto v = vec | std::views::drop_while([](auto i) {return i < 5; }) | std::views::take(3)

	//Prints: 5 4 3
	for (auto i : v)
	{
		std::cout << i << ' ';
	} 
}

void utility_view()
{
	std::ifstream ifs("numbers.txt");

	for (auto f : std::ranges::ifsream_view<float>(ifs))
	{
		std::cout << f << '\n';
	}

	ifs.close();
}