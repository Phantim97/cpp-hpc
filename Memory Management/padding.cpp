#include <iostream>

//24 bytes
class Document_RandomInit
{
	bool is_cached = false;
	std::byte padding1[7]; //Invisible padding inserted by compiler
	double rank_ = 0.0;
	int id = 0;
	std::byte padding2[4]; //Invisible padding inserted by compiler
};

//16 bytes
class Document_Proper
{
	double rank_ = 0.0;
	int id_ = 0;
	bool is_cached = false;
	std::byte padding[3]; //Invisible Padding inserted by the compiler
};