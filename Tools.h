#pragma once

#include <iostream>

namespace tools {
   bool checkPrimeNumber(int& number);

   bool checkCoprimeNumbers(int x, int y);

   int randomInt(int lower, int upper);

   int coprimeNumber(int& n);

   //prime number which n % 4 == 3;
   int primeNumberModulo(int lower, int upper, int divider, int rest);

   int primeNumber(int lower, int upper); 

   struct Fraction {
      int n;
      int d;
   };
}