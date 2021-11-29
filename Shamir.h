#pragma once

#include "Tools.h"

#include <vector>

namespace shamir {
   class Encoder {
   private:
      //poly degree
      int t;
      //shares
      int n;
      //secret
      int s;
      //p = random prime number
      int p;
      //pairs (i, si) where si = s + sum(t-1) aj x^j mod p
      std::vector<int> pairs;
   public:
      Encoder(int t, int n, int s);
      void encode();
      std::vector<int> getPairs();
      int getP();
   };

   class Decoder {
   private:

   public:
      int decode(std::vector<int> pairs, int p);
   private:
      tools::Fraction lagrangeConstant(int x, int t);
   };


}
