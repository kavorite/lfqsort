#include "lfqsort.hh"
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <cassert>

int main() {
    // Sample size for test
    const int sample_size = 10000;

    // Generate a random list of integers
    std::vector<int> data(sample_size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100000);

    std::generate(data.begin(), data.end(), [&]() { return dis(gen); });

    // Create a copy of the original data for std::sort
    std::vector<int> reference_data = data;

    // Create a lazy_pool with the number of hardware threads
    lf::lazy_pool pool(std::thread::hardware_concurrency());

    // Custom comparator (ascending order)
    auto comp = std::less<int>();

    // Run the parallel quicksort (no template arguments needed)
    lf::sync_wait(pool, qsort_async, data.begin(), data.end(), comp);

    // Sort the reference data using std::sort
    std::sort(reference_data.begin(), reference_data.end());

    // Verify that both results are identical
    assert(data == reference_data);

    std::cout << "Test passed: Parallel quicksort matches std::sort." << std::endl;

    return 0;
}
