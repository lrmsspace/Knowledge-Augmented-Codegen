// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a palindromic string s and an integer k.
//
// Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.
//
// Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.
//
// Example:
// Input: s = "abba", k = 2
//
// Output: "baab"
//
// Explanation:
//
//
// 	The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
// 	Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
// 	1 <= k <= 106
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
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
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string smallestPalindrome(string s, int k) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        string half;
        char midChar = '\0';
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 == 1) {
                midChar = 'a' + i;
            }
            half += string(count[i] / 2, 'a' + i);
        }

        string result;
        int totalPermutations = 1;
        for (int i = 2; i <= half.length(); ++i) {
            totalPermutations *= i;
        }
        for (int i = 0; i < 26; ++i) {
            for (int j = 2; j <= count[i] / 2; ++j) {
                totalPermutations /= j;
            }
        }

        if (k > totalPermutations) {
            return "";
        }

        string currentHalf;
        vector<bool> used(half.length(), false);
        for (int pos = 0; pos < half.length(); ++pos) {
            for (int i = 0; i < half.length(); ++i) {
                if (used[i]) continue;

                used[i] = true;
                int permutationsWithThisChar = 1;
                int remaining = half.length() - pos - 1;
                for (int j = 2; j <= remaining; ++j) {
                    permutationsWithThisChar *= j;
                }
                vector<int> freq(26, 0);
                for (int j = 0; j < half.length(); ++j) {
                    if (!used[j]) {
                        freq[half[j] - 'a']++;
                    }
                }
                for (int j = 0; j < 26; ++j) {
                    for (int l = 2; l <= freq[j]; ++l) {
                        permutationsWithThisChar /= l;
                    }
                }

                if (k > permutationsWithThisChar) {
                    k -= permutationsWithThisChar;
                    used[i] = false;
                } else {
                    currentHalf += half[i];
                    break;
                }
            }
        }

        result = currentHalf;
        if (midChar != '\0') {
            result += midChar;
        }
        reverse(currentHalf.begin(), currentHalf.end());
        result += currentHalf;
        return result;
    }
};
