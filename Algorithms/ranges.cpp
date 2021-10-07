#include <algorithm>
#include <vector>

void varying_sorts()
{
	std::vector<int> values = { 9,2,5,3,4 };

	//sort using std algorithms
	std::sort(values.begin(), values.end());

	//Sort using the constrained algorithms under std::ranges
	std::ranges::sort(values);
	std::ranges::sort(values.begin(), values.end());
}

//Generic Function to work with any container 

void print(auto&& r)
{
	std::ranges::for_each(r, [](auto&& i) {std::cout << i << ' '; });
}

//template to replace auto
template <typename T>
void print2(T&& r)
{
	std::ranges::for_each(r, [](T&& i) {std::cout << i << ' '; });
}

void transform_sample()
{
	std::vector<int> in = { 1, 2, 3, 4 };
	std::vector<int> out(in.size());
	auto lambda = [](auto i&&) {return i * i; };

	std::ranges::transform(in, out.begin(), lambda);

	print(out);
}

#include <numeric> //for itoa

//generating elements
void gen_elems()
{
	//flat initialization
	std::vector<int> v(4);
	std::ranges::fill(v, -1);
	print(v); //Prints: -1, -1, -1, -1

	//random initialization
	std::vector<int> v2(4);
	std::ranges::generate(v, std::rand);
	print(v2); //Prints: 23424 78645437 72597 1231319 (random initialization)

	//itoa from numeric generates values in increasing order
	std::vector<int> v3(6);
	std::itoa(v.begin(), v.end(), 0);
	print(v3); //Prints: 0 1 2 3 4 5
}

void sorting_elems()
{
	std::vector<int>v = { 4,3,2,3,6 };
	std::ranges::sort(v);
	print(v);
}

void finding_elems()
{
	std::list<int> l = { 2,4,3,2,3,1 };
	std::list<int>::iterator it = std::ranges::find(col, 2);

	if (it != l.end())
	{
		std::cout << *it << '\n';
	}
}

void binsrch()
{
	std::vector<int> v = { 2,2,3,3,3,4,5 };
	bool found = std::ranges::binary_search(v, 3);
	std::cout << std::boolalpha << found << '\n'; //output true

	assert(std::ranges::is_sorted(v));
}

void bounds()
{
	std::vector<int> v = { 2,2,3,3,3,4,5 };

	//Note: I wonder if performance differs between these (probably not)
	std::vector<int>::iterator it = std::ranges::lower_bound(v, 3);
	if (it != v.end())
	{
		int idx = std::distance(v.begin(), it);
		std::cout << "Low bound Index: " << idx << '\n';
	}

	std::vector<int>::iterator it2 = std::ranges::upper_bound(v, 3);
	if (it2 != v.end())
	{
		int idx = std::distance(v.begin(), it2);
		std::cout << "Upper bound Index: " << idx << '\n';
	}
}

