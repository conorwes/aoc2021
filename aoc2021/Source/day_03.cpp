#include "common.hpp"

#include <functional>
#include <algorithm>

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
            vec.at(j)[i] == '1' ? one_count++ : zero_count++;
         }

         if (one_count > zero_count)
            gamma += pow(2, width - i - 1);
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

      auto process_entries = [vec, width](std::function<char(int)> filter)
      {
         std::vector<std::string> worker = vec;

         for (size_t i = 0; i < width && worker.size() > 1; i++)
         {
            int count = 0;
            for (auto&& entry : worker)
            {
               count += entry[i] == '1' ? 1 : -1;
            }

            char keep = filter(count);
            std::vector<std::string> valid;
            std::copy_if(worker.begin(), worker.end(), std::back_inserter(valid),
               [keep, i](std::string entry) { return entry[i] == keep; }
            );
            worker = valid;
         }

         return std::stoi(worker[0], nullptr, 2);
      };

      oxygen = process_entries([](int count) { return count >= 0 ? '1' : '0'; });
      carbon = process_entries([](int count) { return count < 0 ? '1' : '0'; });
      out = oxygen * carbon;
      _ASSERT(out == 2555739);
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