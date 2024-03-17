#pragma once
#include <istream>
#include <string>
#include <sstream>
class f1_team{
  public:
    f1_team(std::string&);
    friend std::ostream& operator<<(std::ostream& , const f1_team&);
    int number_of_championships_(){return number_of_championships;}
  private:
    std::string team_name;
    std::string country_of_origin;
    int year_founded=0;
    int number_of_championships=0;
    int team_budget_million_usd=0;
};
bool filter(f1_team&);
