#include "Tools.h"

namespace tools {
   bool checkPrimeNumber(int& number) {
      int counter = 0;
      for (int i = 1; i <= number; ++i) {
         if (number % i == 0) {
            ++counter;
         }
         if (counter > 2) {
            return false;
         }
      }
      return true;
   }

   bool checkCoprimeNumbers(int x, int y) {
      while (x != y) {
         if (x > y) {
            x -= y;
         }
         else {
            y -= x;
         }
      }
      if (x != 1) {
         return false;
      }
      return true;
   }

   int randomInt(int lower, int upper) {
      return rand() % (upper - lower) + lower;
   }

   int coprimeNumber(int& n) {
      int x = static_cast<int>(randomInt(1, 1000));
      while (!checkCoprimeNumbers(n, x)) {
         ++x;
      }
      return x;
   }

   //prime number which n % 4 == 3;
   int primeNumberModulo(int lower, int upper, int divider, int rest) {
      int n = static_cast<int>(randomInt(lower, upper));
      while (!checkPrimeNumber(n) || n % divider != rest) {
         ++n;
      }
      return n;
   }

   int primeNumber(int lower, int upper) {
      int n = static_cast<int>(randomInt(lower, upper));
      while (!checkPrimeNumber(n)) {
         ++n;
      }
      return n;
   }
}