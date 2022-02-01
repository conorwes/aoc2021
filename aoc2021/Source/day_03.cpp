#include "common.hpp"

class Day_03 {
public:
   ~Day_03() {};

   // Part One: What is the power consumption of the submarine?
   static bool PartOne(const std::vector<std::string>& vec, int& out) {
      out = 0;
      int gamma = 0, epsilon = 0, width = vec[0].size();
      int zero_count, one_count;

      for (size_t i = 0; i < width; i++) {
         zero_count = 0;
         one_count = 0;

         for (size_t j = 0; j < vec.size(); j++) {
            if (vec.at(j)[i] == '1') {
               one_count++;
            }
            else {
               zero_count++;
            }
         }

         if (one_count > zero_count) {
            gamma += pow(2, width - i - 1);
         }
      }

      epsilon = pow(2, width) - gamma - 1;

      out = gamma * epsilon;
      _ASSERT(out == 3985686);
      return true;
   }

   // Part Two: What is the life support rating of the submarine?
   static bool PartTwo(const std::vector<std::string>& vec, int& out) {
      out = 0;
      int oxygen = 0, carbon = 0, width = vec[0].size();
      std::vector<std::string> valid_oxy{ vec }, valid_carb{ vec };

      auto process_data = [&width](std::vector<std::string>& valid, bool isOxygen) {
         int zero_count, one_count;
         for (size_t i = 0; i < width; i++) {
            zero_count = one_count = 0;
            for (size_t j = 0; j < valid.size(); j++) {
               if (valid.at(j)[i] == '1') {
                  one_count++;
               }
               else {
                  zero_count++;
               }
            }

            if (one_count > zero_count) {
               for (size_t j = 0; j < valid.size(); j++) {
                  if (valid.at(j)[i] == (isOxygen == true ? '0' : '1')) {
                     valid.erase(valid.begin() + j);
                     j--;
                  }
               }
            }
            else {
               for (size_t j = 0; j < valid.size(); j++) {
                  if (valid.at(j)[i] == (isOxygen == true ? '1' : '0')) {
                     valid.erase(valid.begin() + j);
                     j--;
                  }
               }
            }

            if (valid.size() <= 1) {
               break;
            }
         }

         return true;
      };

      process_data(valid_oxy, true);
      oxygen = std::stoi(valid_oxy[0], nullptr, 2);
      std::cout << oxygen << std::endl;
      process_data(valid_carb, false);
      carbon = std::stoi(valid_carb[0], nullptr, 2);
      std::cout << carbon << std::endl;
      out = oxygen * carbon;

      //_ASSERT(out == 1599311480);
      return true;
   }

   static bool Evaluate() {
      std::ifstream in("C:/Repositories/aoc2021/aoc2021/Source/Inputs/Day_03.txt");
      std::string buf;
      std::vector<std::string> vec;
      while (std::getline(in, buf)) {
         vec.push_back(buf);
      }

      std::cout << "Day Three" << std::endl;

      int out;
      if (!PartOne(vec, out))
         return 1;

      std::cout << "Part One: " << out << std::endl;

      if (!PartTwo(vec, out))
         return 1;

      std::cout << "Part Two: " << out << std::endl;
      return true;
   }
};