#include <pthreads> //Linux header

void set_affinity(const std::thread& t, int cpu_)
{
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(cpu_, &cpuset);
	pthread_t native_thread = t.native_handle();
	pthread_set_affinity(native_thread, sizeof(cpu_set_t), &cpuset);
}