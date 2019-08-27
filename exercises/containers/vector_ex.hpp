#ifndef CPPEX_VECTOR_EX_HPP
#define CPPEX_VECTOR_EX_HPP

#include <vector>
#include <iostream>

// Here we declare two functions to implement. Provide implementations!

// Given a vector of integers, return a new vector with only the odd elements from our input
std::vector<int> GetEven(std::vector<int> const& source);

// Given a vector of ints, print the data to the stream
// [0, 1]
void PrintVectorOfInt(std::ostream& output, std::vector<int> const& data);

#endif
