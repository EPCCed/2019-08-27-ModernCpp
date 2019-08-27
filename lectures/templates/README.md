template: titleslide
# Templates
## Rupert Nash
## r.nash@epcc.ed.ac.uk

~~~

We've hinted at this already, with `std::vector<int>`, `std::shared_ptr<Cowboy>` etc


---
# Motivation

Templates are a method of doing *metaprogramming*: a
program that writes a program.

An easy example:

```C++
int sum(int a, int b) {
  return a+b;
}
double sum(double a, double b) {
  return a+b;
}
```

What if we need this for `float`, `unsigned`, and out `Complex` class?

Going to get boring and hard to maintain quickly!

~~~

Recall the sum functions from the first lecture

---
# Template functions

```C++
template<typename T>
T sum(T a, T b) {
  return a+b;
}
```

We can *instantiate* this template for a particular type explicitly by
giving the type inside angle brackets:

```C++
std::cout << "add unsigned=" << sum<unsigned>(1U, 4U) << std::endl;
std::cout << "add floats=" << sum<float>(1.0f, 4e-2f) << std::endl;
```

???

Here the compiler will replace every use of `T` with the type you
supply and then it will compile it for you

---
# Template functions

```C++
template<typename T>
T sum(T a, T b) {
  return a+b;
}
```

You can also let the compiler do the deduction for you

```C++
std::cout << "add unsigned=" << sum(1U, 4U) << endl;
std::cout << "add floats=" << sum(1.0f, 4e-2f) << endl;
```
~~~

This is called implicit template instantiation - there are a few
wrinkles that we'll talk about

---
# Template classes

You can define a template class - i.e. a template that will produce a
class when you instatiate it.

Let's adapt our `dyn_array` container that to hold any type `T`

```C++
template<class T>
class dyn_array {
  unsigned size = 0;
  T* data = nullptr;
public:
  dyn_array ();
  dyn_array (unsigned n);
  // Copy / move?
  ~dyn_array ();
  unsigned size() const;
  const T& operator[](unsigned i) const;
  T& operator[](unsigned i);
};
```

???
Talk through the syntax of the template

We use `T*` as the type of the stored data and `T&` as the return type
of `operator[]`

---
# Type aliases

Often it is useful to be able to create a new name for a type

C++ supports a `using` declaration for this.

```C++

using MyImportantType = int;

using iter = std::map<std:string, std::vector<LongTypeName>>::iterator;
```

???

Really common when creating class templates as if you don't it may be
very hard to figure out the type parameters it was instantiated for in
from other code.

---
# Using declaration in class templates

```C++
template<class T>
class dyn_array {
  unsigned size = 0;
  T* data = nullptr;
public:
  using value_type = T;
  using reference = T&;
  using const_reference = T const&;
  // ...
  const_reference operator[](unsigned i) const;
  reference operator[](unsigned i);
};
```

---
# Where to put your implementation?

Templates are *not* executable code - they tell the compiler how to
create it.

So the definition must be available in the translation unit of the user of your template -
i.e. typically in a header file.

You can define the functions in place like:

```C++
template<class T>
class dyn_array {
public:
  dyn_array() : _size(0), _data(nullptr) {}
};
```

Or at the end of the header (or equivalently in another file that you
include at the end of your header)

```C++
template<class T>
dyn_array<T>::dyn_array(unsigned n) : _size(n) {
  _data = new T[n];
}
```

???
Point out the uglier syntax of the second form but on the other hand
the class definition shown earlier is cleaner with only the member
function declarations

---
# Templates and the One Definition Rule

So we said earlier that everything used had to be defined exactly once.

This has two exceptions:

1. Templates

2. Functions marked `inline`

These can be repeated in many "translation units" (i.e. separate
invocations of the compiler)

At link time the linker will arbitrarily pick one definition to use in
the final executable.

---
# Templates and type deduction

Recall:
```C++
template<class T>
T sum(T a, T b) {
  return a+b;
}
```

We then used this without specifying, explicitly, what type `T` was - e.g.:
```C++
int x = 1, y = 2;
auto z = sum(x, y);
```

The compiler is doing template argument deduction.

This means it examines the types of the expressions given as arguments
to the function and then tries to choose a `T` such that the type of
the argument and the expected type match.

---
# Templates and type deduction

Important to note that the template parameter `T` and the type of
function arguments might be different (but related)

```C++
template<class T>
void f(T x);

template<class T>
void ref(T& x);

template<class T>
void const_ref(T const& x);

template<class T>
void forwarding_ref(T&& x);

template <class T>
void vec(std::vector<T> x);
```

This will affect the deduced argument type

---
# Non-type template parameters

Can also parameterise template with non-types:
- integers
- pointers
- enums

E.g.:

```C++
template <int N>
class Vec;

template <int ROWS, int COLS>
class Matrix;

template<int ROWS, int COLS>
Vec<ROWS> operator*(Matrix<ROWS, COLS> const& A, Vector<COLS> const& x);
```

???
The compiler will now ensure that the matrix and vector are of compatible
shapes and if you make a mistake will give an error!

The size of the answer is correctly deduced for you

---
# Templates and type deduction

Full rules are quite complex

See Meyer's Effective Modern C++ chapter 1 - free online
https://www.safaribooksonline.com/library/view/effective-modern-c/9781491908419/ch01.html


![:thumb]( But usually you can ignore these and just think about:
1. Whether you want to copy the argument or not  - if you don't want a
copy add a reference `&`
2. Whether you can handle a const argument - if so add a `const` qualifier)

---
# Auto

The `auto` keyword follows the same rules as template argument
deduction
