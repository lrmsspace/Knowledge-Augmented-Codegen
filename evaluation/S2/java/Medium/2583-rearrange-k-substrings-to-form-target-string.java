// Source: https://leetcode.com/problems/rearrange-k-substrings-to-form-target-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t, both of which are anagrams of each other, and an integer k.
//
// Your task is to determine whether it is possible to split the string s into k equal-sized substrings, rearrange the substrings, and concatenate them in any order to create a new string that matches the given string t.
//
// Return true if this is possible, otherwise, return false.
//
// An anagram is a word or phrase formed by rearranging the letters of a different word or phrase, using all the original letters exactly once.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "abcd", t = "cdab", k = 2
//
// Output: true
//
// Explanation:
//
//
// 	Split s into 2 substrings of length 2: ["ab", "cd"].
// 	Rearranging these substrings as ["cd", "ab"], and then concatenating them results in "cdab", which matches t.
//
// Constraints:
// 1 <= s.length == t.length <= 2 * 105
// 	1 <= k <= s.length
// 	s.length is divisible by k.
// 	s and t consist only of lowercase English letters.
// 	The input is generated such that s and t are anagrams of each other.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
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
    public boolean isPossibleToRearrange(String s, String t, int k) {
        int n = s.length();
        int m = n / k;

        // Step 1: Count the frequency of each character in s and t
        int[] countS = new int[26];
        int[] countT = new int[26];

        for (int i = 0; i < n; i++) {
            countS[s.charAt(i) - 'a']++;
            countT[t.charAt(i) - 'a']++;
        }

        // Step 2: Check if the frequency of characters in s can be rearranged to match t
        for (int i = 0; i < 26; i++) {
            if (countS[i] != countT[i]) {
                return false; // If frequencies don't match, return false
            }
        }

        // Step 3: Check if we can split s into k equal-sized substrings and rearrange them to form t
        // We need to ensure that the frequency of characters in each substring can be rearranged to match the corresponding frequency in t
        for (int i = 0; i < 26; i++) {
            if (countS[i] % m != 0) {
                return false; // If any character's frequency is not divisible by m, we cannot split it into equal substrings
            }
        }

        return true; // If all checks pass, return true         
    }
}
