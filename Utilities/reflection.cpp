#include <utility>
#include <iostream>
#include <string>

class Player
{
private:
	std::string name_;
	int level_;
	int score_;
public:
	Player (std::string name, int level, int score)
	{
		name_ = name;
		level_ = level;
		score_ = score;
	}

	auto reflect() const
	{
		return std::tie(name_, level_, score_);
	}
};