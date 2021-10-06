#include "Performance Metrics/ScopedTimer.h"
#include <array>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

struct SmallObject
{
	std::array<char, 4> data_ = {};
	int score_ = std::rand();
};

struct BigObject
{
	std::array<char, 256> data_ = {};
	int score_ = std::rand();
};

void size_comparrison()
{
	std::cout << sizeof(SmallObject) << '\n';
	std::cout << sizeof(BigObject) << '\n';
}

template <typename T>
int inline sum_scores(const std::vector<T>& objs)
{
	ScopedTimer t{ "sum_scores" };

	int sum = 0;
	for (size_t i = 0; i < objs.size(); i++)
	{
		sum += objs[i].score_;
	}

	return sum;
}

//compare iteration in struct size comparison 

void testing()
{
	std::vector<SmallObject> small_objs = std::vector<SmallObject>(1000000);
	std::vector<BigObject> big_objs = std::vector<BigObject>(1000000);

	int sum = 0;
	sum += sum_scores(small_objs);
	sum += sum_scores(big_objs);
}

struct User
{
	std::string name_;
	std::string username_;
	std::string password_;
	std::string seq_q_;
	std::string seq_a_;
	short level = 0;
	bool is_playing_ = false;
};

//Roughly 11 ms
int num_users_at_level(const std::vector<User>& users, short level)
{
	ScopedTimer t{ "num_users_at_level (using 128 bytes User)" };

	int num_users = 0;
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].level_ == level)
		{
			num_users++;
		}
	}

	return num_users;
}

//Roughly 10 ms
int num_playing_users(const std::vector<User>& users)
{
	ScopedTimer t{ "num_playing_users (using 128 bytes User)"};

	return std::count_if(users.begin(), users.end(), [](const User& user) {return user.is_playing_; });
}

//More optimal to split the structs 4ms and 3ms for above functions respectively
struct AuthInfo
{
	std::string username_;
	std::string password_;
	std::string seq_q_;
	std::string seq_a_;
};

struct User
{
	std::string name_;
	std::unique_ptr<AuthInfo> auth_info_;
	short level = 0;
	bool is_playing;
};