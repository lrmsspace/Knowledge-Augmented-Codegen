// Source: https://leetcode.com/problems/fruits-into-baskets-iii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i] represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the jth basket.
//
// From left to right, place the fruits according to these rules:
//
//
// 	Each fruit type must be placed in the leftmost available basket with a capacity greater than or equal to the quantity of that fruit type.
// 	Each basket can hold only one type of fruit.
// 	If a fruit type cannot be placed in any basket, it remains unplaced.
//
//
// Return the number of fruit types that remain unplaced after all possible allocations are made.
//
// Example:
// Input: fruits = [4,2,5], baskets = [3,5,4]
//
// Output: 1
//
// Explanation:
//
//
// 	fruits[0] = 4 is placed in baskets[1] = 5.
// 	fruits[1] = 2 is placed in baskets[0] = 3.
// 	fruits[2] = 5 cannot be placed in baskets[2] = 4.
//
//
// Since one fruit type remains unplaced, we return 1.
//
// Constraints:
// n == fruits.length == baskets.length
// 	1 <= n <= 105
// 	1 <= fruits[i], baskets[i] <= 109
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
// - Segment Tree (tree, array, segment-tree, merge-sort, binary-search)
//   • When to use: Use when processing range queries or updates on an array, or when efficient searching and sorting of data are required. It's also applicable for problems that can be broken down into smaller, independent subproblems.
//   • Idea: This card describes techniques for efficiently handling range queries and updates on arrays, as well as searching and sorting elements. These methods typically achieve logarithmic time complexity for operations.
//   • Invariants: Each node in the segment tree represents a specific range of the original array.; The target element, if present, is always within the current binary search interval [low, high].
//   • Tips: Segment trees are powerful for static arrays with dynamic queries.; Merge sort's divide-and-conquer approach can be adapted for counting inversions.
//   • Pitfalls: Off-by-one errors in binary search bounds.; Incorrect segment tree node merging logic.
// - Segment Tree (tree, array, segment-tree)
//   • When to use: Use when you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in logarithmic time.
//   • Idea: A Segment Tree is a tree-based data structure that stores information about array intervals, enabling efficient O(log n) range queries and point/range updates.
//   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; The value stored in a non-leaf node is an aggregation of the values from its direct children.
//   • Tips: Build the tree recursively, dividing the array into halves.; Use lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors when defining segment boundaries or array indices.; Forgetting to push down lazy tags before querying or updating children nodes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size();
        vector<int> sortedBaskets = baskets;
        sort(sortedBaskets.begin(), sortedBaskets.end());

        int unplacedCount = 0;
        for (int fruit : fruits) {
            // Find the leftmost basket that can accommodate the current fruit
            auto it = lower_bound(sortedBaskets.begin(), sortedBaskets.end(), fruit);
            if (it != sortedBaskets.end()) {
                // If a suitable basket is found, remove it from the sorted list
                sortedBaskets.erase(it);
            } else {
                // If no suitable basket is found, increment the unplaced count
                unplacedCount++;
            }
        }

        return unplacedCount;           
    }
};
