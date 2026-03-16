// Source: https://leetcode.com/problems/minimum-number-of-chairs-in-a-waiting-room/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s. Simulate events at each second i:
//
//
// 	If s[i] == 'E', a person enters the waiting room and takes one of the chairs in it.
// 	If s[i] == 'L', a person leaves the waiting room, freeing up a chair.
//
//
// Return the minimum number of chairs needed so that a chair is available for every person who enters the waiting room given that it is initially empty.
//
// Example:
// Input: s = "EEEEEEE"
//
// Output: 7
//
// Explanation:
//
// After each second, a person enters the waiting room and no person leaves it. Therefore, a minimum of 7 chairs is needed.
//
// Constraints:
// 1 <= s.length <= 50
// 	s consists only of the letters 'E' and 'L'.
// 	s represents a valid sequence of entries and exits.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumChairs(char* s) {
    int currentChairs = 0; // Tracks the number of chairs currently occupied
    int maxChairs = 0;     // Tracks the maximum number of chairs needed at any time

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'E') {
            currentChairs++; // A person enters, so we need one more chair
            if (currentChairs > maxChairs) {
                maxChairs = currentChairs; // Update maxChairs if current exceeds it
            }
        } else if (s[i] == 'L') {
            currentChairs--; // A person leaves, so we free up a chair
        }
    }

    return maxChairs; // The maximum number of chairs needed at any time        
}
