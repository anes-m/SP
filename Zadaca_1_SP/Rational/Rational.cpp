#include "Rational.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <cmath>
Rational::Rational(): numerator_{0} ,denominator_{1}{}
Rational::Rational(int numerator, int denominator){
  if(denominator==0)
    throw std::invalid_argument("Nazivnik ne moze biti 0!");
  else{
    numerator_=numerator;
    denominator_=denominator;
    if((numerator_<0)&&(denominator_<0)){
      numerator_*=-1;
      denominator_*=-1;
    }
  }
}
Rational::Rational(const std::string& unos ){
  auto i=begin(unos);
  std::string pom1,pom2;
  int b,n;
  if(unos.find('/')==std::string::npos){
    throw std::invalid_argument("Niste unijeli razlomak;");
  }
  for(auto k=begin(unos);k<end(unos);++k){
    if(*k>=47&&*k<=57)
      continue;
    else throw std::invalid_argument("Neodgovarajuci razlomak!");
  }
  while(*i!='/'){
    pom1+=*i;
    ++i;
  }
  b=std::stoi(pom1);
  //if(pom1.find('-')==1)
  //  b*=-1;
  //else
    numerator_=b;
  ++i;
  while(i!=end(unos)){
    pom2+=*i;
    ++i;
  }
  n=std::stoi(pom2);
  if(n==0){
    throw std::invalid_argument("Nazivnik ne moze biti nula!");
  }else{
    //if(pom2.find('-')==1)
    //  n*=-1;
    //else
      denominator_=n;
  }
  if((numerator_<0)&&(denominator_<0)){
    numerator_*=-1;
    denominator_*=-1;
  }
}
Rational::Rational(const char* rational){
  std::string rez=rational;
  *this=rez;
}
Rational::Rational(const Rational& a){
  numerator_=a.numerator_;
  denominator_=a.denominator_;
}
Rational::Rational(Rational&& a){
  numerator_=a.numerator_;
  denominator_=a.denominator_;
  a.numerator_=0;
  a.denominator_=1;
}
Rational& Rational::operator=(const Rational& a){
  numerator_=a.numerator_;
  denominator_=a.denominator_;
  return *this;
}
Rational& Rational::operator=(Rational&& a){
  numerator_=a.numerator_;
  denominator_=a.denominator_;
  a.numerator_=0;
  a.denominator_=1;
  return *this;
}
Rational Rational::operator+(const Rational& a)const {
  Rational rez;
  int njz=0,pom;
  if(a.numerator_==0){
    return *this;
  } else if(numerator_==0){
    return a;
  }else{
  njz=denominator_*a.denominator_;
  rez.denominator_=njz;
  rez.numerator_=numerator_*(njz/denominator_)+a.numerator_*(njz/a.denominator_);
  }
  pom=gcd(rez.numerator_,a.denominator_);
  rez.numerator_/=pom;
  rez.denominator_/=pom;
  return rez;
}
Rational Rational::operator+(int numerator)const {
  Rational rez,pom{numerator,1};
  rez.numerator_=numerator_+pom.numerator_*denominator_;
  rez.denominator_=denominator_;
  int njz=gcd(rez.numerator_,rez.denominator_);
  rez.numerator_/=njz;
  rez.denominator_/=njz;
  return rez;
}
Rational Rational::operator-(const Rational& a) const {
   Rational rez;
  int njz=0,pom;
  if(a.numerator_==0){
    return *this;
  } else if(numerator_==0){
    return a;
  }else{
  njz=denominator_*a.denominator_;
  rez.denominator_=njz;
  rez.numerator_=numerator_*(njz/denominator_)-a.numerator_*(njz/a.denominator_);
  }
  pom=gcd(rez.numerator_,a.denominator_);
  rez.numerator_/=pom;
  rez.denominator_/=pom;
  if(rez.numerator_<0&&rez.denominator_<0){
    rez.numerator_*=-1;
    rez.denominator_*=-1;
  }

  return rez;
}
Rational Rational::operator-(int numerator)const {
  Rational rez,pom{numerator,1};
  rez.numerator_=numerator_-numerator*denominator_;
  rez.denominator_=denominator_;
  int njz=gcd(rez.numerator_,rez.denominator_);
  rez.numerator_/=njz;
  rez.denominator_/=njz;
  return rez;
}
Rational Rational::operator*(const Rational& a)const {
  Rational rez;
  rez.numerator_=numerator_*a.numerator_;
  rez.denominator_=denominator_*a.denominator_;
  int njz=gcd(rez.numerator_,rez.denominator_);
  rez.numerator_/=njz;
  rez.denominator_/=njz;
 
  return rez;
}
Rational Rational::operator*(int numerator) const {
  Rational rez;
  rez.numerator_=numerator_*numerator;
  rez.denominator_=denominator_;  
  int njz=gcd(rez.numerator_,rez.denominator_);
  rez.numerator_/=njz;
  rez.denominator_/=njz;
  return rez;
}
Rational Rational::operator/(const Rational& a)const {
  Rational rez;
  rez.numerator_=numerator_*a.denominator_;
  rez.denominator_=denominator_*a.numerator_;
  int njz=gcd(rez.numerator_,rez.denominator_);
  rez.numerator_/=njz;
  rez.denominator_/=njz;
  return rez;
}
Rational Rational::operator/(int numerator)const {
  Rational rez;
  rez.numerator_=numerator_*1;
  rez.denominator_=denominator_*numerator;  
  int njz=gcd(rez.numerator_,rez.denominator_);
  rez.numerator_/=njz;
  rez.denominator_/=njz;
  return rez;

}
Rational Rational::operator^(int e)const {
  Rational rez;
  rez.numerator_=pow(numerator_,e);
  rez.denominator_=pow(denominator_,e);
  int njz=gcd(rez.numerator_,rez.denominator_);
  rez.numerator_/=njz;
  rez.denominator_/=njz;
  return rez;
}
Rational& Rational::operator++(){
  *this=*this+1;
  return *this;
}
Rational Rational::operator++(int){
  Rational rez{numerator_,denominator_};
  *this=*this+1;
  return rez;
}
Rational& Rational::operator--(){
  *this=*this-1;
  return *this;
}
Rational Rational::operator--(int){
  Rational rez{numerator_,denominator_};
  *this=*this-1;
  return rez;
}
bool Rational::operator==(const Rational& a) const {
  auto njz=gcd(numerator_,denominator_);
  auto njz2=gcd(a.numerator_,a.denominator_);
  if((numerator_/njz==a.numerator_/njz2)&&(denominator_/njz==a.denominator_/njz2))
    return true;
  else
    return false;
}
bool Rational::operator==(const char* rational)const {
  Rational rez{rational};
  return *this==rez;
}
bool Rational::operator!=(const Rational& a)const {
  auto njz=gcd(numerator_,denominator_);
  auto njz2=gcd(a.numerator_,a.denominator_);
  if((numerator_/njz!=a.numerator_/njz2)&&(denominator_/njz!=a.denominator_/njz2))
    return true;
  else 
    return false;
}
bool Rational::operator!=(const char* rational)const {
  Rational rez=rational;
  return *this!=rez;
}
const int Rational::numerator() const{
  return numerator_;
}
const int Rational::denominator() const{
  return denominator_;
}
std::ostream& operator<<(std::ostream& os, const Rational& rational){
  if(rational.numerator()==0){
    os << rational.numerator();
  }else if(rational.denominator()==1){
    os << rational.numerator();
  }else {
    int pom=gcd(rational.numerator(), rational.denominator());
    if((rational.numerator()<0)&&(rational.denominator()<0)){
    os << rational.numerator()/pom;
    rational.denominator()/pom==1 ? os << " " : os << '/' << rational.denominator()/pom;
    }else {os << rational.numerator()/pom ;
    rational.denominator()/pom==1 ? os << " " : os << '/' << rational.denominator()/pom;
    }
  }
  return os;
}
int gcd(int numerator, int denominator){
  int shift;
  for(shift=0;((numerator|denominator) & 1)==0; ++shift){
    numerator>>=1;
    denominator>>=1;
  }
  while((numerator & 1)==0){
    numerator>>=1;
  }
  while(denominator!=0){
    while((denominator & 1)==0){
      denominator>>=1;
    }
    if(numerator>denominator){
      std::swap(numerator,denominator);
    }
    denominator-=numerator;
  }
  return numerator<<shift;
}
