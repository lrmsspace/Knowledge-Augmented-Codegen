// Source: https://leetcode.com/problems/count-beautiful-substrings-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and a positive integer k.
//
// Let vowels and consonants be the number of vowels and consonants in a string.
//
// A string is beautiful if:
//
//
// 	vowels == consonants.
// 	(vowels * consonants) % k == 0, in other terms the multiplication of vowels and consonants is divisible by k.
//
//
// Return the number of non-empty beautiful substrings in the given string s.
//
// A substring is a contiguous sequence of characters in a string.
//
// Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
//
// Consonant letters in English are every letter except vowels.
//
// Example:
// Input: s = "baeyh", k = 2
// Output: 2
// Explanation: There are 2 beautiful substrings in the given string.
// - Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["y","h"]).
// You can see that string "aeyh" is beautiful as vowels == consonants and vowels * consonants % k == 0.
// - Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["b","y"]). 
// You can see that string "baey" is beautiful as vowels == consonants and vowels * consonants % k == 0.
// It can be shown that there are only 2 beautiful substrings in the given string.
//
// Constraints:
// 1 <= s.length <= 1000
// 	1 <= k <= 1000
// 	s consists of only English lowercase letters.
//
// Helpful references (internal KB):
// - Suffix array (array, string, suffix-array, divide-and-conquer, recursion)
//   • When to use: Use when you need to efficiently perform various string operations like pattern searching, finding repeated substrings, or comparing suffixes lexicographically on a given text. It is a fundamental data structure for advanced string algorithms.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string. It allows for efficient string operations, with construction typically achievable in O(N log N) or O(N) time for advanced algorithms.
//   • Invariants: The suffix array SA[i] stores the starting index of the i-th lexicographically smallest suffix.; All suffixes of the input string are present exactly once in the suffix array.
//   • Tips: Consider using SA-IS for optimal O(N) construction time and space complexity.; Pair the suffix array with an LCP array for enhanced functionality, such as finding longest common substrings.
//   • Pitfalls: Naive O(N^2 log N) construction is too slow for large input strings.; Implementing linear-time algorithms like SA-IS or DC3 can be complex and error-prone.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean isVowel(char c) {
        char lowerC = Character.toLowerCase(c);
        return lowerC == 'a' || lowerC == 'e' || lowerC == 'i' || lowerC == 'o' || lowerC == 'u';
    }
    public int beautifulSubstrings(String s, int k) {
        int n = s.length();
        int count = 0;

        for (int i = 0; i < n; i++) {
            int vowels = 0;
            int consonants = 0;

            for (int j = i; j < n; j++) {
                char ch = s.charAt(j);
                if (isVowel(ch)) {
                    vowels++;
                } else {
                    consonants++;
                }

                if (vowels == consonants && (vowels * consonants) % k == 0) {
                    count++;
                }
            }
        }

        return count;           
    }
}
