#include "VC.h"

#include <iostream>
#include <fstream>


void VC::setImage(std::vector<std::string> image) {
   this->image = image;
}

void VC::loadImage(const char* filename) {
   std::ifstream file(filename);
   if (file.fail()) {
      std::cout << "Failed to load " << filename << std::endl;
      return;
   }
   image.clear();
   while (!file.eof()) {
      std::string row;
      std::getline(file, row);
      image.push_back(row);
   }
   file.close();
}

void VC::createParts() {
   part1.clear();
   part2.clear();
   srand(time(NULL));
   for (size_t i = 0; i < image.size(); ++i) {
      std::string row1;
      std::string row2;
      for (size_t j = 0; j < image[i].size(); ++j) {
         int random = std::rand() % 1000;
         if (random % 2 == 0) {
            if (image[i][j] == '0') {
               row1.push_back('2');
               row2.push_back('3');
            }
            else {
               row1.push_back('2');
               row2.push_back('2');
            }
         }
         else {
            if (image[i][j] == '0') {
               row1.push_back('3');
               row2.push_back('2');
            }
            else {
               row1.push_back('3');
               row2.push_back('3');
            }
         }
      }
      part1.push_back(row1);
      part2.push_back(row2);
   }
}

void VC::calcResult() {
   result.clear();
   if (part1.size() != part2.size() && part2.size() != image.size()) {
      std::cout << "Failed to calculate result!" << std::endl;
      return;
   }
   for (size_t i = 0; i < image.size(); ++i) {
      std::string row;
      for (size_t j = 0; j < image[i].size(); ++j) {
         if (part1[i][j] != part2[i][j]) {
            row.push_back('0');
         }
         else {
            row.push_back(part1[i][j]);
         }
      }
      result.push_back(row);
   }
}

void VC::printImage() {
   print(image);
}

void VC::printPart1() {
   print(part1);
}

void VC::printPart2() {
   print(part2);
}

void VC::printResult() {
   print(result);
}

void VC::print(std::vector<std::string> img) {
   for (size_t i = 0; i < img.size(); ++i) {
      for (size_t j = 0; j < img[i].size(); ++j) {
         if (img[i][j] == '0') {
            std::cout << "  ";
         }
         else if(img[i][j] == '1') {
            std::cout << "\xDB\xDB";
         }
         else if (img[i][j] == '2') {
            std::cout << "\xDB ";
         }
         else {
            std::cout << " \xDB";
         }
      }
      std::cout << std::endl;
   }
}