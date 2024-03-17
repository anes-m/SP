#include <iostream>
#include "duration.hpp"

int main() {
  // ovdje možete samostalno testirati neke funkcionalnosti. 
  // Napomena: main.cpp se ne pregleda, sva implementacija 
  // ide u duration .cpp i .hpp fileove.
  Duration d1(2,4,5),d2;
  std::cin >> d2;
  std::cout << (d1 + Duration{3, 2, 1}) << std::endl;

}
