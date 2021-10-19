#include <vector>
#include <new>

struct alignas(std::hardware_destructive_interface_size) Element
{
	int counter_ = 0;
}

constexpr int num_threads = 8;

std::vector<Element> element(num_threads);