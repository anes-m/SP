#include "f1.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main(void){
  std::vector<f1_team> F;
  std::fstream unos;
  unos.open("f1_teams.csv");
  std::string u;
  while(getline(unos,u)){
    F.push_back(f1_team(u));
  }
  unos.close();
  sort(begin(F), end(F),[](f1_team&a , f1_team& b){ return a.number_of_championships_()>b.number_of_championships_();}); // sortiranje od vecega ka manjem
  for(auto i=begin(F);i<end(F);++i){
    if(filter(*i)){
      F.erase(i);
      i=begin(F);
      }
  }
  std::ofstream ispis{"f1_team_sorted.csv"};
  for(const auto i : F)
    ispis << i << '\n'; 
  ispis.close();
  return 0;
}
