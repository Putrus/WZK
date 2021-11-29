#include "BBS.h"

#include <iostream>
#include <vector>

int main() {
   BBS bbs;
   int attempts = 0;
   while (!bbs.allTests()) {
      bbs.generate();
      ++attempts;
   }
   std::cout << "Attempts: " << attempts << std::endl;
   bbs.printValues();
   bbs.allTests(true);

   return 0;
}