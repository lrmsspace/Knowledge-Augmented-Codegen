// Source: https://leetcode.com/problems/replace-question-marks-in-string-to-minimize-its-value/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s. s[i] is either a lowercase English letter or '?'.
//
// For a string t having length m containing only lowercase English letters, we define the function cost(i) for an index i as the number of characters equal to t[i] that appeared before it, i.e. in the range [0, i - 1].
//
// The value of t is the sum of cost(i) for all indices i.
//
// For example, for the string t = "aab":
//
//
// 	cost(0) = 0
// 	cost(1) = 1
// 	cost(2) = 0
// 	Hence, the value of "aab" is 0 + 1 + 0 = 1.
//
//
// Your task is to replace all occurrences of '?' in s with any lowercase English letter so that the value of s is minimized.
//
// Return a string denoting the modified string with replaced occurrences of '?'. If there are multiple strings resulting in the minimum value, return the lexicographically smallest one.
//
// Example:
// Input:   s = "???" 
//
// Output:   "abc" 
//
// Explanation:  In this example, we can replace the occurrences of '?' to make s equal to "abc".
//
// For "abc", cost(0) = 0, cost(1) = 0, and cost(2) = 0.
//
// The value of "abc" is 0.
//
// Some other modifications of s that have a value of 0 are "cba", "abz", and, "hey".
//
// Among all of them, we choose the lexicographically smallest.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either a lowercase English letter or '?'.
//
// Helpful references (internal KB):
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String minimizeStringValue(String s) {
        StringBuilder sb = new StringBuilder(s);
        int n = sb.length();

        for (int i = 0; i < n; i++) {
            if (sb.charAt(i) == '?') {
                for (char c = 'a'; c <= 'z'; c++) {
                    if ((i > 0 && sb.charAt(i - 1) == c) || (i < n - 1 && sb.charAt(i + 1) == c)) {
                        continue;
                    }
                    sb.setCharAt(i, c);
                    break;
                }
            }
        }

        return sb.toString();           
    }
}
