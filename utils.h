//******************************************************************************************
//File: utils.h
//Programmer: William McCarthy
//Date: 10/18/2020
//Description: Utility header file.
//******************************************************************************************

#ifndef __utils_h__
#define __utils_h__

#include <iostream>
#include <fstream>
#include <cstdlib>


#define ARGC_ERROR  1
#define FILENAME_ERROR  2

class begin_end {
public:
  begin_end() : function_name(__FUNCTION__) {
    std::cout << "......... Beginning of " << function_name
              << ".................................\n";
  }
  ~begin_end() {
    std::cout << "................................. end of "
              << function_name << "......... \n";
  }
private:
  std::string function_name;
};


bool open_cmdline_file(int argc, const char* argv[], std::fstream& ifs) {
  if (argc != 2) {
    std::cerr << "Usage: ./sqb filename\n";
    exit(ARGC_ERROR);
  }
  std::string filename = argv[1];

  ifs.open(filename);
  if (!ifs.is_open()) {
    std::cerr << "Could not open: '" << filename << "'\n";
    exit(FILENAME_ERROR);
  }
  return true;
}

//==========================================================================
// printing utilities
//==========================================================================
std::string yes_or_no(bool condition) { return condition ? "YES" : "no"; }

template <typename T>
void print(const std::string& msg, T* arr, size_t low, size_t high) {
  std::cout << msg;
  for (size_t i = low; i < high; ++i) { std::cout << arr[i] << " "; }
}

template <typename T>
void print(const std::string& msg, T* arr, size_t n) { print(msg, arr, 0, n - 1); }


//==========================================================================
// sorting utilities
//==========================================================================
template <typename T>
struct comparator {
  comparator() { }
  virtual bool operator()(const T& v, const T& w) const = 0;
};

template <typename T>
struct fwd_comparator : public comparator<T> {
  virtual bool operator()(const T& v, const T& w) const override { return v < w; }
};

template <typename T>
struct rev_comparator : public comparator<T> {
  virtual bool operator()(const T& v, const T& w) const override { return w < v; }
};

template <typename T>
struct null_comparator : public comparator<T> {
  virtual bool operator()(const T& v, const T& w) const override { return false; }
};

// template <typename T>
// struct comparator_lambda : public comparator<T> {
//   comparator_lambda(const std::function<bool(const T&, const T&)>& lambda)
//   : lambda_(lambda) { }
  
//   virtual bool operator()(const T& v, const T& w) const {
//     bool result = lambda_(v, w);
//     return result;
//   }
//   std::function <bool(const T&, const T&)> const lambda_;
// };

template <typename T>
bool less(T& v, T& w) { return v < w; }

template <typename T>
bool less(T& v, T& w, const comparator<T>& comp) { return comp(v, w); }

template <typename T>
bool compare(T& v, T& w) {
  int result;

  if (less(v, w))        { result = -1;
  } else if (less(w, v)) { result = 1;
  } else                 { result = 0; }

  return result;
}

template <typename T>
int compare(T& v, T& w, const comparator<T>& comp) {
  int result;

  if (less(v, w, comp))        { result = -1;
  } else if (less(w, v, comp)) { result = 1;
  } else                       { result = 0; }

  return result;
}


template <typename T>
void exchange(T* a, size_t i, size_t j) {
  T swap = a[i];
  a[i] = a[j];
  a[j] = swap;
}


template <typename T>
bool is_sorted(T* a, size_t low, size_t high) {
  for (size_t i = low + 1; i < high; ++i) {
    if (less(a[i], a[i - 1])) { return false; }
  }
  return true;
}

template <typename T>
bool is_sorted(T* a, size_t low, size_t high, const comparator<T>& comp) {
  for (size_t i = low + 1; i < high; ++i) {
    if (less(a[i], a[i - 1], comp)) { return false; }
  }
  return true;
}


template <typename T>
bool is_sorted(T* a, size_t size) { return is_sorted(a, 0, size - 1); }

template <typename T>
bool is_sorted(T* a, size_t size, const comparator<T>& comp) {
  return is_sorted(a, 0, size - 1, comp);
}

//==========================================================================


#endif /* __utils_h__ */
