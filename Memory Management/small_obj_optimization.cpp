#include <iostream>

size_t allocated = 0;

//Overload operator new and delete to track allocations
void* operator new(size_t size)
{
	void* p = std::malloc(size);
	allocated += size;
	return p;
}

void operator delete(void* p) noexcept
{
	return std::free(p);
}

void alloc_main()
{
	allocated = 0;
	std::string s = std::string{""}; //Elaborate with different string sizes

	std::cout << "stack space = " << sizeof(s) << ", capacity = " << s.capacty() << '\n';

	s = { "1234567890123456789012" };
	s = { "12345678901234567890123" }; //should use heap space here at 32 since capacity was last at 22 above
}

//all are 8 bytes so 23 in total, char pointer is a pointer to dynamically
//allocated memory that will hold strings
struct Long
{
	size_t capacity_ = 0;
	size_t size_ = 0;
	char* data_;
};

//Compile time constant needs no capacity size
struct Short
{
	unsigned char size_ = 0;
	char data_[23];
};

//Now combine both with a union
//Check the lsb of capacity in long and size_ in short to determine which union to use
union u
{
	Short short_layout_;
	Long long_layout_;
};