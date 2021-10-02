#include <array>

constexpr int kL1CacheCapacity = 640000; // Based on my system L1 Data Cache Size
constexpr int kSize = kL1CacheCapacity / sizeof(int);

using MatrixType = std::array<std::array<int, kSize>, kSize>;

void cache_thrashing(MatrixType& matrix)
{
	int counter = 0;

	for (int i = 0; i < kSize; i++)
	{
		for (int j = 0; j < kSize; j++)
		{
			matrix[i][j] = counter++; //causes program to go 40 ms
			//matrix[j][i] = counter++; //causes program to go 800+ ms
		}
	}
}