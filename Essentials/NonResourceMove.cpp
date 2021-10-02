#include <vector>
#include <initializer_list>

class Menu
{
private:
	int index_ = -1;
	std::vector<std::string> items_;

public:
	Menu(const std::initializer_list<std::string>& items)
	{
		items_ = items;
	}

	//To resolve crashes it is best to override the moves as such
	Menu(Menu&& other) noexcept
	{
		std::swap(items_, other.items_);
		std::swap(index_, other.index_);
	}

	Menu& operator=(Menu&& other) noexcept
	{
		std::swap(items_, other.items_);
		std::swap(index_, other.index_);
		return *this;
	}

	void select(int i)
	{
		index_ = i;
	}

	std::string selected_item() const
	{
		if (index_ != -1)
		{
			return items_[index_];
		}
		else
		{
			return "";
		}
	}
};