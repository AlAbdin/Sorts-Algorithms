//******************************************************************************************
//File: insertion_sort.h
//Programmer: Alaa Abdin
//Date: 10/12/2020
//Description: Insertion sort header file.
//******************************************************************************************
#ifndef insertion_sort_h
#define insertion_sort_h

#include <cassert>
#include "utils.h"

template <typename T>
class insertion_sort {
public:                       
  static void sort(T* arr, size_t low, size_t high, const comparator<T>& comp=fwd_comparator<T>()) {
    for (size_t i = low; i <= high; ++i) {
      for (size_t j = i; j > 0; --j) {
        if (less(arr[j], arr[j - 1], comp)) { exchange(arr, j, j - 1); }
        else { break; }
      }
    }
    assert(is_sorted(arr, low, high, comp));
  }
  static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
    sort(arr, 0, n - 1, comp);
  }
};


#endif /* insertion_sort_h */
