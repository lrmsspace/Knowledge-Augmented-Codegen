// Source: https://leetcode.com/problems/minimum-time-to-revert-word-to-initial-state-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string word and an integer k.
//
// At every second, you must perform the following operations:
//
//
// 	Remove the first k characters of word.
// 	Add any k characters to the end of word.
//
//
// Note that you do not necessarily need to add the same characters that you removed. However, you must perform both operations at every second.
//
// Return the minimum time greater than zero required for word to revert to its initial state.
//
// Example:
// Input: word = "abacaba", k = 3
// Output: 2
// Explanation: At the 1st second, we remove characters "aba" from the prefix of word, and add characters "bac" to the end of word. Thus, word becomes equal to "cababac".
// At the 2nd second, we remove characters "cab" from the prefix of word, and add "aba" to the end of word. Thus, word becomes equal to "abacaba" and reverts to its initial state.
// It can be shown that 2 seconds is the minimum time greater than zero required for word to revert to its initial state.
//
// Constraints:
// 1 <= word.length <= 50 
// 	1 <= k <= word.length
// 	word consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    public int minimumTimeToInitialState(String word, int k) {
        int n = word.length();
        int gcd = gcd(n, k);
        return n / gcd;         
    }
}
