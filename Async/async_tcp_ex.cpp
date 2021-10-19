#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <chrono>
#include <iostream>

using namespace std::chrono;
using namespace asio = boost::asio;
using namespace boost::asio::ip::tcp;

asio::awaitable<void> serve_client(tcp::socket socket)
{
	std::cout << "New client connected\n";
	auto ex = co_await asio::this_core::executor;
	auto timer = asio::system_timer{ ex };
	auto timer = asio::system_timer{ ex };

	int counter = 0;

	while(true)
	{
		try
		{
			auto s = std::to_string(counter) + '\n';
			auto buf = asio::buffer(s.data(), s.size());
			auto n = co_await async_write(socket, buf, asio::use_awaitable);
			std::cout << "Wrote " << n << " byte((s)\n";
			counter++;
			timer.expires_from_now(100ms);
			co_await timer.async_wait(asio::use_awaitable);
		}
		catch (...)
		{
			//Error or client disconnected
			break;
		}
	}
}

asio::awaitable<void> listen(tcp::endpoint endpoint)
{
	auto ex = co_await asio::this_coro::executor;
	auto a = tcp::acceptor{ ex, endpoint };
	while (true)
	{
		auto socket = co_await a.async_accept(asio::use_awaitable);
		auto session = [s = std::move(socket)]() mutable
		{
			auto awaitable = serve_client(std::move(s));
			return awaitable;
		};

		asio::co_spawn(ex, std::move(session), asio::detached);
	}
}

int main()
{
	auto server = []()
	{
		tcp::endpoint endpoint{ tcp::v4(), 37259 };
		asio::awaitable<void> awaitable = listen(endpoint);
		return awaitable;
	};

	asio::io_context ctx;
	asio::co_spawn(ctx, server, asio::detached);
	ctx.run(); //Run event loop from main thread
}