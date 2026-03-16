// Source: https://leetcode.com/problems/maximum-strong-pair-xor-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums. A pair of integers x and y is called a strong pair if it satisfies the condition:
//
//
// 	|x - y| <= min(x, y)
//
//
// You need to select two integers from nums such that they form a strong pair and their bitwise XOR is the maximum among all strong pairs in the array.
//
// Return the maximum XOR value out of all possible strong pairs in the array nums.
//
// Note that you can pick the same integer twice to form a pair.
//
// Example:
// Input: nums = [1,2,3,4,5]
// Output: 7
// Explanation: There are 11 strong pairs in the array nums: (1, 1), (1, 2), (2, 2), (2, 3), (2, 4), (3, 3), (3, 4), (3, 5), (4, 4), (4, 5) and (5, 5).
// The maximum XOR possible from these pairs is 3 XOR 4 = 7.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= nums[i] <= 220 - 1
//
// Helpful references (internal KB):
// - Sqrt Tree (array, tree, recursion)
//   • When to use: When you need to perform O(1) range queries and support efficient updates (single element or range) on an array, leveraging a hierarchical decomposition.
//   • Idea: A Sqrt Tree is a data structure that supports O(1) range queries and efficient updates on an array. It recursively decomposes the array into blocks and layers, using precomputed information and bitwise operations to quickly answer queries and propagate updates.
//   • Invariants: Each element is part of exactly one block at each layer of the Sqrt Tree.; The highest differing bit between `l` and `r` identifies the specific layer for processing `q(l, r)`.
//   • Tips: Precompute highest bit for efficient layer selection.; Decompose queries into intra-block and inter-block segments.
//   • Pitfalls: Naive updates can result in O(N) complexity per update.; High memory consumption due to multiple layers of precomputed arrays.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximumStrongPairXor(vector<int>& nums) {
        int n = nums.size();
        int maxXor = 0;

        // Check all pairs (i, j) where i <= j
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (abs(nums[i] - nums[j]) <= min(nums[i], nums[j])) {
                    maxXor = max(maxXor, nums[i] ^ nums[j]);
                }
            }
        }

        return maxXor;          
    }
};
