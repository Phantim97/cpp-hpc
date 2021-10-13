#include <iostream>
#include <cassert>

void alignment_test()
{
	std::cout << alignof(int) << '\n'; // Possible output is 4
}

bool is_aligned(void* ptr, size_t alignment)
{
	assert(ptr != nullptr);
	assert(std::has_single_bit(alignment)); //Power of 2

	size_t s = std::numeric_limits<size_t>::max();
	void* aligned_ptr = ptr;
	std::align(alignment, 1, aligned_ptr, s);
	return ptr == aligned_ptr;
}

void allign_allocate()
{
	int* p = new int;
	assert(is_aligned(p, 4ul)); //True

	char* c = new char{};
	size_t max_alignment - alignof(std::max_align_t);
	assert(is_aligned(p, max_alignment));

	//could be 16 bytes apart
	char* c1 = new char{ 'a' };
	char* c2 = new char{ 'b' };
}

void custom_alignment()
{
	//Separate cache lines
	alignas(64) x = 0;
	alignas(64) y = 0;
}

//Custom alignment can be done when defining a type:
struct alignas(64) CacheLine
{
	std::byte data[64];
};

void custom_stack_variable()
{
	CacheLine x;
	CacheLine y;
	assert(is_aligned(&x, 64));
	assert(is_aligned(&y, 64));
	//...
}

constexpr size_t ps = size_t{ 4096 };

struct alignas(ps) Page
{
	std::byte data_[ps];
};

void alignment_aware_alloc()
{
	Page* page = new Page{};
	assert(is_aligned(page, ps));
	//Use page
	delete page;
}