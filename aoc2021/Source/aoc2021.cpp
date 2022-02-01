#include <iostream>
#include "day_01.cpp"
#include "day_02.cpp"
#include "day_03.cpp"

int main()
{
   std::cout << "Advent of Code 2021!\n\n";
   std::cout << Day_01::Evaluate() << std::endl;
   std::cout << Day_02::Evaluate() << std::endl;
   std::cout << Day_03::Evaluate() << std::endl;
}