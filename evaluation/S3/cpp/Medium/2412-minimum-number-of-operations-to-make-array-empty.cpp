// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers.
//
// There are two types of operations that you can apply on the array any number of times:
//
//
// 	Choose two elements with equal values and delete them from the array.
// 	Choose three elements with equal values and delete them from the array.
//
//
// Return the minimum number of operations required to make the array empty, or -1 if it is not possible.
//
// Example:
// Input: nums = [2,3,3,2,2,4,2,3,4]
// Output: 4
// Explanation: We can apply the following operations to make the array empty:
// - Apply the first operation on the elements at indices 0 and 3. The resulting array is nums = [3,3,2,4,2,3,4].
// - Apply the first operation on the elements at indices 2 and 4. The resulting array is nums = [3,3,4,3,4].
// - Apply the second operation on the elements at indices 0, 1, and 3. The resulting array is nums = [4,4].
// - Apply the first operation on the elements at indices 0 and 1. The resulting array is nums = [].
// It can be shown that we cannot make the array empty in less than 4 operations.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//
//
//  
// Note: This question is the same as 2244: Minimum Rounds to Complete All Tasks.
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - MEX (minimal excluded) of a sequence (ds, enumeration)
//   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
//   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
//   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
//   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
//   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
// - bucket-sort (array, bucket-sort)
//   • When to use: When the input elements are uniformly distributed across a specific range, allowing for efficient partitioning and sorting.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket, then concatenates them. It achieves O(N+K) average time complexity, where N is elements and K is buckets, assuming uniform distribution.
//   • Invariants: All elements from the input are initially present in the unsorted collection.; After distribution, each element resides in exactly one bucket, corresponding to its value range.
//   • Tips: Choose the number of buckets carefully based on data range and distribution.; Use an efficient sorting algorithm for individual buckets (e.g., insertion sort for small buckets).
//   • Pitfalls: Poor performance with non-uniform data distribution, leading to elements clustering in few buckets.; Requires knowing the range of input values beforehand to define bucket boundaries.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minOperations(vector<int>& nums) {
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        int operations = 0;
        for (const auto& [num, count] : freq) {
            if (count == 1) {
                return -1; // Cannot remove a single element
            }
            operations += count / 3 + (count % 3 != 0); // 3 elements in one operation, if there's a remainder, we need one more operation
        }

        return operations;          
    }
};
