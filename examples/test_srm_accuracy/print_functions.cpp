
#include "print_functions.hpp"

#include <vector>
#include <iostream>

void printData(const std::vector<doubleArray3>& inDoubleParam, const int length)
{
   doubleArray3 data{};

   for (int i = 0; i < static_cast<int>(inDoubleParam.size()); i++) {
      data = inDoubleParam.at(i);
      std::cout << i + 1 << " ";
      for (int j = 0; j < length; j++)
         std::cout << data.var[j] << ", ";
      std::cout << std::endl;
   }
}



