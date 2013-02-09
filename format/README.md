format
======

A typesafe c++11 class for formatting strings using composite based formats and specifiers.

basic usage is:

```c++

cout << format("A bear walked up {0} miles and saw {1}.", 20, "an eagle");

```

you can also do this:

```c++
format f("{2} saw {0} {1}!");

f.arg(20, "eagles");

f.arg("A bear");

string str = f; // will equal "A bear saw 20 eagles!"
```

you can also specify type formatting:

```c++
format f("{0:f2}", 123.45278);

f.str() == "123.45"; // floating point with precision 2

format f("{0:X}", 10);

f.str() == "0A"; // uppercase hexidecimal

```

or:

```c++
format f("{0,8} h2", "h1");

f.str() == "      h1 h2"; // right aligned spacing

format f("{0,-8:f2} cm", 23.45213);

f.str() == "23.45   cm"; // left aligned spacing

```

the class will throw *invalid_argument* exception on errors:

```c++

format f("{2} arg"); // throws an exception. no 0 or 1 specifier


format f("{0}", "test", "two"); // throws an exception. missing specifier

```


format plays nice with streams:

```c++

  ofstream myfile;
  myfile.open ("test.txt");

  format f("a bear {0} for a {1}");

  f.arg("went", "walk");

  // myfile << f;

  f.print(myfile); // does the same as above

  // myfile will contain "a bear went for a walk"
  myfile.close();

```

requirements
============
- a c++11 compiler that supports variadic templates

optional
========
- [igloo](http://igloo-testing.org) unit testing headers
- [premake](http://industriousone.com/premake) build configuration

compiling
=========

here's what I used for testing:

clang++ -g -std=c++11 -stdlib=libc++ -o format_test format.cpp format_test.cpp; ./format_test


formatting
==========

I borrowed the feel of [composite formating](http://msdn.microsoft.com/en-us/library/txafckwd.aspx) from c#.

basic structure I use here is:

```

+------------------> opening tag
|    +-------------> width seperator
|    |    +--------> format seperator
|    |    |
{  0 , -8 : F 2 } -> closing tag

   |   |    | |
   |   |    | +----> formating argument, variable length, reserved for future use
   |   |    +------> type of formating, see below
   |   +-----------> width of argument, integer, optional negative sign indicating left align
   +---------------> argument index, integer

```

format types
============

- **x**: lower case hexidecimal
- **X**: upper case hexidecimal
- **o**: octal
- **f**: floating point values
- **e**: scientific floating point
- **E**: uppercase scientific floating point

some examples are:

```
{0,-8}  // left align value with a width of 8
{1,4:X} // align right a hexidecmal value with a width of 4
{2:E}   // scientific floating point
```

licensing
=========

copyrighted under the Lesser GNU Public License

