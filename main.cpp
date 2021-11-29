#include "BBS.h"
#include "Shamir.h"

#include <iostream>
#include <vector>

int main() {
   /*BBS bbs;
   int attempts = 0;
   while (!bbs.allTests()) {
      bbs.generate();
      ++attempts;
   }
   std::cout << "Attempts: " << attempts << std::endl;
   bbs.printValues();
   bbs.allTests(true);*/

   shamir::Encoder e (3, 4, 1200);
   e.encode();
   shamir::Decoder d;
   std::cout << d.decode(e.getPairs(), e.getP());
   return 0;
}