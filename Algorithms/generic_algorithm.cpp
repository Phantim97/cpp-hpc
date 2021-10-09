#include <vector>

//non generic (only for int vector)(
bool contains(std::vector<int>& arr, int v)
{
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (arr[i] == v)
		{
			return true;
		}
	}

	return false;
}

//Generic version
template <typename Iterator, typename T>
bool contains(Iterator begin, Iterator end, const T& v)
{
	for (Iterator it = begin, it != end, it++)
	{
		if (*it == v)
		{
			return true;
		}
	}

	return false;
}

void driver_code()
{
	std::vector<int> v = { 3,4,2,4 };
	if (contains(v.begin, v.end(), 3))
	{
		// Do some code
	}
}

//Force it to be even more generic (only data structure needed, no iterators)
bool contains(std::ranges::ranges auto& r, const auto& x)
{
	auto it = std::begin(r);
	auto sentinel = std::end();
	return contains(it, sentinel, x);
}

void driver_code2()
{
	std::vector<int> v = { 3,4,2,4 };
	if (contains(v, 3))
	{
		// Do some code
	}
}

//Generic data structure
struct Grid
{
	size_t w_ = 0;
	size_t h_ = 0;
	std::vector<int> data_{};

	Grid(size_t w, size_t h)
	{
		w_ = w;
		h_ = h;
		data_.resize(w * h);
	}

	//Version 1 clumsy
	/*auto get_row(size_t y)
	{
		auto left = data_.begin() + w_ * y;
		auto right = left + w_;
		return std::make_pair(left, right);
	}*/

	//Cleaner Version
	/*auto get_row(size_t y)
	{
		auto first = data_.begin() + w_ * y;
		auto sentinel = first + w_;
		return std::ranges::subrange{ first, w_ };
	}*/

	//Lazier version
	auto get_row(size_t y)
	{
		auto first = data_.begin() + w_ * y;
		return std::views::counted(first, w_);
	}
};

void driver()
{
	Grid grid = Grid{ 10, 10 };
	size_t y = 3;

	//old impl with the pair return
	/*auto row = grid.get_row(y);
	std::generate(row.first, row.second, std::rand);
	auto num_fives = std::count(row.first, row.second, 5);*/

	auto row = grid.get_row(3);
	std::ranges::generate(row, std::rand);
	auto num_fives = std::ranges::count(row, 5);
}