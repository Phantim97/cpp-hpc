#include <future>
#include <iostream>

void divide(int a, int b, std::promise<int>& p)
{
	if (b == 0)
	{
		auto e = std::runtime_error{ "Divide by zero exception" };
		p.set_exception(std::make_exception_ptr(e));
	}
	else
	{
		const int result = a / b;
		p.set_value(result);
	}
}

void main()
{
	std::promise<int> p;
	std::thread(divide, 45, 5, std::ref(p)).detach();

	auto f = p.get_future();
	try
	{
		const auto& result = f.get(); //Blocks until ready
		std::cout << "Result: " << result << '\n';
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught Exception: " << e.what() << '\n';
	}
}

//Same problem but with std::packaged_task
int divide2(int a, int b)
{
	if (b == 0)
	{
		throw std::runtime_error{ "Divide by zero exception" };
	}

	return a / b;
}

void main2()
{
	//std::async replaces the need for:
	//auto task = std::packaged_task<decltype(divide)>(divide);
	//auto f = task.get_future();

	auto future = std::async(divide, 45, 5);
	
	try
	{
		const auto& result = future.get();
		std::cout << "Result = " << result << '\n';
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught Exception: " << e.what() << '\n';
	}
}