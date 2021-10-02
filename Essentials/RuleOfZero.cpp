class Button
{
public:
	Button() = default;

	//All of these are done by default so they don't need to be made
	//
	//Copy constructor/copy assignment
	Button(const Button&) = default;
	Button& operator=(const Button&) = default;

	//Move constructor/move assignment
	Button(Button&&) noexcept = default;
	Button& operator=(Button&&) noexcept = default;

	~Button() = default;

};