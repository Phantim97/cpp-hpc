#include <algorithm>
#include <vector>
#include <iostream>

struct Student
{
	int year_ = 0;
	int score_ = 0;
	std::string name_ = "";
	// ...
};

int get_max_score(std::vector<Student>& students, int year)
{
	auto by_year = [=](const Student& s) {return s.year_ == year; }

	std::vector<Student> v;
	std::ranges::copy_if(students, std::back_inserter(v), by_year);
	auto it = std::ranges::max_element(v, std::less{}, &Students::score_);

	if (it != v.end())
	{
		return it->score;
	}

	return 0;
}

//Using views from the Ranges library
#include <ranges>
int max_value(auto&& range)
{
	const auto it = std::ranges::max_element(range);

	if (it != range.end())
	{
		return *it;
	}

	return 0;
}

int get_max_score_views(const std::vector<Students>& students, int year)
{
	const auto by_year = [=](auto&& s) {return s.year_ == year};

	return max_value(students | std::views::filter(by_year) | std::views::transform(&Student::score_));
}

void ex()
{
	std::vector<Student> students = {
		{3, 120, "Niki"},
		{2, 140, "Karo"},
		{3, 190, "Sirius"},
		{2, 110, "Rani"}
	};

	int score = get_max_score(students, 2);
	std::cout << score << '\n'; //prints 140
}