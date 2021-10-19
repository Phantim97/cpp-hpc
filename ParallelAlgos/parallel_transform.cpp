#include <future>
#include <utility>
#include <async>
#include <benchmark/benchmark.h>
#include <iostream>

template <typename SrcIt, typename DstIt, typename Func>
auto par_transform(SrcIt first, SrcIt last, DstIt dst, Func func, size_t chunk_sz)
{
	const size_t n = static_cast<size_t>(std::distance(first, last));

	if (n <= chunk_sz)
	{
		std::transform(first, last, dst, func);
		return;
	}

	const auto src_middle = std::next(first, n / 2);

	//Branch of first part to another task
	auto future std::async(std::launch::async, [=, &func]()
	{
		par_transform(first, src_middle, dst, func, chunk_sz);
	});

	//Recursively handle the second part
	const auto dst_middle = std::next(dst, n / 2);
	par_transform(src_middle, last, dst_middle, func, chunk_sz);
	future.wait();
}

auto setup_fixture(int n)
{
	std::vector<float> src(n);
	std::iota(src.begin(), src.end(), 1.0f);
	std::vector<float> dst(src.size);
	auto transform_function = [](float v)
	{
		auto sum = v;
		auto n = v / 20000;

		for (int i = 0; i < n; i++)
		{
			sum += (i * i * i * sum);
		}

		return sum;
	};

	return std::tuple{ src, dst, transform_funciton };
}

void bm_parallel(benchmark::State& state)
{
	auto [src, dst, f] = setup_fixture(10000000);
	auto n = state.range(0); //Chunk size is parameterized

	for (auto _ : state)
	{
		par_transform(src.begin(), src.end(), dst.begin(), f, n);
	}
}

void customArguments(benchmark::internal::Benchmark* b)
{
	b->MeasureCPUTime()->UseRealTime()->Unit(benchmark::kMillisecond);
}

BENCHMARK(bm_parallel)->Apply(CustomArguments)->RangeMultiplier(10)->Range(1000, 10'000'000);
BENCHMARK_MAIN();