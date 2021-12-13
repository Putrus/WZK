#pragma once

#include <vector>
#include <string>

class VC {
private:
   std::vector<std::string> image;
   std::vector<std::string> part1;
   std::vector<std::string> part2;
   std::vector<std::string> result;

public:
   void setImage(std::vector<std::string> image);
   void loadImage(const char* filename);
   void createParts();
   void calcResult();
   void printImage();
   void printPart1();
   void printPart2();
   void printResult();

private:
   void print(std::vector<std::string> img);
};