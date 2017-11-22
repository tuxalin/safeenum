
#include <iostream>

//redefine assert macro to log instead
#define SAFE_ENUM_ASSERT(cond, msg) if(!cond) std::cout << msg << "\n"

#include <safe_enum.h>

//normal declaration
SAFE_ENUM_DECLARE(Shape,
	eCircle, eSquare, eTriangle);

//or you can also declare an enum class using unsigned char
SAFE_ENUM_TYPE_DECLARE(Shape8, unsigned char,
	eCircle = 3, eSquare = 1, eTriangle = 5);

//or a custom enum with extended functions
struct Color_def {
	SAFE_ENUM_DEFINE_FORMAT(eRed = 0x1, eGreen = 0x2, eBlue = 0x4, eYellow = eRed | eGreen);

	bool hasRed() const;
};
typedef util::SafeEnum<Color_def> Color;

bool Color_def::hasRed() const
{
	Color col = static_cast<const Color&>(*this);
	return col.get() & Color::eRed;
}

// TODO: make unit tests out of these

int main()
{
	// C++11 enum classes type support, prints: 4 1
	std::cout << sizeof(Shape) << " " << sizeof(Shape8) << "\n";

	// compile time enumeration count support, prints: 3 4
	std::cout << Shape::Count << " " << Color::Count << "\n";

	// iterate through all enum values, prints: 0 1 2
	for (Shape::iterator it = Shape::first(); it != Shape::last(); ++it)
	{
		std::cout << it->get() << " ";
		//or in C++11 via explicit cast: std::cout << (int)*it << " ";
	}
	std::cout << "\n";

	// iterate until an enum value,  prints: 0 1
	for (Shape::iterator it = Shape::first(); it != Shape::eTriangle; ++it)
	{
		std::cout << it->get() << " ";
	}
	std::cout << "\n";

	// iterate through all enum values, non-contiguous, prints: 3 1 5
	for (Shape8::iterator it = Shape8::first(); it != Shape8::last(); ++it)
	{
		std::cout << (int)it->get() << " ";
	}
	std::cout << "\n";

	// iterate starting from an enum value, prints: eSquare eTriangle
	Shape shape = *(Shape::first() + 1);
	for (Shape::iterator it = shape.begin(); it != Shape::last(); ++it)
	{
		std::cout << it->str() << " ";
	}
	std::cout << "\n";
	//print ordinal, prints: 1
	std::cout << shape.ordinal() << "\n";

	//conversion from string, prints: 0 eCircle
	std::pair<bool, Shape> res = Shape::fromString("eCircle");
	std::cout << res.second.get() << " " << res.second.str() << "\n";
	assert(res.first);

	// using extended enums, prints: 1 0 0 1
	for (Color::iterator it = Color::first(); it != Color::last(); ++it)
	{
		std::cout << it->hasRed() << " ";
	}
	std::cout << "\n";

	// dynamic checks
	shape = Shape::from(2); // will set to eTriangle
	shape = Shape::from(5); // will assert
	shape.set(5); // will assert
	shape = Shape::fromUnsafe(5); // wont assert

	// bitfield support
	Color color = Color::eRed;
	color |= Color::eGreen;  // will set to eYellow
	color &= Color::eRed;  // will set to eRed
	color &= Color::eBlue; // will assert

	return 0;
}
