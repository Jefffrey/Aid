#pragma once

#include <algorithm>
#include <iterator>

namespace aid {

    // worst case: n^2
    // average case: n^2
    // best case: n^2
    // space complexity: 1
    template<typename It>
    void bubble_sort(It first, It last) {
        for (auto it = std::prev(last); it != first; --it)
            for (auto it2 = first; it2 != it; ++it2)
                if (*it2 > *std::next(it2))
                    std::iter_swap(it2, std::next(it2));
    }

    // worst case: n^2
    // average case: n^2
    // best case: n
    // space complexity: 1
    template<typename It>
    void insertion_sort(It first, It last) {
        for (auto it = std::next(first); it != last; ++it)
            for (auto it2 = it; it2 != first && *std::prev(it2) > *it2; --it2)
                std::iter_swap(std::prev(it2), it2);
    }

    // worst case: n
    // average case: n
    // best case: n
    // space complexity: n
    template<typename It, typename OutIt>
    void merge(It first1, It last1, It first2, It last2, OutIt out) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 <= *first2) {
                *out++ = *first1++;
                if (first1 == last1) std::copy(first2, last2, out);
            } else {
                *out++ = *first2++;
                if (first2 == last2) std::copy(first1, last1, out);
            }
        }
    }

    // worst case: n * log(n)
    // average case: n * log(n)
    // best case: n * log(n)
    // space complexity: n
    template<typename It>
    void merge_sort(It first, It last) {
        if (std::distance(first, last) < 2) return;
        auto length = std::distance(first, last);
        auto middle = std::next(first, length / 2);
        merge_sort(first, middle);
        merge_sort(middle, last);
        
        std::vector<typename It::value_type> temp(length);
        merge(first, middle, middle, last, begin(temp));
        std::copy(begin(temp), end(temp), first);
    }

    namespace detail {

        // returns the left child of the given iterator
        // if the current iterator does not have a left child
        // in the range, the behaviour is undefined
        template<typename It>
        It left_child(It begin, It end, It current) {
            auto distance = std::distance(begin, current);
            return std::next(current, distance + 1);
        }

        // returns the right child of the given iterator;
        // if the current iterator does not have a right child
        // in the range, the behaviour is undefined
        template<typename It>
        It right_child(It begin, It end, It current) {
            auto distance = std::distance(begin, current);
            return std::next(current, distance + 2);
        }
        
        // returns the parent of the given iterator;
        // calling this on the root has undefined behaviour
        template<typename It>
        It parent(It begin, It end, It current) {
            auto distance = std::distance(begin, current);
            return std::prev(current, distance / 2 + 1);
        }
        
        // returns true only if the given iterator has
        // a left child in the range
        template<typename It>
        bool has_left_child(It begin, It end, It current) {
            auto distance = std::distance(begin, current);
            auto end_distance = std::distance(current, end);
            return end_distance > (distance + 1);
        }
        
        // returns true only if the given iterator has
        // a right child in the range
        template<typename It>
        bool has_right_child(It begin, It end, It current) {
            auto distance = std::distance(begin, current);
            auto end_distance = std::distance(current, end);
            return end_distance > (distance + 2);
        }
        
        // given a range and an iterator, it "takes" down
        // the value pointed to by the iterator, until the value
        // does not satisfy the given predicate over one of the children
        template<typename It, typename BinaryOp>
        void heapify(It first, It last, It i, BinaryOp op) {
            auto to_swap = i;
            if (has_left_child(first, last, i) && op(*left_child(first, last, i), *to_swap))
                to_swap = left_child(first, last, i);
            if (has_right_child(first, last, i) && op(*right_child(first, last, i), *to_swap))
                to_swap = right_child(first, last, i);
            if (to_swap != i) {
                std::iter_swap(to_swap, i);
                heapify(first, last, to_swap, op);
            }
        }
        
        // same version as above, 
        // just with `std::greater` as default predicate
        template<typename It>
        void heapify(It first, It last, It i) {
            heapify(first, last, i, std::greater<typename It::value_type>());
        }

    }
    
    // build the heap structure from an unsorted container
    template<typename It, typename BinaryOp>
    void build_heap(It first, It last, BinaryOp op) {
        for (auto it = detail::parent(first, last, last - 1); /* */; --it) {
            detail::heapify(first, last, it, op);
            if (it == first) break;
        }
    }
        
    // same version as above, 
    // just with `std::greater` as default predicate
    template<typename It>
    void build_heap(It first, It last) {
        build_heap(first, last, std::greater<typename It::value_type>());
    }
    
    // worst case: n * log(n)
    // average case: n * log(n)
    // worst case: n * log(n)
    // space complexity: 1
    template<typename It, typename BinaryOp>
    void heap_sort(It first, It last, BinaryOp op) {
        build_heap(first, last, op);
        for (auto heap_last = last - 1; heap_last != first; --heap_last) {
            std::iter_swap(first, heap_last);
            detail::heapify(first, heap_last, first, op);
        }
    }
    
    // same version as above, 
    // just with `std::greater` as default predicate
    template<typename It>
    void heap_sort(It first, It last) {
        heap_sort(first, last, std::greater<typename It::value_type>());
    }

}
