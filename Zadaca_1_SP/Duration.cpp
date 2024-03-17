#include "duration.hpp"
#include <iostream>

Duration::Duration(): _sekunde{0}, _minute{0}, _sati{0} {}
Duration::Duration(int a) {
  if(a<0){
    throw std::out_of_range("Van granica!");
  }else if(a<60){
    _sekunde=a;
  } else if (a>=60){
    _minute=a/60;
    a-=_minute*60;
    _sekunde=a;
    if(_minute>=60){
      _sati=_minute/60;
      _minute-=_sati*60;
    }
  }
}
Duration::Duration(int h, int m, int s){
  if(h<0||m>=60||m<0||s<0||s>=60){
    throw std::out_of_range("Van granica!");
  } else {
    _sati=h;
    _minute=m;
    _sekunde=s;
  }
}
Duration::Duration(std::string unos){
  char znak=':';
  int ho,mi,se;
  std::string h,m,s;
  auto i=begin(unos);
  while(*i!=znak){
    h+=*i;
    ++i;
  }
  ho=std::stoi(h);
  if(ho<0)
    throw std::out_of_range("Sati ne mogu biti negativni");
  else 
    _sati=ho;
  ++i;
  while(*i!=znak){
    m+=*i;
    ++i;
  }
  mi=std::stoi(m);
  if(mi<0||mi>=60)
    throw std::out_of_range("Unesite minute u vrijednostima od 0 do 59!");
  else 
    _minute=mi;
  ++i;
  while(i!=end(unos)){
    s+=*i;
    ++i;
  }
  se=std::stoi(s);
  if(se<0||se>=60)
    throw std::out_of_range("Unesite sekunde u vrijednostima od 0 do 59!");
  else
    _sekunde=se;
}

Duration::Duration(const Duration& a){
  _sati=a._sati;
  _minute=a._minute;
  _sekunde=a._sekunde;
}
Duration::Duration(Duration&& a){
  _sati=a._sati;
  _minute=a._minute;
  _sekunde=a._sekunde;
}
Duration& Duration::operator=(const Duration& a){
  _sati=a._sati;
  _minute=a._minute;
  _sekunde=a._sekunde;
  return *this;
}
Duration& Duration::operator=(Duration&& a){
  _sati=a._sati;
  _minute=a._minute;
  _sekunde=a._sekunde;
  return *this;
}

Duration& Duration::set_s(int s){ 
  if(s>=60||s<0){
    throw std::out_of_range("Van granica!");}
  else{
    _sekunde=s;
    return* this;
  }
}
Duration& Duration::set_m(int m){
  if(m>=60||m<0){
    throw std::out_of_range("Van granica!");}
  else{
  _minute=m;
  return *this;
  }
}

Duration& Duration::set_h(int h){ 
  if(h<0){
   throw std::out_of_range("Van granica!");
  }else{
    _sati=h; 
  }
  return *this;
}
bool Duration::operator==(const Duration& a) const{
  if((_sati==a._sati)&&(_minute==a._minute)&&(_sekunde==a._sekunde)){
    return true;
  }else {
  return false;
  }
}
bool Duration::operator!=(const Duration& a) const{
  if((_sati!=a._sati)||(_minute!=a._minute)||(_sekunde!=a._sekunde)){
    return true;
  }else return false;
}
bool Duration::operator<(const Duration& a) const{
  if(_sati<a._sati){
    return true;
  }else if((_sati==a._sati)&&(_minute<a._minute)&&(_sekunde==a._sekunde)){
    return true;
  }else if((_sati==a._sati)&&(_minute==a._minute)&&(_sekunde<a._sekunde)){
    return true;
  }else return false;
}
bool Duration::operator>(const Duration& a)const {
  if(_sati>a._sati){
    return true;
  }else if((_sati==a._sati)&&(_minute>a._minute)&&(_sekunde==a._sekunde)){
    return true;
  }else if((_sati==a._sati)&&(_minute==a._minute)&&(_sekunde>a._sekunde)){
    return true;
  }else return false;
}
bool Duration::operator<=(const Duration& a) const{
  if(_sati<a._sati){
    return true;
  }else if((_sati==a._sati)&&(_minute<=a._minute)&&(_sekunde==a._sekunde)){
  return true;
  }else if((_sati==a._sati)&&(_minute==a._minute)&&(_sekunde<=a._sekunde)){
  return true;
  }else return false;
}
bool Duration::operator>=(const Duration& a) const{
  if(_sati>a._sati){
    return true;
  }else if((_sati==a._sati)&&(_minute>=a._minute)&&(_sekunde==a._sekunde)){
    return true;
  }else if((_sati==a._sati)&&(_minute==a._minute)&&(_sekunde>=a._sekunde)){
    return true;
  }else return false;
}
Duration Duration::operator+(const Duration& a) const{
  Duration rez;
  rez._sati=_sati+a._sati;
  if((_minute+a._minute)>=60){
    int pom=_minute+a._minute,pom1;
    pom1=pom/60;
    rez._sati+=pom1;
    pom-=pom1*60;
    rez._minute=pom;
  }else{
  rez._minute=_minute+a._minute;
  }
  if((_sekunde+a._sekunde)>=60){
    int pom=_sekunde+a._sekunde,pom1;
    pom1=pom/60;
    rez._minute+=pom1;
    pom-=pom1*60;
    rez._sekunde=pom;
  }else {
  rez._sekunde=_sekunde+a._sekunde;
  }
  return rez;
}

Duration& Duration::operator+=(const Duration& a){
  _sati+=a._sati;
  if((_minute+a._minute)>=60){
    int pom=_minute+a._minute,pom1;
    _sati+=pom/60;
    pom1=pom/60;
    pom-=pom1*60;
    _minute=pom;
  }else {
  _minute+=a._minute;
  }
  if((_sekunde+a._sekunde)>=60){
    int pom=_sekunde+a._sekunde,pom1;
    _minute+=pom/60;
    pom1=pom/60;
    pom-=pom1*60;
    _sekunde=pom;
  }else{
  _sekunde+=a._sekunde;
  }
  return *this;
}
Duration Duration::operator-(const Duration& a) const{
  Duration rez;
  rez._sati=_sati;
  rez._minute=_minute;
  rez._sekunde=_sekunde;
  if((_sati-a._sati)<0){
    throw std::out_of_range("Van granica");
  }else if((_minute-a._minute)<0){
    (_sati-1)>0 ? rez._sati-=1 : throw std::out_of_range("Van granica");
    rez._sati-=a._sati;
    rez. _minute+=60;
    rez._minute-=a._minute;
    if((_sekunde-a._sekunde)<0){
      (_minute-1)>0 ? rez._minute-=1 : throw std::out_of_range("Van granica");
      rez._sekunde+=60;
      rez._sekunde-=a._sekunde;
    }else{ rez._sekunde-=a._sekunde; }
  }else if((_sekunde-a._sekunde)<0){
    (_minute-1)>0 ? rez._minute-=1 : throw std::out_of_range("Van granica");
    rez._sati-=a._sati;
    rez._minute-=a._minute;
    rez._sekunde+=60;
    rez._sekunde-=a._sekunde;
  }else {
  rez._sati-=a._sati;
  rez._minute-=a._minute;
  rez._sekunde-=a._sekunde;
  }
  return rez;
}
Duration& Duration::operator-=(const Duration& a){
  if((_sati-a._sati)<0){
    throw std::out_of_range("Van granica");
  }else if((_minute-a._minute)<0){
    (_sati-1)>0 ? _sati-=1 : throw std::out_of_range("Van granica");
    _sati-=a._sati;
    _minute+=60;
    _minute-=a._minute;
    if((_sekunde-a._sekunde)<0){
      (_minute-1)>0 ? _minute-=1 : throw std::out_of_range("Van granica");
      _sekunde+=60;
      _sekunde-=a._sekunde;
    }else{ _sekunde-=a._sekunde; }
  }else if((_sekunde-a._sekunde)<0){
    (_minute-1)>0 ? _minute-=1 : throw std::out_of_range("Van granica");
    _sati-=a._sati;
    _minute-=a._minute;
    _sekunde+=60;
    _sekunde-=a._sekunde;
  }else {
  _sati-=a._sati;
  _minute-=a._minute;
  _sekunde-=a._sekunde;
  }
  return *this;
}
Duration Duration::operator*(const int& a) const{
  Duration rez;
  rez._sati=_sati*a;
  if((_minute*a)>=60){
    int pom=_minute*a,pom1;
    rez._sati+=pom/60;
    pom1=pom/60;
    pom-=pom1*60;
    rez._minute=pom;
    if((_sekunde*a)>=60){
      int pom=_sekunde*a,pom1;
      rez._minute+=pom/60;
      pom1=pom/60;
      pom-=pom1*60;
      rez._sekunde=pom;
    }else{
    rez._sekunde=_sekunde*a;
    }
  }else if(_sekunde*a>=60){
    rez._minute=_minute*a;
    int pom=_sekunde*a,pom1;
    rez._minute+=pom/60;
    pom1=pom/60;
    pom-=pom1*60;
    rez._sekunde=pom;
  }else {
    rez._minute=_minute*a;
    rez._sekunde=_sekunde*a;
  }
  return rez;
}
Duration Duration::operator/(const int& a) const{
  Duration rez;
  rez._sati=_sati/a;
  rez._minute=_minute/a;
  rez._sekunde=_sekunde/a;
  return rez;
}

Duration& Duration::operator*=(const int& a){
  _sati*=a;
  if((_minute*a)>=60){
    int pom=_minute*a,pom1;
    _sati+=pom/60;
    pom1=pom/60;
    pom-=pom1*60;
    _minute=pom;
    if((_sekunde*a)>=60){
      int pom=_sekunde*a,pom1;
      _minute+=pom/60;
      pom1=pom/60;
      pom-=pom1*60;
      _sekunde=pom;
    }else{
    _sekunde*=a;
    }
  }else if(_sekunde*a>=60){
    _minute*=a;
    int pom=_sekunde*a,pom1;
    _minute+=pom/60;
    pom1=pom/60;
    pom-=pom1*60;
    _sekunde=pom;
  }else {
    _minute*=a;
    _sekunde*=a;
  }
  return *this;
}
Duration& Duration::operator/=(const int& a){
  if(_sati%a!=0){
    _minute+=60;
    _sati-=1;
    if(_minute%a!=0){
      _sekunde+=60;
      _minute-=1;
      _minute/=a;
      _sekunde/=a;
    }else{
    _minute/=a;
    _sekunde/=a;
    }
  }else if(_minute%a!=0){
    _sekunde+=60;
    _minute-=1;
    _minute/=a;
    _sekunde/=a;
  }else{
    _sati/=a;
    _minute/=a;
    _sekunde/=a;
  } 
  return *this;
}
