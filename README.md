# SafeEnum [![Build Status](https://travis-ci.org/tuxalin/safeenum.svg?branch=master)](https://travis-ci.org/tuxalin/safeenum)
A type-safe, powerful enumeration implementation for C++ with features like automatic string conversion and iterators.

## Features

Improves type-safety of native enum data type in C++ 03 to provide C++ 11 like enum classes.
The extended features over C++ 11 enums are:
- automatic string conversion
- dynamic checks to ensure only valid enumerations
- iterators, also for non-contiguous enumerations
- compile time enumeration count, also for non-contiguous enumerations
- multi platform support, tested on major compilers: MSVC, GCC and Clang
- support for enum method extension
	
## Installation

The safeenum implementation is header only, it's requirements are: variadic macros and unordered_map(C++03 TR1) support.

## Usage

You must use the SAFE_ENUM_DECLARE macro for declaration to be able to use the extended features:
```cpp
	SAFE_ENUM_DECLARE(Shape,
                      eCircle, eSquare, eTriangle);
                  
	//or you can also declare an enum class using unsigned char
	SAFE_ENUM_TYPE_DECLARE(Shape, unsigned char,
	                       eCircle, eSquare, eTriangle);
``` 	
If you don't wish the extended features(eg. string conversion, iterators, count) you can declare it manually:
```cpp
	struct Color_def {
	    enum type { eRed, eGreen, eBlue };
	};
	typedef util::SafeEnum<Color_def> Color;
	
	// or as before you can also declare it using unsigned char
	struct Shape_def {
	    enum type { eCircle, eSquare, eTriangle };
	};
	typedef util::SafeEnum<Shape_def, unsigned char> Shape;
``` 

If you wish to have extended features on your custom enum class use the SAFE_ENUM_DEFINE_FORMAT macro:
```cpp
    struct Shape_def {
	    SAFE_ENUM_DEFINE_FORMAT(eCircle, eSquare, eTriangle);
	    //other methods down here
	};
	typedef util::SafeEnum<Shape_def, unsigned char> Shape;
```

Be sure to check the test folder for more detailed examples.

## Contributing

Based on [Type Safe Enum on wikibooks](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Type_Safe_Enum).
Bug reports and pull requests are welcome on GitHub at https://github.com/tuxalin/safeenum.

## License

The code is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
