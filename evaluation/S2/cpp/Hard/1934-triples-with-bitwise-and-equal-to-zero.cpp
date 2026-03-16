// Source: https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the number of AND triples.
//
// An AND triple is a triple of indices (i, j, k) such that:
//
//
// 	0 <= i < nums.length
// 	0 <= j < nums.length
// 	0 <= k < nums.length
// 	nums[i] & nums[j] & nums[k] == 0, where & represents the bitwise-AND operator.
//
// Example:
// Input: nums = [2,1,3]
// Output: 12
// Explanation: We could choose the following i, j, k triples:
// (i=0, j=0, k=1) : 2 & 2 & 1
// (i=0, j=1, k=0) : 2 & 1 & 2
// (i=0, j=1, k=1) : 2 & 1 & 1
// (i=0, j=1, k=2) : 2 & 1 & 3
// (i=0, j=2, k=1) : 2 & 3 & 1
// (i=1, j=0, k=0) : 1 & 2 & 2
// (i=1, j=0, k=1) : 1 & 2 & 1
// (i=1, j=0, k=2) : 1 & 2 & 3
// (i=1, j=1, k=0) : 1 & 1 & 2
// (i=1, j=2, k=0) : 1 & 3 & 2
// (i=2, j=0, k=1) : 3 & 2 & 1
// (i=2, j=1, k=0) : 3 & 1 & 2
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] < 216
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countTriplets(vector<int>& nums) {
        // Count the frequency of each number in nums
        vector<int> count(1 << 16, 0);
        for (int num : nums) {
            count[num]++;
        }

        int result = 0;

        // Iterate through all possible pairs of numbers (a, b)
        for (int a = 0; a < (1 << 16); ++a) {
            for (int b = 0; b < (1 << 16); ++b) {
                if (count[a] > 0 && count[b] > 0) {
                    // Calculate the bitwise AND of a and b
                    int c = a & b;
                    // If c is zero, add the product of their counts to the result
                    if (c == 0) {
                        result += count[a] * count[b];
                    }
                }
            }
        }

        return result;          
    }
};
