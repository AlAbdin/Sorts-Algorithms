#ifndef quick_sort_h
#define quick_sort_h

#include <cassert>
#include "utils.h"
#include "random.h"


template <typename T>
class quick_sort{
    public:
        static void sort(T *arr, size_t n, const comparator<T> &comp = fwd_comparator<T>()){
            std_random<T>::shuffle(arr, n);
            sort(arr, 0, n - 1, comp);
        }

        static T select(T *arr, size_t n, size_t k, const comparator<T> &comp = fwd_comparator<T>()){
            std_random<T>::shuffle(arr, n);
            size_t lo = 0, hi = n - 1;
            while (hi > lo){
                size_t i = partition(arr, lo, hi, comp);
                if (i < k)
                    lo = i + 1;
                else if (i > k)
                    hi = (i == 0 ? 0 : i - 1);
                else
                    return arr[i];
            }
            return arr[k];
        }

    private:
        static const int CUTOFF_ = 10;
        static void sort(T *arr, size_t lo, size_t hi, const comparator<T> &comp = fwd_comparator<T>()){
            if (hi <= lo)
                return;
            insertion_sort<T> insertion;
            if (hi <= lo + CUTOFF_ - 1){
                insertion.sort(arr, lo, hi, comp);
                return;
            }
            size_t j = partition(arr, lo, hi, comp);
            sort(arr, lo, (j == 0 ? 0 : j - 1), comp);
            sort(arr, j + 1, hi, comp);
            assert (is_sorted(arr, lo, hi, comp));
        }

        static size_t partition(T *arr, size_t lo, size_t hi, const comparator<T> &comp = fwd_comparator<T>()){
            size_t i = lo, j = hi + 1;
            while (true) {
                while (less(arr[++i], arr[lo], comp)){
                    if (i == hi)
                        break;
                }
                while (less(arr[lo], arr[--j], comp)){
                    if (j == lo)
                        break; 
                }
                if (i >= j)
                    break;

                exchange(arr, i, j);
            }
            exchange(arr, lo, j);
            return j;
        }
};

template <typename T>
class quick_sort_3way{
public:
    static void sort(T *arr, size_t n, const comparator<T> &comp = fwd_comparator<T>()){
            std_random<T>::shuffle(arr, n);
            sort(arr, 0, n - 1, comp);
    }
private:
    static const int CUTOFF_ = 10;
    static void sort(T *arr, size_t lo, size_t hi, const comparator<T> &comp = fwd_comparator<T>()) { 
        if (hi <= lo) 
            return;
        insertion_sort<T> insertion;
        if (hi <= lo + CUTOFF_ - 1){
            insertion.sort(arr, lo, hi, comp);
             return;
         }
        size_t lt = lo, gt = hi;
        T value = arr[lo];
        size_t i = lo + 1;

        while (i <= gt) {
            if (less (arr[i], value, comp))
                exchange (arr, lt++, i++);
            else if (less(value, arr[i], comp)){
                exchange (arr, i ,gt);
                if (gt != 0)
                    --gt;
            }
            else
                ++i;    
        }

        sort(arr, lo, (lt == 0 ? 0 : lt-1), comp);
        sort(arr, gt+1, hi, comp);
        assert (is_sorted(arr, lo, hi, comp));
    }
};
#endif /* quick_sort_h */
