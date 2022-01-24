#include "BBS.h"
#include "Shamir.h"
#include "VC.h"
#include "DH.h"
#include "RSA.h"

#include <iostream>
#include <vector>

int main() {
   BBS bbs;
   //int attempts = 0,;
   //while (!bbs.allTests()) {
   //   bbs.generate();
   //   ++attempts;
   //}
   //std::cout << "Attempts: " << attempts << std::endl;
   /*bbs.generate();
   bbs.printValues();
   bbs.allTests(true);*/

   /*std::cout << '\xDB' << '\xDB' << std::endl;
   std::cout << '\xDB' << '\xDB' << std::endl;*/

   /*VC v;
   v.loadImage("Images/trollface.txt");
   v.printImage();
   v.createParts();
   std::cout << std::endl;
   v.printPart1();
   std::cout << std::endl;
   v.printPart2();
   v.calcResult();
   std::cout << std::endl;
   v.printResult();*/
   //int t = 3;
   //int n = 4;
   //int s = 2137;
   //srand(static_cast<unsigned int>(time(NULL)));
   //shamir::Encoder e(t, n, s);
   //e.encode();
   //shamir::Decoder d;
   //std::cout << d.decode(e.getPairs(), e.getP(), t) << std::endl;

   DH dh;
   dh.calculate();

   RSA rsa;
   rsa.calculate();
   return 0;
}