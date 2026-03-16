// Source: https://leetcode.com/problems/count-complete-subarrays-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// We call a subarray of an array complete if the following condition is satisfied:
//
//
// 	The number of distinct elements in the subarray is equal to the number of distinct elements in the whole array.
//
//
// Return the number of complete subarrays.
//
// A subarray is a contiguous non-empty part of an array.
//
// Example:
// Input: nums = [1,3,1,2,2]
// Output: 4
// Explanation: The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 2000
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
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countCompleteSubarrays(int* nums, int numsSize) {
    int distinctCount = 0;
    int count[2001] = {0}; // Count of each number (1 to 2000)
    int left = 0, right = 0;
    int result = 0;

    // First, count the number of distinct elements in the whole array
    for (int i = 0; i < numsSize; i++) {
        if (count[nums[i]] == 0) {
            distinctCount++;
        }
        count[nums[i]]++;
    }

    // Reset count for the sliding window
    for (int i = 0; i < 2001; i++) {
        count[i] = 0;
    }

    int currentDistinct = 0;

    while (right < numsSize) {
        // Expand the right pointer
        if (count[nums[right]] == 0) {
            currentDistinct++;
        }
        count[nums[right]]++;

        // If we have all distinct elements in the current window
        while (currentDistinct == distinctCount) {
            // All subarrays starting from left to right are complete
            result += (numsSize - right); // All subarrays [left, right], [left, right+1], ..., [left, numsSize-1]

            // Shrink the left pointer
            count[nums[left]]--;
            if (count[nums[left]] == 0) {
                currentDistinct--;
            }
            left++;
        }
        right++;
    }

    return result;      
}
