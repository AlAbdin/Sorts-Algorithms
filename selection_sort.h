//******************************************************************************************
//File: selection_sort.h
//Programmer: Alaa Abdin
//Date: 09/18/2020
//Description: Selection sort header file.
//******************************************************************************************
#ifndef selection_sort_h
#define selection_sort_h

#include <cassert>
#include "utils.h"

template <typename T>
class selection_sort {          
public:
  static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
    for (size_t i = 0; i < n; ++i) {
      size_t min = i;
      for (size_t j = i + 1; j < n; ++j) {
        if (less(arr[j], arr[min], comp)) { min = j; }      // return (arr[j] < arr[min]);
      }
      exchange(arr, i, min);
    }
    assert(is_sorted(arr, n, comp));
  }
};


#endif /* selection_sort_h */
