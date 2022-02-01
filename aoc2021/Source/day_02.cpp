#include "common.hpp"

struct Submarine {
   int horizontal;
   int vertical;
   int aim;

   Submarine(int x = 0, int z = 0, int t = 0) { horizontal = x; vertical = z; aim = t; }
};

class Day_02 {
public:
   ~Day_02() {};

   // Part One: What do you get if you multiply your final horizontal position by your final depth?
   static bool PartOne(const std::vector<std::string>& vec, int& out) {
      out = 0;
      Submarine sub;
      for (auto&& v : vec) {
         auto line = split(v, " ");
         if (line.at(0) == "forward") {
            sub.horizontal += std::stoi(line.at(1));
         }
         else if (line.at(0) == "down") {
            sub.vertical += std::stoi(line.at(1));
         }
         else if (line.at(0) == "up") {
            sub.vertical -= std::stoi(line.at(1));
         }
         else {
            sub.horizontal -= std::stoi(line.at(1));
         }
      }

      out = sub.horizontal * sub.vertical;
      _ASSERT(out == 2019945);
      return true;
   }

   // Part Two: What do you get if you multiply your final horizontal position by your final depth?
   static bool PartTwo(const std::vector<std::string>& vec, int& out) {
      out = 0;
      Submarine sub;
      for (auto&& v : vec) {
         auto line = split(v, " ");
         if (line.at(0) == "forward") {
            sub.horizontal += std::stoi(line.at(1));
            sub.vertical += sub.aim * std::stoi(line.at(1));
         }
         else if (line.at(0) == "down") {
            sub.aim += std::stoi(line.at(1));
         }
         else if (line.at(0) == "up") {
            sub.aim -= std::stoi(line.at(1));
         }
         else {
            sub.horizontal -= std::stoi(line.at(1));
            sub.vertical -= sub.aim * std::stoi(line.at(1));
         }
      }

      out = sub.horizontal * sub.vertical;
      _ASSERT(out == 1599311480);
      return true;
   }

   static bool Evaluate() {
      std::ifstream in("C:/Repositories/aoc2021/aoc2021/Source/Inputs/Day_02.txt");
      std::string buf;
      std::vector<std::string> vec;
      while (std::getline(in, buf)) {
         vec.push_back(buf);
      }

      std::cout << "Day Two" << std::endl;

      int out = 0;
      if (!PartOne(vec, out))
         return 1;

      std::cout << "Part One: " << out << std::endl;

      if (!PartTwo(vec, out))
         return 1;

      std::cout << "Part Two: " << out << std::endl;
      return true;
   }
};