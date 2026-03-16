// Source: https://leetcode.com/problems/find-maximum-removals-from-source-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string source of size n, a string pattern that is a subsequence of source, and a sorted integer array targetIndices that contains distinct numbers in the range [0, n - 1].
//
// We define an operation as removing a character at an index idx from source such that:
//
//
// 	idx is an element of targetIndices.
// 	pattern remains a subsequence of source after removing the character.
//
//
// Performing an operation does not change the indices of the other characters in source. For example, if you remove 'c' from "acb", the character at index 2 would still be 'b'.
//
// Return the maximum number of operations that can be performed.
//
// Example:
// Input: source = "abbaa", pattern = "aba", targetIndices = [0,1,2]
//
// Output: 1
//
// Explanation:
//
// We can't remove source[0] but we can do either of these two operations:
//
//
// 	Remove source[1], so that source becomes "a_baa".
// 	Remove source[2], so that source becomes "ab_aa".
//
// Constraints:
// 1 <= n == source.length <= 3 * 103
// 	1 <= pattern.length <= n
// 	1 <= targetIndices.length <= n
// 	targetIndices is sorted in ascending order.
// 	The input is generated such that targetIndices contains distinct elements in the range [0, n - 1].
// 	source and pattern consist only of lowercase English letters.
// 	The input is generated such that pattern appears as a subsequence in source.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean canRemove(String source, String pattern, int[] targetIndices, int removals) {
        int n = source.length();
        boolean[] removed = new boolean[n];
        for (int i = 0; i < removals; i++) {
            removed[targetIndices[i]] = true;
        }

        int pIndex = 0;
        for (int sIndex = 0; sIndex < n; sIndex++) {
            if (removed[sIndex]) {
                continue;
            }
            if (source.charAt(sIndex) == pattern.charAt(pIndex)) {
                pIndex++;
                if (pIndex == pattern.length()) {
                    return true;
                }
            }
        }

        return pIndex == pattern.length();
    }
    public int maxRemovals(String source, String pattern, int[] targetIndices) {
        int left = 0, right = targetIndices.length;

        while (left < right) {
            int mid = left + (right - left + 1) / 2;

            if (canRemove(source, pattern, targetIndices, mid)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return left;            
    }
}
