#include <iostream>
#include <string>

void stack_size_estimate(std::byte* stack_bottom_addr)
{
	std::byte data[1024];
	std::cout << stack_bottom_addr - data << '\n';
	stack_size_estimate(stack_botttom_addr);
}

void estimate_driver()
{
	std::byte b;
	stack_size_estimate(&b);
}

//Placement New
class User
{
private:
	std::string name_ = "";
public:
	User() = default;
	User(std::string n)
	{
		name_ = n;
	}
};

void placement_new_ex()
{
	std::byte* memory = std::malloc(sizeof(User));
	User* user = ::new (memory) User("john");

	//Do some stuff

	//Dealloc
	user->~User();
	std::free(memory);
}

#include <memory>
//other way is more recommended
void placement_new_ex2()
{
	std::byte* memory = std::malloc(sizeof(User));
	User* user_ptr = reinterpret_cast<User*>(memory);
	std::unitialized_fill_n(user_ptr, 1, User("john"));
	std::destroy_at(user_ptr);
	std::free(memory);

	//We also have construct at (C++20)
	//std::construct_at(user_ptr, User("john"));
}

void* operator new(size_t size)
{
	void* p = std::malloc(size);
	std::cout << "allocated " << size << " byte(s)\n";
	return p;
}

void operator delete(void* p)
{
	std::cout << "Deleted memory\n";
	return std::free(p);
}

void using_operator_overloads()
{
	//executes print statements above
	char* p = new char{ 'a' };
	delete p;
}

//With arrays as well
void* operator new[](size_t size)
{
	void* p = std::malloc(size);
	std::cout << "Allocated " << size << " byte(s) with new[]\n";
	return p;
}

void operator delete[](void *p)
{
	std::cout << "Deleted memory with delete[]\n";
	return std::free(p);
}

class Document
{
	std::string title_;
	std::string context_;
public:
	Document() = default;
	Document(std::string t, std::string c)
	{
		title_ = t;
		context_ = c;
	}

	void* operator new(size_t size)
	{
		return ::operator new(size);
	}

	void operator delete(void* p)
	{
		return ::operator delete(size);
	}
};

void ex_with_class()
{
	Document* p = new Document; //Use class specific operator new
	delete p;

	Document* p2 = ::new Document; //Use global operator new
	::delete p2;
}