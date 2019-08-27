template: titleslide

# A brief introduction to C++
## Rupert Nash
## r.nash@epcc.ed.ac.uk

---

template: titleslide
# Introduction

---
# Assumptions

- You are a decent programmer in another language

- You know how to use the shell

- You have access to a terminal in front of you with a C++ compiler

---
# What this is not!

Writing efficient software, more than anything, requires you to choose
an appropriate algorithmic approach for your problem.

<!-- For lots on how to do this well, consider the Parallel Design Patterns course. -->

Here we want to take a lower-level approach and talk about how to
implement patterns efficiently using C++.

---
# What is "scientific computing"?

Both HPC and data science, when you actually come to running a
program, are about getting a large amount of data from memory to a
core, doing something useful to it, and storing it again.

This is why FORTRAN is still relevant!

But it does force you to confront this all time.

C++ is all about building abstractions and composing them.

![:thumb](I will talk about a few and give some suggestions of
default rules)

---
# These few lectures

We could spend a whole semester going in depth on C++, so we've picked
a handful of features to cover that you really need to write modern
C++ for technical computing.

This is not trying to teach the *whole language* in the many different
styles that people have developed over the decades.

Please ask questions any time!
<!-- - Basic syntax and concepts of the language -->

<!-- - References and memory -->

<!-- - Overloading -->

<!-- - Classes -->

<!-- - Templates -->

---
# The misunderstood monster

.center[![:scale_img 30%](frank_mon.jpg)]

By Universal Studios - Dr. Macro, Public Domain,
https://commons.wikimedia.org/w/index.php?curid=3558176

---
# The misunderstood monster

- Large: the C++17 standard is about 1600 pages

- Composed of many parts: C, classes, generics, functional
  programming, exceptions, the vast library, ...

- Inspires dread in those do not understand it

- Dangerous:
> "C makes it easy to shoot yourself in the foot;
> C++ makes it harder, but when you do it blows your whole leg
> off." - Bjarne Stroustrup

- "Expert friendly"

---
# Octopus vs Swiss Army knife

> "C++ is an octopus made by nailing extra legs onto a dog" - Steve Taylor

.center[![:scale_img 40%](octodog.jpg) ![:scale_img 40%](sak.jpg)]

But you can cut off some extra legs to get the right dog for your
program!

???

Why is it called C++17?

Because that's how many legs they had to nail on to "fix" the octopus.

---
# The philosophy of C++ (community)

-   General purpose

-   Flexible by allowing developers to build abstractions (and provides
    a large number through the library)

-   Performance and efficiency are always targeted "you only pay for
    what you use"

-   Use the powerful type system to express intent

-   Communicate with the reader, not the compiler

---
# C++ is alive!

C++ is a work in progress.

Every three years there is a new update to the International Standard

Next one in 2020 will include various fun things, the biggest change
will probably be "modules".

---
# References
-   Bjarne Stroustrup, "Programming: Principles and Practice Using C++"
    (2nd Ed.). Assumes very little but it's long

-   Bjarne Stroustrup, "A Tour of C++". Assumes you're an experience
    programmer and is quite brief - recently updated for C++17

-   Best online *reference* is <http://en.cppreference.com/>
    (comes in other human languages too!)

-   Scott Meyers, "Effective Modern C++", 2014. This is *the* book to
    get once you know your way around C++, but you want to improve.
    Teaches lots of techniques and rules of thumb for writing correct,
    idiomatic, maintainable code.

-   [stackoverflow.com](stackoverflow.com) has a lot of good questions
    about C++ (look for ones with at least 100 up-votes).

---
template: titleslide
# But first\...

---
name: hello
# Hello!

```C++
#include <iostream>

int main() { 
  std::cout << "Hello, world!" << std::endl;
}
```

---
template: hello

```
$ g++ --std=c++11 hello.cpp -o hello
$ ./hello 
Hello, world!
```

---
template: hello

- The preprocessor runs first

- The `#include` directive copies the contents of another file into
  the current compilation unit.

- The angle brackets `<...>` tell it to look only in system
  directories.

- This includes the `iostream` standard library header

---
template: hello

- Every program must have exactly one main function.

- The compiler and OS arrange for this to be called when you run it.

- (Not shown, but you can also get the command line arguments)

---
template: hello

- `std` is the standard library namespace.

- A namespace allows scoping of names (much like a filesystem has
  directories).

- The scope resolution operator `::` lets us access something from
  inside a namespace.

- `cout` represents console output (i.e. standard output / stdout)

---
template: hello

- The standard library uses the bitwise left shift operator (`<<`) to mean
  stream insertion

- I.e. output the right hand side to the left.

- Every statement in C++ must be terminated with a semicolon (`;`)

- The language treats all whitespace (space, tab, line break) the same

---

template: titleslide
# Your turn

---
# Machine choice

You can use your laptop or Cirrus

__Your machine__ : you need a C++ compiler that supports at least
C++11. If you use Windows and MSVC we may not be able to help
much... Sorry!

__Cirrus__: We passed out log in details. Connect via SSH:
```
ssh trainingXXX@cirrus-login2.epcc.ed.ac.uk
```
Or follow the instructions for MobaXterm (as detailed on the ARCHER
training webpage https://www.archer.ac.uk/training/courses/software.php)

Once connected you need to load the up-to-date compilers:
```
module load gcc/8.2.0
```

---
# Getting the source code

All these slides and the exerices are available on GitHub:
https://github.com/EPCCed/2019-08-27-ModernCpp/

You also can view the slides and other materials in a browser by going
to https://EPCCed.github.io/2019-08-27-ModernCpp/

In the terminal, you need to use git get a copy of the exercises:
```
git clone https://github.com/EPCCed/2019-08-27-ModernCpp/
```

Then you can change to the directory with this simple program
```
cd 2019-08-27-ModernCpp/lectures/cpp-intro/hello
```

---
# Say hello

View the program source

```
vim hello.cpp
emacs hello.cpp
```

Compile the program:

```
g++ --std=c++11 hello.cpp -o hello
```

No output means success!

Run it:
```
./hello
```

---
template: titleslide
# A few things

---
# C++:

- It is a typed language - all variables must be declared
  - But you can often tell the compiler to figure out the type

- Counts from zero (like C, Python) not from one (like Fortran)

---
template: titleslide
# Variables

---
# Variables

A variable is

- an object

or

- a reference

that is declared to have a type and a name.

???

We'll talk about references later

---

# Objects

An object is a region of storage that has:

- type
- size
- value
- lifetime

???

types are next, explain a bit about the others

---

template: titleslide
# Types

---
# What is a type?

> "Objects and expressions have a property called type, which
> both restricts the operations that are permitted for those entities
> and provides semantic meaning to the otherwise generic sequences of
> bits." -- <https://en.cppreference.com>

---
# Fundamental types

| Type        | Description |
|-------------|-------------|
| `void`      | Nothing - used to indicate a function returns no value.|
| `bool`      | `true` or `false` |
| `int`       | Standard *signed* integer for your machine. *At least* 16bits. *Usually* 32 bits.|
| `double`    | Double-precision floating point. *Usually* an IEEE 754 64 bit number.|
| `std::byte` | Raw untyped memory |

There are also `unsigned` versions of the integer types

The header `<cstdint>` provides fixed-width integer types available on
your implementation: e.g. `std::int32_t` and `std::uint64_t`.

???

There are others:
- single precision floats
- short/long/long long ints

Go look them up on CPP Reference as you need to

---

# Strings

The standard library has a class* called `string` that holds a string
of text characters.

You have to `#include <string>` to use it which includes the "header
file" that contains all the information the compiler needs to let you
use it.

```
#include <iostream>
#include <string>

int main() {
  std::string message = "Hello, world";
  std::cout << message << std::endl;
}
```

???
Character encoding in the standard library is a bit of a mess.

Partially fixed in C++20

Find a library if you need to do serious text handling because Unicode
is super complicated

---
template: titleslide
# Functions

---
# Functions

A function encapsulates a piece of code between braces (curly
brackets, `{}`) and gives it a name so you can use it later.

```C++
void say_hello() {
  std::cout << "Hello, world!" << std::endl;
}

int main(int argc, char* argv[]) {
  say_hello();
}
```
???

You declare function by first giving the return type (`void`)

Then the name (`say_hello`)

Then the list of zero or more parameters

---
# Functions

You must declare the return type and parameter types.

Parameters are local variables that are initialised by the caller.

Return a value with the `return` statement - the type of the
expression must be (convertible to) the declared return type.

```C++
int sum(int a, int b) {
  return a + b;
}
```

Can alse use trailing return type (aka "east end functions"):
```C++
auto sum(int a, int b) -> int {
  return a + b;
}
```

???

First sight of the `auto` keyword - this basically says to the
compiler: "figure it out from what follows"

In this case, by us telling it later

---
# Functions

To use a function - to "call" it - you give its name and then provide
the arguments in parentheses

```
int main () {
  int x = 42;
  std::cout << "Total = " << sum(x, 100) << std::endl;
}
```

The parameters to the function must match the (a) declaration.

---
# Function overloading

You can have multiple functions with the **same
name** but **different arguments**.
```C++
int sum(int a, int b) {
  return a + b;
}
double sum(double a, double b) {
  return a + b;
}
```

When you call `sum`, the compiler knows the types of the arguments and
will try to find the best match from all the candidates with the name.

The compiler will also try to use any built-in or user-defined
conversion rules.

---
# What happens here?

```C++
int i1 = 1;
int i2 = 2;
double d1 = 1.0;
double d2 = 2.0;
unsigned u42 = 42;
std::string name = "Alice";
std::string file = "data.csv";

std::cout << sum(i1, i2) << std::endl;
std::cout << sum(3, 72) << std::endl;
std::cout << sum(i1, u42) << std::endl;
std::cout << sum(d2, d1) << std::endl;
std::cout << sum(d2, 1e6) << std::endl;
std::cout << sum(d2, i1) << std::endl;
std::cout << sum(name, file) << std::endl;
```

---
# Operators are functions

C++ operators, for the non-fundamental types, are just functions with odd
names, e.g.:
```C++
std::string operator+(const std::string& a, const std::string& b);
```

You can then use the natural syntax when manipulating these in other
code:

```C++
std::string user_name = "alice";
auto data_file = user_name + ".csv";
```

We'll come back to this!

???

In general we'd recommend using auto quite a lot "Almost always auto"

Why?

Can't have an uninitialized variable

Add types - on RHS as constructors - when you need to ensure the type
of something (is known to the reader).


---
# Let's write some code

```C++
#include <iostream>
#include <string>

void say_hello() {
  std::cout << "Hello, world!" << std::endl;
}

int main(int argc, char* argv[]) {
  std::cout << "What is your name?" << std::endl;
  auto name = std::string{};
  // Read from the terminal
  std::cin >> name;

  // Have the program greet the user by name
  say_hello(name);
}
```

???

What I'd like you to do is change `say_hello` to accept the name it
read from the terminal, create a new message saying "Hello, $NAME!"
and print it to standard output.

I've shown here how to read a string from standard input.
