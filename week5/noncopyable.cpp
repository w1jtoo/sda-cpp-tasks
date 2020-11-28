#include <iostream>
#include <type_traits>

class NonCopyable { 
public:
	NonCopyable() noexcept = default;
	~NonCopyable() noexcept = default;

	NonCopyable(const NonCopyable&) = delete;
};

NonCopyable get_from_function() {
	return NonCopyable();
}

int main(void) { 
	auto a = NonCopyable();
	auto b = std::move(a);

	std::cout << std::boolalpha
		<< std::is_copy_constructible<NonCopyable>::value << std::endl
		<< std::is_move_constructible<NonCopyable>::value << std::endl
		<< std::is_copy_assignable<NonCopyable>::value << std::endl
		<< std::is_move_assignable<NonCopyable>::value << std::endl;

	return 0;
}
