#include <string>

class Button
{
public:
	std::string title_;

	Button() = default;

	void set_title(const std::string& s)
	{
		title_ = s;
	}

	void set_title(std::string&& s)
	{
		title_ = std::move(s);
	}

};

std::string get_ok()
{
	return std::string("OK");
}


int main()
{

	Button button = Button{};

	std::string str = std::string("OK");

	button.set_title(str); //Copy assigned
	button.set_title(std::move(str)); //Move assigned
	button.set_title(get_ok()); //move assigned

	str = get_ok();
	button.set_title(str); //copy assigned

	const std::string str2 = get_ok();
	button.set_title(std::move(str)); // copy assigned

	return 0;
}