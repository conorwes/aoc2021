#include "common.cpp"

class Day_01 {
public:
   ~Day_01() {};

   // Part One: How Many Measurements are Larger than the Previous?
   static bool PartOne(const std::vector<int>& vec, int& out) {
      out = 0;
      for (size_t i = 1; i < vec.size(); i++) {
         if (vec.at(i) > vec.at(i - 1))
            out++;
      }

      _ASSERT(out == 1583);
      return true;
   }

   // Part Two: How Many 3-Element Sums are Larger than the Previous?
   static bool PartTwo(const std::vector<int>& vec, int& out) {
      out = 0;
      auto first = vec.begin();
      auto second = std::next(first, 1);
      auto third = std::next(first, 2);

      int previous = 0, current = 0;
      while (third != vec.end()) {
         current = *first + *second + *third;
         if (first == vec.begin()) {
            previous = current;
         }

         if (current > previous)
            out++;

         previous = current;

         first++;
         second++;
         third++;
      }

      _ASSERT(out == 1627);
      return true;
   }

   static int Evaluate() {
      std::ifstream in("C:/Repositories/aoc2021/aoc2021/Source/Inputs/Day_01.txt");
      std::string buf;
      std::vector<int> vec;
      while (std::getline(in, buf)) {
         vec.push_back(std::stoi(buf));
      }

      std::cout << "Day One" << std::endl;

      int out = 0;
      if (!PartOne(vec, out))
         return 1;

      std::cout << "Part One: " << out << std::endl;

      if (!PartTwo(vec, out))
         return 1;

      std::cout << "Part Two: " << out << std::endl;

      std::cout << std::endl;

      return 0;
   }
};