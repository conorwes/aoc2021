#include "common.hpp"

#include <functional>
#include <algorithm>
#include <tuple>

struct Space {
   int Number;
   bool Checked;
};

typedef std::vector<Space> Board;

class Day_04 {
public:
   ~Day_04() {};

   static void MarkNumber(Board& board, int num) {
      for (size_t i = 0; i < 25; i++) {
         if (board.at(i).Number == num) {
            board.at(i).Checked = true;
         }
      }
   }

   static int SumUncheckedNumbers(Board& board) {
      int sum = 0;
      for (size_t i = 0; i < 25; i++) {
         if (board.at(i).Checked == false) {
            sum += board.at(i).Number;
         }
      }

      return sum;
   }

   static bool CheckBingo(Board& board) {
      for (size_t i = 0; i < 5; ++i)
      {
         bool row_checked{ true }, col_checked{ true };

         for (size_t j = 0; j < 5; ++j)
         {
            row_checked &= board[i * 5 + j].Checked;
            col_checked &= board[j * 5 + i].Checked;
         }

         if (row_checked || col_checked)
         {
            return true;
         }
      }
      return false;
   }


   // Part One: What will your final score be if you choose that board?
   static bool PartOne(const std::vector<int>& draws, std::vector<Board>& boards, int& out) {
      out = 0;

      Board winner;
      int last_draw = 0;

      auto FindWinner = [&]() {
         for (auto&& d : draws)
         {
            for (auto&& b : boards)
            {
               MarkNumber(b, d);

               if (CheckBingo(b))
               {
                  winner = b;
                  last_draw = d;
                  return true;
               }
            }
         }

         return false;
      };

      if (!FindWinner())
         return false;

      out = SumUncheckedNumbers(winner) * last_draw;
      _ASSERT(out == 10374);
      return true;
   }

   // Part Two: Once it wins, what would its final score be?
   static bool PartTwo(const std::vector<int>& draws, std::vector<Board>& boards, int& out) {
      out = 0;

      auto workers = boards;
      for (auto&& d : draws)
      {
         std::vector<Board> losers;
         for (auto&& b : workers)
         {
            MarkNumber(b, d);
            if (!CheckBingo(b))
            {
               losers.push_back(b);
            }
            else
            {
               if (workers.size() == 1)
                  out = SumUncheckedNumbers(b) * d;
            }
         }
         workers = losers;
      }

      _ASSERT(out == 24742);
      return true;
   }

   static bool Evaluate() {
      std::ifstream in("C:/Repositories/aoc2021/aoc2021/Source/Inputs/Day_04.txt");

      // first parse draw order
      std::vector<int> draws;
      std::string order;
      in >> order;

      std::replace(order.begin(), order.end(), ',', ' ');
      std::stringstream ss(order);

      int number = 0;
      while (ss >> number)
         draws.push_back(number);

      // then parse bingo boards
      std::vector<Board> boards;
      number = 0;
      Board worker;
      while (in >> number) {
         worker.push_back({ number, false });
         if (worker.size() == 25) {
            boards.push_back(worker);
            worker = Board();
         }
      }

      std::cout << "Day Four" << std::endl;

      int out;
      if (!PartOne(draws, boards, out))
         return 1;

      std::cout << "Part One: " << out << std::endl;

      if (!PartTwo(draws, boards, out))
         return 1;

      std::cout << "Part Two: " << out << std::endl;
      return true;
   }
};