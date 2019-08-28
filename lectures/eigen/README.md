template: titleslide
# Using Eigen
## Chris Richardson, Rupert Nash
## chris@bpi.cam.ac.uk, r.nash@epcc.ed.ac.uk
## CC-BY

---
# What is Eigen3 and why use it?
- C++ library for matrix arithmetic
- “Header only” implementation: no libraries to compile and install (easy)
- Provides some “missing” features needed for scientific computing in C++
- Contains optimisations to get good performance out of ARM & Intel processors
- Easy to use interface
- Support for dense and sparse matrices, vectors and “arrays”
- Some support for ‘solvers’ (A.x = b)
- Download from https://eigen.tuxfamily.org or e.g. `apt install libeigen3-dev`
- If you know Python, it is a bit like a NumPy for C++

---
# Basics

```C++
#include <Eigen/Dense>

int main()
{
   Eigen::Matrix<double, 10, 10> A;
   A.setZero();
   A(9, 0) = 1.234;
   std::cout << A << std::endl;
   return 0;
}
```

This is pretty similar to `double A[10][10];`

---
# Dynamic size

```C++
int n = 64;
int m = 65;
Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> A(n, m);

A.resize(20, 20);

std::cout << “Size is ”;
std::cout << A.rows() << “ x ” << A.cols() << std::endl;
```

So this is more like a 2D version of `std::vector<double>`

---
# Convenience aliases
```C++
using Eigen::Matrix3d = Eigen::Matrix<double, 3, 3>
using Eigen::Matrix3i = Eigen::Matrix<int, 3, 3>
using Eigen::MatrixXd = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
using Eigen::VectorXd = Eigen::Matrix<double, Eigen::Dynamic, 1>
using Eigen::RowVectorXd = Eigen::Matrix<double, 1, Eigen::Dynamic>

```

---
# You can do Matrix arithmetic...

```C++
Eigen::MatrixXd A(5, 10);
Eigen::MatrixXd B(10, 2);
Eigen::VectorXd vec(10);

Eigen::MatrixXd C = A * B;
Eigen::VectorXd w = A * vec;
```

Also dot and cross products for vectors, transpose, and usual scalar arithmetic `+ - * /`

---
#  Element-wise ops with `Array`s

For example:
```C++
Eigen::Matrix3d A, B;
// set all values to 2.0
A.array() = 2.0;

// set each element of A to sin() of the same element in B
A.array() = B.array().sin();

Eigen::Array3d W;
W = W * A;  // Error - cannot mix Array with Matrix
```

---
# View other data as a `Matrix` or `Array`

Mix and match with `std::vector` or any contiguous layout

It is easy to “overlay” existing memory with an Eigen `Array` or `Matrix`:

```C++
std::vector<double> a(1000);

Eigen::Map<Eigen::Matrix<double, 100, 10>> a_eigen(a.data());

a_eigen(10, 0) = 1.0;

Eigen::Map<Eigen::MatrixXd> a2_eigen(a.data(), 10, 100);
```

---
# Efficiency: Eigen does lots of checks in debug mode

Turn optimisation on: `-O2` etc.

Turn off debug: `-DNDEBUG`

---
# Walk through example

Solve diffusion equation

$$\frac{\partial T}{\partial t} = k \frac{\partial^2 T}{\partial x^2}$$

in 1D using an explicit method

Each timestep can be solved by using `\(T_{n+1} = A T_n\)`

1. Create an initial vector for `T`
2. Create a dense matrix for `A`
3. Matrix multiply several times
- Convert to an implicit method: `\(A.T_{n+1} = T_n\)`
- Sparse matrices


Type along with me - see `exercises/eigen`

---
# Diffusion equation (explicit) 

Subscript means time, square brackets position

`$$T_{n+1}[i] = T_n[i] + \frac{k \Delta t}{\Delta x^2}(T_n[i-1] - 2T_n[i] + T_n[i+1])$$`

Our matrix equation is now:

`$$T_{n+1} = A.T_{n}$$`

Left-hand side is unknown (next time step)

Let: `\(\delta = k\Delta t/ \Delta x^2\)`

---
# Matrix

```
A = [ 1-ẟ ẟ    0    0    0 …        ]
    [ ẟ   1-2ẟ ẟ    0    0 …        ]
    [ 0   ẟ    1-2ẟ ẟ    0 …        ]
    [ 0   0    ẟ    1-2ẟ ẟ    0  0 …] 
    [ 0   0    0    ẟ    1-2ẟ ẟ  0 …]
	
```

---
# Diffusion equation (implicit)

Subscript means time, square brackets position

`$$T_{n+1}[i] - \frac{k \Delta t}{\Delta x^2} (T_{n+1}[i-1] - 2*T_{n+1}[i] + T_{n+1}[i+1]) = T[i]$$`

Left-hand side is unknown (next time step)
`$$A.T_{n+1} = T_n$$`

Let: $$\delta = k \Delta t/\Delta x^2$$

???
The matrix A is very similar - just flip the sign of the delta terms
