#pragma once
#include <vector>

typedef unsigned long long LINT;

class BBS {
private:
   LINT p;
   LINT q;
   LINT N;
   LINT x;

   std::vector<LINT> elements;
   std::vector<bool> bits;

   //single bit test val
   int singleBits;
   //series test val
   int series[6]; 
   //long series test val
   int maxSeries;
   //poker test val
   float pokerX;

public:
   BBS(bool print = false);
   void generate(bool print = false);
   bool singleBitTest(bool print = false);
   bool seriesTest(bool print = false);
   bool longSeriesTest(bool print = false);
   bool pokerTest(bool print = false);
   bool allTests(bool print = false);
   void printValues();

private:
   bool  checkPrimeNumber(LINT& number);
   bool  checkCoprimeNumbers(LINT x, LINT y);
   LINT  primeNumber();
   LINT  coprimeNumber(LINT& n);
   void  printTestResult(bool result, const char* text);
   void  clear();
   void  calcPokerX();
};