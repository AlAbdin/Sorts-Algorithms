//******************************************************************************************
//File: heap_sort.h
//Programmer: Alaa Abdin
//Date: 10/23/2020
//Description: Heap sort header file.
//******************************************************************************************
#ifndef heap_sort_h
#define heap_sort_h

#include <cassert>
#include "array.h"

template <typename T>
class heap_sort{
    public:
        static void sort(T* pq, size_t len, const comparator<T>& comp = fwd_comparator<T>()){
            for (size_t i = len/2; i >= 1; i--){
                sink(pq, i, len, comp);
            }
            size_t k = len;
            while(k > 1){
                exchange(pq, 0, k-1);
                k--;
                sink(pq, 1, k, comp);
            }

        }
    private:
        static void sink(T* pq, size_t k, size_t n, const comparator<T>& comp){
            while (2* k <= n){
                size_t j = 2*k;
                if (j < n && (less(pq[j-1], pq[j], comp)))
                    j++;
                if(!less(pq[k-1],  pq[j-1], comp))
                    break;
                exchange(pq, k-1, j-1);
                k = j;
            }
        }
};

template <typename T>
class max_pq_heap{
    public:
        max_pq_heap() : max_pq_heap(MIN_CAPACITY_){}
        max_pq_heap(size_t capacity) : pq_(capacity + 1){}
        max_pq_heap(size_t capacity, const comparator<T>& compar)
        : pq_(capacity + 1), comp(compar) { pq_.push_back(T()); } 

        max_pq_heap(const std::initializer_list<T>& li, const comparator<T>& compar)
        : max_pq_heap(li.size(), compar) {
            for (const T& el : li) {
            if (el != "-") { insert(el);
            } 
            else { std::cout << del_max() << " "; }
        }
            std::cout << "\t(" << size() << " left on the heap)\n\n";\
        }

        bool empty ()const { return pq_.empty();}

        void insert(const T& value, const comparator<T> & comp){
            pq_.push_bakc(value);
            swim(pq_.size(), comp);
        }

        T delMax(){
            T& max = pq_[1];
            size_t n = pq_.size();

            exchange(1,n);
            pq_.pop_back();
            sink(1);
            pq_[n + 1] = T();
            return max;
        }

        void swim(size_t k, const comparator<T>& comp){
            while (k > 1 && less(k/2, k, comp)){
                exchange(k, k/2);
                k /= 2;
            }
        }
        void sink(size_t k, const comparator<T>& comp){
            size_t n = pq_.size();

            while(2 * k <= n){
                size_t j = 2 * k;
                if(j < n && less(j, j + 1, comp)) 
                    ++j;
                if(!less(k, j, comp))
                    break;
                
                exchange(k, j);
                k = j;
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const max_pq_heap& maxpq) {
            if (maxpq.empty()) { return os << "max_pq_heap is empty\n"; }
            return os << maxpq.pq_ << "\n";
  }
    private:
        static const size_t MIN_CAPACITY_;

        void exchange(size_t i, size_t j){
            T& temp = pq_[i]; 
            pq_[i] = pq_[j];
            pq_[j] = temp;
        }

        bool less(size_t i, size_t j, const comparator<T> & comp){
            return::less(pq_[i], pq_[j], comp);
        }

        array_<T> pq_;
};

#endif /* heap_sort_h */