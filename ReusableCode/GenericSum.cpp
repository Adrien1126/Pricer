#ifndef GenericSum_CPP
#define GenericSum_CPP

#include "GenericSum.hpp"

template <class T> 
T sum(const T& a,const T& b){
    return a + b;
}

template <class T>
T sum(const T& a,const T& b,const T& c){
    return sum(sum(a,b),c);
}

#endif  // GenericSum_CPP
