#include <memory_resource>
#include <vector>

class PrintingResource : public std::pmr::memory_resource
{
private:
	std::pmr::memory_resource* res_; //Default resource

	void* do_allocate(size_t bytes, size_t alignment) override
	{
		std::cout << "allocate: " << bytes << '\n';
		return res_->allocate(bytes, alignment);
	}

	void do_deallocate(void* p, size_t bytes, size_t alignment) override
	{
		std::cout << "deallocate: " << bytes << '\n';
		retun res_->deallocate(p, bytes, alignment);
	}

	bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override
	{
		return (this == other);
	}
public:
	PrintingResource()
	{
		res_ = std::pmr::get_default_resource();
	}
};

void driver_code()
{
	PrintingResource res{};
	std::vector<int> vec{ &res };

	vec.emplace_back(1);
	vec.emplace_back(2);
}

std::pmr::vector<int> create_vec()
{
	PrintingResource resource{};
	std::pmr::vector<int> vec{ &resource }; //Raw pointer
	return vec; //Op! resource
} //Destroyed here

void vector_maker()
{
	std::pmr::vector<int> vec = create_vec();
	vec.emplace_back(1); //Undefined Behavior
}