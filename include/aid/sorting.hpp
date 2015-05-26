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

}
