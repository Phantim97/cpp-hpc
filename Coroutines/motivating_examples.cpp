#include <coroutine>

//Pseudocode
Generator<int> iota(int start)
{
	for (int i = start; i < std::numeric_limits<int>::max(); i++)
	{
		co_yield i;
	}
}

//Pseudocode
Generator<int> take_until(Generator<int>& gen, int value)
{
	for (auto v : gen)
	{
		if (v == value)
		{
			co_return;
		}
		co_yield v;
	}
}

//Pseudocode
void main()
{
	auto i = iota(2);
	auto t = take_until(i, 5);
	for (auto v : t)
	{
		std::cout << v << ", ";
	}
	return 0;
} //Prints 2, 3, 4

//Pseudocode
Task<> tcp_echo_server()
{
	char data[1024];
	for (;;)
	{
		size_t n = co_await async_read(socket, buffer(data));
		co_await async_write(socket, buffer(data, n));
	}
}

//Pseudocode
auto coroutine()
{
	int value = 10;
	await something; //Suspend/Resume Point
	//...
	yield value++; //Suspend/Resume Point
	yield value++; //Suspend/Resume Point
	//...
	return;
}

auto res = coroutine(); //call
res.resume(); //resume

//Suspend resume example
//Pseudocode
auto coroutine2()
{
	int x = 0;
	yield x++; //Suspend
	g(); //Call some other funciton
	yield x++; //Suspend
	return;
}

auto co = coroutine2(); //Call subroutine to start it
//...					// Coroutine is suspended
auto a = resume(co); //Resume coroutine to get
auto b = resume(co); //next value