#pragma once

#include "libfork/core.hpp"
#include "libfork/schedule.hpp"
#include <vector>
#include <algorithm>
#include <iterator>

template<typename RandomIt, typename Compare>
RandomIt pivot_partition (RandomIt first, RandomIt last, Compare comp) {
    auto pivot_iter = std::prev(last);
    auto pivot = *pivot_iter;
    RandomIt i = first;

    for (RandomIt j = first; j != pivot_iter; ++j) {
        if (comp(*j, pivot)) {
            std::iter_swap(i, j);
            ++i;
        }
    }
    std::iter_swap(i, pivot_iter);
    return i;
}

// Async quicksort function using libfork
inline constexpr auto qsort_async = [](auto qsort_async, auto first, auto last, auto comp) -> lf::task<> {
    if (first != last && std::next(first) != last) {
        auto pivot_it = pivot_partition(first, last, comp); // Use the renamed partition

        // Fork the left partition
        co_await lf::fork(qsort_async)(first, pivot_it, comp);

        // Fork the right partition
        co_await lf::fork(qsort_async)(std::next(pivot_it), last, comp);

        // Wait for both partitions to be sorted
        co_await lf::join;
    }
    co_return;
};