#include <catch.hpp>
#include "optimized_bubble_sort.h"
#include <vector>


TEST_CASE("OptimizedBubbleSort: variant 2", "[lab1][opt_bubble][variant2]") {
    std::vector<int> arr = { 5, 10, 18, 0, 2, 7, 11, 14 };
    optimizedBubbleSort(arr);
    REQUIRE(arr == std::vector<int>{ 0, 2, 5, 7, 10, 11, 14, 18 });
}

TEST_CASE("OptimizedBubbleSort: empty array", "[opt_bubble][edge]") {
    std::vector<int> arr = {};
    optimizedBubbleSort(arr);
    REQUIRE(arr.empty());
}

TEST_CASE("OptimizedBubbleSort: single element", "[opt_bubble][edge]") {
    std::vector<int> arr = { 42 };
    optimizedBubbleSort(arr);
    REQUIRE(arr.size() == 1);
    REQUIRE(arr[0] == 42);
}

TEST_CASE("OptimizedBubbleSort: already sorted", "[opt_bubble][positive]") {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    optimizedBubbleSort(arr);
    std::vector<int> expected = { 1, 2, 3, 4, 5 };
    REQUIRE(arr == expected);
}

TEST_CASE("OptimizedBubbleSort: reverse sorted", "[opt_bubble][positive]") {
    std::vector<int> arr = { 5, 4, 3, 2, 1 };
    optimizedBubbleSort(arr);
    std::vector<int> expected = { 1, 2, 3, 4, 5 };
    REQUIRE(arr == expected);
}

TEST_CASE("OptimizedBubbleSort: random order", "[opt_bubble][positive]") {
    std::vector<int> arr = { 64, 34, 25, 12, 22, 11, 90 };
    optimizedBubbleSort(arr);
    std::vector<int> expected = { 11, 12, 22, 25, 34, 64, 90 };
    REQUIRE(arr == expected);
}

TEST_CASE("OptimizedBubbleSort: double type", "[opt_bubble][positive]") {
    std::vector<double> arr = { 3.14, 1.41, 2.71, 0.57 };
    optimizedBubbleSort(arr);
    std::vector<double> expected = { 0.57, 1.41, 2.71, 3.14 };
    REQUIRE(arr == expected);
}

TEST_CASE("OptimizedBubbleSort: duplicate elements", "[opt_bubble][positive]") {
    std::vector<int> arr = { 3, 1, 4, 1, 5, 9, 2, 6, 5 };
    optimizedBubbleSort(arr);
    std::vector<int> expected = { 1, 1, 2, 3, 4, 5, 5, 6, 9 };
    REQUIRE(arr == expected);
}