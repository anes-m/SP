#include "f1.hpp"
#include <iostream>
f1_team::f1_team(std::string& unos){
  std::string pom;
  std::istringstream s(unos);
  while(s){
    getline(s,team_name,',');
    getline(s,country_of_origin,',');
    while(s){
    s >> year_founded;
    s.ignore();
    s >> number_of_championships;
    s.ignore();
    s >> team_budget_million_usd;
    }
  }
}
bool filter(f1_team& a){
if(a.number_of_championships_()==0)
  return true;
else 
  return false;
}
std::ostream& operator<<(std::ostream& izlaz, const f1_team& a){
  izlaz << a.team_name << "," << a.country_of_origin << "," << a.year_founded << "," << a.number_of_championships << "," << a.team_budget_million_usd ;
  return izlaz;
}
