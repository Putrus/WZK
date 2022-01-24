#include "DH.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Tools.h"

void DH::calculate() {
   srand(time(NULL));
   std::cout << "DH" << std::endl;
   int n = 7;
   std::cout << "n = " << n << std::endl;
   int g = 5;
   std::cout << "g = " << g << std::endl;
   int x = tools::randomInt(1, 10);
   std::cout << "Klucz prywatny A, x = " << x << std::endl;
   int y = tools::randomInt(1, 10);
   std::cout << "Klucz prywatny B, y = " << y << std::endl;
   int X = (int)pow((double)g, (double)x) % n;
   int Y = (int)pow((double)g, y) % n;
   int ka = (int)pow((double)Y, (double)x) % n;
   int kb = (int)pow((double)X, (double)y) % n;
   std::cout << "Klucz sesji A, k = " << ka << std::endl;
   std::cout << "Klucz sesji B, k = " << kb << std::endl;
}

int DH::primeRoot(int number) {
   std::vector<int> roots;
   for (double i = 0; i < number; ++i) {
      for (double p = 1; p < number; ++p) {
         roots.push_back((int)pow(i, p) % number);
      }
   }
   int r = tools::randomInt(0, roots.size());
   return roots[r];
}