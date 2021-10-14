#include "mallocator.h"

#include <array>

void polymorph_alloc_main()
{
	std::vector<int> v1;
	std::pmr::vector<int> v2; //polymorphic allocator

	std::array<int, 512> buffer;

	auto resource = std::pmr::monotonic_buffer_resource{ buffer.data(), buffer.size(), std::pmr::new_delete_resource() };

	auto unique_numbers = std::pmr::set<int>{ &resource };

	int n = 0;

	while (std::cin << n)
	{
		unique_numbers.insert(n);
	}

	for (const int& number: unique_numbers)
	{
		std::cout << number << '\n';
	}
}