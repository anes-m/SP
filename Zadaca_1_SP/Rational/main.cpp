#include "Rational.hpp"
#include <iostream>
#include <fstream>
int main(void){
  std::fstream ulaz;
  ulaz.open("input.txt");
  std::string pom;
  while(getline(ulaz,pom)){
    Rational r {pom};
    std::cout << r << std::endl;
  }
  ulaz.close();
  return 0;
}
