#pragma once
#include <iostream>
#include <string>
class Duration {
  public:
    Duration();
    explicit Duration(int);
    explicit Duration(int, int, int);
    explicit Duration(std::string);
    Duration(const Duration&);
    Duration(Duration&&);
    Duration& operator=(const Duration&);
    Duration& operator=(Duration&&);
    int get_s() const {return _sekunde;}
    int get_m() const {return _minute;}
    int get_h() const {return _sati;}
    Duration& set_s(int);
    Duration& set_m(int);
    Duration& set_h(int);
    int& in_h(){ return _sati;}
    int& in_m(){return _minute;}
    int& in_s(){return _sekunde;}
    bool operator==(const Duration&)const;
    bool operator!=(const Duration&)const;
    bool operator<(const Duration&)const;
    bool operator>(const Duration&)const;
    bool operator<=(const Duration&)const;
    bool operator>=(const Duration&)const;
    Duration operator+(const Duration&) const;
    Duration operator-(const Duration&) const;
    Duration operator*(const int&) const;
    Duration operator/(const int&) const;
    Duration& operator+=(const Duration&);
    Duration& operator-=(const Duration&);
    Duration& operator*=(const int&);
    Duration& operator/=(const int&);
    explicit operator bool() const {
      if((_sekunde==0)&&(_minute==0)&&(_sati==0)){
        return false;
      }
      else return true;
    }
    bool operator!()const{
      if((_sekunde==0)||(_minute==0)||(_sati==0)){
        return true;
      }
      else return false;
      }
   friend std::ostream& operator<<(std::ostream& izlaz , const Duration& a){
      if((a.get_h()==0)||(a.get_m()==0)||(a.get_s()==0))
       izlaz << a.get_h() << "0" << ":" << a.get_m() << "0" << ":" << a.get_s() << "0";
      else{
        if(a.get_h()>=10)
          izlaz << a.get_h() << ":";
        else 
          izlaz << "0" << a.get_h() << ":";
        if(a.get_m()>=10)
          izlaz << a.get_m() << ":";
        else 
          izlaz << "0" << a.get_m() << ":";
        if(a.get_s()>=10)
          izlaz << a.get_s();
        else 
          izlaz << "0" << a.get_s();
      }
    return izlaz;
    }
    friend std::istream& operator>>(std::istream& unos, Duration& a){
      std::string rez;
      unos >> rez;
      a=Duration(rez);
      return unos;
    }
  private:
    int _sekunde=0;
    int _minute=0;
    int _sati=0;
};
