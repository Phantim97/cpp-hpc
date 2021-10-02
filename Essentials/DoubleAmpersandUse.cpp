struct Foo
{
	auto func() &&
	{
		
	}
};

int main()
{
	Foo a = Foo{};
	//a.func(); //Does not compile
	std::move(a).func(); //Compiles
	Foo{}.func(); //Compiles;
	return 0;
}