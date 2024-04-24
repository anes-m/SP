#pragma once
#include <iostream>
#include <initializer_list>


template<typename T>
class MojVektor{
  public:
    class Iterator;
    MojVektor();
    MojVektor(const std::initializer_list<T>&);
    MojVektor(const MojVektor&);
    MojVektor(MojVektor&&);
    MojVektor& operator=(const MojVektor&);
    MojVektor& operator=(MojVektor&&);
    ~MojVektor();
    size_t capacity() const { return capacity_; };
    size_t size() const { return size_; };
    T& at(size_t);
    void push_back(const T&);
    void push_back(T&&);
    void push_front(const T&);
    void push_front(T&&);
    void pop_back();
    void pop_front();
    void resize(size_t newSize,const T& default_vale);
    void clear();
    T& back() const;
    T& front() const;
    bool empty() const { return size_ == 0;};
    bool full() const { return capacity_ == size_;};
    bool operator==(const MojVektor& other) const;
    bool operator!=(const MojVektor& other) const; 
    T& operator[](size_t index )const { return data_[index];};
    Iterator begin() const { return Iterator {data_}; };
    Iterator end() const { return Iterator {data_+size_}; };
    Iterator find( const T&) const;
    Iterator erase(Iterator);
    Iterator erase(Iterator, Iterator);
    Iterator insert(Iterator, const T&);
    Iterator insert(Iterator, T&&);
    Iterator rbegin() const;
    Iterator rend() const;
    MojVektor subvector(Iterator, Iterator);
    void rotate();
    void rotate(Iterator, Iterator);
    T* data()const {return data_; };
  private:
    void realoc();
    size_t capacity_;
    size_t size_;
    T* data_;

};

template<typename T>
class MojVektor<T>::Iterator { 
  public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef  T value_type;
    typedef size_t difference_type;
    typedef T* pointer;
    typedef T& reference;
  public: 
    Iterator() noexcept : pointer_{nullptr}{};
    Iterator( T* point ): pointer_{ point }{};
    Iterator( const Iterator& it ): pointer_{ it.pointer_ }{};
    Iterator( Iterator&& it ): pointer_{ it.pointer_ }{ it.pointer_=nullptr; };
    Iterator& operator=( const Iterator& it) { pointer_=it.pointer_; return *this; };
    Iterator& operator=( Iterator&& it ){ pointer_=it.pointer_; it.pointer_=nullptr; return *this; };
    ~Iterator(){ pointer_=nullptr; };
    Iterator& operator++() { ++pointer_; return *this; };
    Iterator& operator--() { --pointer_; return *this; };
    Iterator& operator++(int) { auto it = *this ; ++pointer_; return it; };
    Iterator& operator--(int) { auto it = *this ; --pointer_; return it; };
    T& operator*(){ return *pointer_;};
    T& operator*() const { return *pointer_;};
    T* operator->(){return pointer_;};
    T* operator->() const {return pointer_;};
    T* operator[](size_t index){ return pointer_+index;};
    T* operator[](size_t index) const { return pointer_+index;};
    Iterator operator+(int n) const { return Iterator{pointer_+n}; };
    Iterator& operator+=(int n) const { pointer_+=n; return *this; };
    Iterator operator-(int n) const { return Iterator{pointer_-n}; };
    int operator-(const Iterator& it) const {return pointer_-it.pointer_; };
    bool operator==(const Iterator& it) const { return pointer_ == it.pointer_;};
    bool operator!=(const Iterator& it) const { return pointer_ != it.pointer_;};
    bool operator<(const Iterator& it) const {return pointer_ < it.pointer_;};
    bool operator>(const Iterator& it) const {return pointer_ > it.pointer_;};
    bool operator<=(const Iterator& it) const {return pointer_ <= it.pointer_;};
    bool operator>=(const Iterator& it) const {return pointer_ >= it.pointer_;};
  private:
    T* pointer_;
};

template<typename T>  
  MojVektor<T>::MojVektor(): capacity_{10}, size_{0}, data_{ new T [capacity_]} { }
template<typename T>  
  MojVektor<T>::MojVektor(const std::initializer_list<T>& lista){  
    capacity_ = lista.size();
    size_ = lista.size();
    data_ = new T [capacity_];
    std::copy(lista.begin(), lista.end(), data_);
  }
template<typename T>  
  MojVektor<T>::MojVektor(const MojVektor& other){  
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = new T [capacity_];
    for(auto i = 0;  i < size_ ; ++i){
      data_[i] = other.data_[i];
    }
  }
template<typename T>  
  MojVektor<T>::MojVektor( MojVektor&& other){  
    capacity_ = other.capacity_;    other.capacity_ = 0;
    size_ = other.size_;    other.size_ = 0;
    data_ = other.data_;    other.data_ = nullptr;
  }
template<typename T>  
  MojVektor<T>& MojVektor<T>::operator=(const  MojVektor& other){
    if( this != &other ){
      capacity_ = other.capacity_;
      size_ = other.size_;
      data_ = new T[capacity_];
      for(auto i = 0;  i < size_ ; ++i){
        data_[i] = other.data_[i];
      }
    }
    return *this;
  }
template<typename T>  
  MojVektor<T>& MojVektor<T>::operator=( MojVektor&& other){  
    if( this != &other ){ 
      capacity_ = other.capacity_;    
      size_ = other.size_;
      data_ = other.data_;    other.data_ = nullptr;
      other.capacity_ = other.size_ = 0;
    }
    return *this;
  }
template<typename T>
  MojVektor<T>::~MojVektor(){
    capacity_ =  size_ = 0;
    data_ = nullptr;
  }
template<typename T>
  void MojVektor<T>::realoc(){
    capacity_*=2;
    T* temp = new T[capacity_];
    for(auto i = 0 ; i < size_ ; ++i){
      temp[i] = data_[i];
    }
    delete [] data_;
    data_ = temp;
}
template<typename T>
  void MojVektor<T>::clear(){
    delete [] data_;
    data_ = nullptr;
    size_ = 0;
  }
template<typename T>
  T&  MojVektor<T>::at(size_t index ){
    if( 0 > index || index > size_ )
      throw std::out_of_range{"Van granica vektora!"};
    else{
      return data_[index];
    }
  }
template<typename T>
  void MojVektor<T>::push_back(const T& element){
    if( capacity_ == size_ )
      realoc();
    if( data_ == nullptr ){
      capacity_ = 10;
      size_ = 0;  
      data_ = new T[capacity_];
    }
    data_[size_++] = element;
  } 
template<typename T>
  void MojVektor<T>::push_back( T&& element){
    if( capacity_ == size_ )
      realoc(); 
    if( data_ == nullptr ){
      capacity_ = 10;
      size_ = 0;
      data_ = new T[capacity_];
    }
    data_[size_++] = std::move(element);
  }
template<typename T>
  void MojVektor<T>::push_front(const T& element ){
    if( capacity_ == size_ )
      realoc(); 
    if( data_ == nullptr ){
      capacity_ = 10;
      data_ = new T[capacity_];
      size_ = 0;
    }
    for(auto i = size_ ; 0 < i ; --i){
      data_[i] = std::move(at(i-1));
    }
    data_[0] = element;
    ++size_;
  }
template<typename T>
  void MojVektor<T>::push_front( T&& element ){
    if( capacity_ == size_ )
      realoc(); 
    if( data_ == nullptr ){
      capacity_ = 10;
      size_ = 0;
      data_ = new T[capacity_];
    }
    for(auto i = size_ ; 0 < i ; --i){
      data_[i] = std::move(at(i-1));
    }
    data_[0] = std::move(element);
    ++size_;
  }
template<typename T>
  void MojVektor<T>::pop_back(){
    if(size_ == 0){
      throw std::out_of_range{"Vektor je prazan."};
    }else{
      --size_;
    }
  }
template<typename T>
  void MojVektor<T>::pop_front(){
    if(size_ == 0){
      throw std::out_of_range{"Vektor je prazan."};
    }
    else{
      for(auto i = 1 ; i < size_; ++i){
        data_[i-1]= std::move(data_[i]);
      }
      size_--;
    }
  }
template<typename T>
  void MojVektor<T>::resize(size_t newSize, const T& default_vale ){
    if( newSize < size_){
      size_ = newSize;
    }else if( capacity_ < newSize ){
      realoc();
      for(auto i = size_ ; i < newSize ; ++i)
        data_[i] = default_vale;
      size_ = newSize;
    }
  }
template<typename T>
  T& MojVektor<T>::back()const {
    if(empty()){
      throw std::out_of_range{"Prazan komtejner"};
    }else{
      return data_[size_-1];
    }
  }
template<typename T>
  T& MojVektor<T>::front()const {
    if(empty()){
      throw std::out_of_range{"Prazan komtejner"};
    }else{
      return data_[0];
    }
  }
template<typename T>
  bool MojVektor<T>::operator==(const MojVektor<T>& other) const {
    if( size_ != other.size_ )
      return false;
    else{
      for(auto i = 0; i < size_; ++i){
        if( data_[i] != other.data_[i])
          return false;
        }
      return true;
    }
  }
template<typename T>
  bool MojVektor<T>::operator!=(const MojVektor<T>& other) const {
    if( size_ == other.size_ )
      return false;
    else{
      for(auto i = 0; i < size_; ++i){
        if( data_[i] == other.data_[i])
          return false;
        }
      return true;
    }
  }
template<typename T>
  typename MojVektor<T>::Iterator MojVektor<T>::find(const T& value) const {
    for(auto i = begin(); i != end(); ++i){
      if(*i == value)
        return i;
    }
    return end();
  }
template<typename T>
  typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator pos) {
    if( pos == end())
      return end();
    for(auto i = pos; i <  end(); ++i){
      *i=std::move(*(i+1));
    }
    --size_;
    return pos;
  } 
template<typename T>
  typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt, Iterator endIt) {
    auto i=0;
    for(auto it = beginIt; it < endIt; ++it)
      ++i;
    for(auto it = beginIt, it2 = endIt ; it2 < end() ; ++it, ++it2){
      *it=std::move(*it2);
    }
    size_-=i;
    return beginIt;
  } 

template<typename T>
  typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos,const  T& value){
    if( pos > end()-1 || pos < begin())
      throw std::out_of_range{"Vane granica vektora"};
      ++size_;
    if(full())
      realoc();
    for(auto it = end()-1 ; pos <= it ; --it ){
      *(it+1) = std::move(*it);
    }
    *pos = value;
    return pos;
  }
template<typename T>
  typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, T&& value){
    if( pos > end()-1 || pos < begin())
      throw std::out_of_range{"Vane granica vektora"};
      ++size_;
    if(full())
      realoc();
    for(auto it = end()-1 ; pos <= it ; --it ){
      *(it+1) = std::move(*it);
    }
    *pos = std::move(value);
    return pos;
  }

template<typename T>
  typename MojVektor<T>::Iterator MojVektor<T>::rbegin() const {
    if(empty())
      throw std::out_of_range{"Prazan vektor"};
    else
      return end()-1;
  }
template<typename T>
  typename MojVektor<T>::Iterator MojVektor<T>::rend() const {
    if(empty())
      throw std::out_of_range{"Prazan vektor"};
    else
      return begin()-1;
  }
template<typename T>
  MojVektor<T> MojVektor<T>::subvector(Iterator beginIt, Iterator endIt){
    MojVektor rez;
    for(auto it = beginIt ; it < endIt; ++it)
      rez.push_back(*it);
    return rez;
  }
template<typename T>
  void  MojVektor<T>::rotate(){
    for(auto ib = begin(), ie = end()-1; ib < ie; ++ib, --ie){
      auto pom = *ib;
      *ib = *ie;
      *ie = pom;
    }
  }
template<typename T>
  void  MojVektor<T>::rotate(Iterator beginIt, Iterator endIt){
    for(auto ib = beginIt, ie = endIt-1 ; ib < ie; ++ib, --ie){
      auto pom = *ib;
      *ib = *ie;
      *ie = pom;
    }
  }
template<typename T>
std::ostream& operator<<(std::ostream& output, const MojVektor<T> vektor){
  for(auto i = vektor.begin(); i < vektor.end(); ++i){
    if((i+1) == vektor.end())
      output << *i;
    else 
      output << *i << ", ";
  }
  return output;
}
