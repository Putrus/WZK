#include "BBS.h"
#include "Tools.h"

#include <Windows.h>
#include <iostream>
#include <string>

#define ELEMENTS 20000
#define DEFAULT 7
#define GREEN 10
#define RED 12


BBS::BBS(bool print) {
   generate(print);
}

void BBS::generate(bool print) {
   clear();
   srand(time(NULL));
   p = static_cast<LINT>(tools::primeNumberModulo(1000, 9999, 4, 3));
   q = static_cast<LINT>(tools::primeNumberModulo(1000, 9999, 4, 3));
   N = p * q;
   int Nint = static_cast<int>(N);
   x = static_cast<LINT>(tools::coprimeNumber(Nint));

   elements.push_back((x * x) % N);
   bits.push_back(elements[0] & 1);

   //lastBit for calc series
   bool lastBit = bits[0];
   int seriesCounter = 1;
   for (LINT i = 1; i < ELEMENTS; ++i) {
      elements.push_back((elements[i - 1] * elements[i - 1]) % N);
      bits.push_back(elements[i] & 1);

      //calc bits for single bits test and series
      if (bits[i]) {
         ++singleBits;
         ++seriesCounter;
      }
      else if (lastBit == 1 && seriesCounter != 0) {
         ++series[(seriesCounter >= 6) ? 5 : (seriesCounter - 1)];
         maxSeries = max(maxSeries, seriesCounter);
         seriesCounter = 0;
      }
      lastBit = bits[i];
   }
   calcPokerX();

   if (print) {
      printValues();
   }
}

bool BBS::singleBitTest(bool print) {
   bool result = singleBits > 9725 && singleBits < 10275;
   if (print) {
      printTestResult(result, "Single bit test");
   }
   return result;
}

bool BBS::seriesTest(bool print) {
   int interval[6][2] = { {2315, 2685}, {1114, 1386}, {527, 723}, {240, 384}, {103, 209}, {103, 209} };
   std::string text;
   bool finalResult = true;
   for (int i = 0; i < 6; ++i) {
      bool result = series[i] > interval[i][0] && series[i] < interval[i][1];
      finalResult = (result) ? finalResult : false;
      /*text = "Series " + std::to_string(i) + "(" + std::to_string(interval[i][0]) + ", " + std::to_string(interval[i][1]) + ") = " + std::to_string(series[i]);
      printTestResult(result, text.c_str());*/
   }
   if (print) {
      printTestResult(finalResult, "Series test");
   }
   return finalResult;
}

bool BBS::longSeriesTest(bool print) {
   bool result = maxSeries < 26;
   if (print) {
      printTestResult(result, "Long series test");
   }
   return result;
}

bool BBS::pokerTest(bool print) {
   bool result = pokerX > 2.16f && pokerX < 46.17f;
   if (print) {
      printTestResult(result, "Poker test");
   }
   return result;
}

bool BBS::allTests(bool print) {
   bool result = true;
   bool t1 = singleBitTest(print);
   bool t2 = seriesTest(print);
   bool t3 = longSeriesTest(print);
   bool t4 = pokerTest(print);
   result = t1 && t2 && t3 && t4;
   if (print) {
      printTestResult(result, "Tests");
   }
   return result;
}

void BBS::printValues() {
   std::cout << "BBS values" << std::endl;
   std::cout << "p = " << p << std::endl;
   std::cout << "q = " << q << std::endl;
   std::cout << "N = " << N << std::endl;
   std::cout << "x = " << x << std::endl;
   std::cout << "n(1) = " << singleBits << std::endl;
   std::cout << "Series:" << std::endl;
   for (int i = 0; i < 6; ++i) {
      std::cout << i + 1 << " " << series[i] << std::endl;
   }
   std::cout << "MaxSeries = " << maxSeries << std::endl;
   std::cout << "Poker x = " << pokerX << std::endl;
}

void  BBS::printTestResult(bool result, const char* text) {
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   if (result) {
      SetConsoleTextAttribute(hConsole, GREEN);
      std::cout << text << " succeed!" << std::endl;
   }
   else {
      SetConsoleTextAttribute(hConsole, RED);
      std::cout << text << " failed!" << std::endl;
   }
   SetConsoleTextAttribute(hConsole, DEFAULT);
}

void BBS::clear() {
   elements.clear();
   bits.clear();
   for (int i = 0; i < 6; ++i) {
      series[i] = 0;
   }
   maxSeries = 0;
   singleBits = 0;
   pokerX = 0.0f;
}

void BBS::calcPokerX() {
   int values[16];
   for (int i = 0; i < 16; ++i) {
      values[i] = 0;
   }
   for (size_t i = 0; i < bits.size(); i += 4) {
      int val = bits[i] * 8 + bits[i + 1] * 4 + bits[i + 2] * 2 + bits[i + 3] * 1;
      values[val]++;
   }
   pokerX = 0.0f;
   int sum = 0;
   for (size_t i = 0; i < 16; ++i) {
      sum += values[i] * values[i];
   }
   pokerX = 16.0f / 5000.0f * static_cast<float>(sum) - 5000.0f;
}

