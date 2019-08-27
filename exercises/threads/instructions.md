# C++ threads
## Mark Bull
## m.bull@epcc.ed.ac.uk

Source for this can be obtained from Github. Get a new copy with:

```
git clone https://github.com/EPCCed/cpp4hpc.git
```

or update your existing one with

```
git pull
```

then you can

```
cd cpp4hpc/exercises/threads
```



`area.cpp` contains a C++ version of the Mandelbrot example which you used in Threaded Programming. 

Parallelise the outer loop of the main computation using C++
threads. Try using either a function pointer or a lambda expression.

Try different mechanisms for synchronising the update to the shared
counter: a mutex, and lock guard or an atomic int.

