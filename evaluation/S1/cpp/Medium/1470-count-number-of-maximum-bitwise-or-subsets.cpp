// Source: https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return the number of different non-empty subsets with the maximum bitwise OR.
//
// An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b. Two subsets are considered different if the indices of the elements chosen are different.
//
// The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).
//
// Example:
// Input: nums = [3,1]
// Output: 2
// Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
// - [3]
// - [3,1]
//
// Constraints:
// 1 <= nums.length <= 16
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        int n = nums.size();
        int maxOr = 0;
        for (int num : nums) {
            maxOr |= num;
        }

        int count = 0;
        int totalMasks = 1 << n;
        for (int mask = 1; mask < totalMasks; ++mask) {
            int currentOr = 0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    currentOr |= nums[i];
                }
            }
            if (currentOr == maxOr) {
                count++;
            }
        }

        return count;           
    }
};
