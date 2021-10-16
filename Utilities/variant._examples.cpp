#include <utility>

void variant_example()
{
	using VariantType = std::variant<int, std::string, bool>;

	VariantType v;
	std::holds_alternative<int>(v); //true if int is first alternative

	v = 7;

	std::holds_alternative<int>(v); // true
	v = std::string{ "Anne" };
	std::holds_alternative<int>(v); // false
	v = false;
	std::holds_alternative<bool>(v); // true

	std::cout << "VariantType: " << sizeof(VariantType);
	std::cout << "std::string: " << sizeof(std::string);
	std::cout << "size_t: " << sizeof(size_t);
}

void visiting_variants()
{
	std::variant<int, bool, float> var;
	std::visit([](auto&& val) {std::cout << val; }, var);
}

void variant_containers()
{
	using VariantType = std::variant<int, std::string, bool>;

	std::vector<VariantType>v{ 42, "needles", true };

	for (const auto& item : v)
	{
		std::visit([](const auto& x) {std::cout << x << '\n'; }, item);
	}
}