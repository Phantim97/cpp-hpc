#include <iostream>
#include <vector>

void implicit_resource_handling()
{
	std::vector<int> v = { 1,2,3,4,5 };
}

class RAIIConnection
{
private:
	Connection connection_;
public:
	explicit RAIIConnection(const std::string& url)
	{
		connection_ = { open_connection(url) };
	}

	~RAIIConnection()
	{
		try
		{
			close(connection);
		}
		catch (const std::exception&)
		{
			//Handle error but never throw from a destructor
		}
	}

	Connection& get()
	{
		return conneciton_;
	}
};

void send_request(const std::string& request)
{
	auto connection = open_connection("http://www.example.com");
	send_request(connection, request);
	close(connection);
}

void send_request_raii(const std::string& request)
{
	auto connection = RAIIConnection("http://www.example.com");
	send_request(connection.get(), request);
	//No need to close since RAII handles it
}

//Smart Pointers section
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

void unique_ptr_example()
{
	std::unique_ptr<User> owner = std::make_unique<User>("John");
	std::unique_ptr<User> new_owner = std::move(owner); //Transfer ownership
}

void* operator new(size_t size)
{
	void* p = std::malloc(size);
	std::cout << "allocated " << size << " byte(s)\n";
	return p;
}

void operator delete(void* p) noexcept
{
	std::cout << "deleted memory\n";
	return std::free(p);
}

void shared_ptr_example()
{
	std::shared_ptr<double> i = std::make_shared<double>(42.0);

	//Shared example:
	std::shared_ptr<double> i = std::make_shared<double>{new double{42.0}};
}

void weak_ptr_ex()
{
	std::shared_ptr<int> shared_i = std::make_shared<int>(10);
	std::weak_ptr<int> weak_i = std::weak_ptr<int>(i);

	//Maybe i.reset() happens here so that the int is deleted
	if (auto shared_i = weak_i.lock())
	{
		//We managed to convert our weak pointer to shared pointer
		std::cout << *shared_i << '\n';
	}
	else
	{
		std::cout << "weak_i has expired, shared_ptr was nullptr\n";
	}
}