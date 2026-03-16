// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s (0-indexed)​​​​​​. You are asked to perform the following operation on s​​​​​​ until you get a sorted string:
//
//
// 	Find the largest index i such that 1 <= i < s.length and s[i] < s[i - 1].
// 	Find the largest index j such that i <= j < s.length and s[k] < s[i - 1] for all the possible values of k in the range [i, j] inclusive.
// 	Swap the two characters at indices i - 1​​​​ and j​​​​​.
// 	Reverse the suffix starting at index i​​​​​​.
//
//
// Return the number of operations needed to make the string sorted. Since the answer can be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "cba"
// Output: 5
// Explanation: The simulation goes as follows:
// Operation 1: i=2, j=2. Swap s[1] and s[2] to get s="cab", then reverse the suffix starting at 2. Now, s="cab".
// Operation 2: i=1, j=2. Swap s[0] and s[2] to get s="bac", then reverse the suffix starting at 1. Now, s="bca".
// Operation 3: i=2, j=2. Swap s[1] and s[2] to get s="bac", then reverse the suffix starting at 2. Now, s="bac".
// Operation 4: i=1, j=1. Swap s[0] and s[1] to get s="abc", then reverse the suffix starting at 1. Now, s="acb".
// Operation 5: i=2, j=2. Swap s[1] and s[2] to get s="abc", then reverse the suffix starting at 2. Now, s="abc".
//
// Constraints:
// 1 <= s.length <= 3000
// 	s​​​​​​ consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - String Sorts (array, string, number, radix-sort, recursion, counting-sort)
//   • When to use: Use when sorting a large collection of strings or integers with a limited range of character/digit values. It is particularly efficient for fixed-length keys but can be adapted for variable lengths.
//   • Idea: Radix sort is a non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys by individual digits or characters which share the same significant position and value. It typically achieves O(N*W) time complexity, where N is the number of items and W is the key length.
//   • Invariants: After each pass `d`, the elements are stably sorted according to their digits up to position `d`.; The counting sort subroutine correctly places elements into their sorted positions for the current digit, preserving relative order.
//   • Tips: LSD (Least Significant Digit) is simpler for fixed-length keys.; MSD (Most Significant Digit) is better for variable-length keys or when keys are very long.
//   • Pitfalls: Not efficient for small N or very large W due to constant factors.; Requires extra space for auxiliary array and counting array.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int makeStringSorted(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<int> count(26, 0);
        long long result = 0;
        long long factorial = 1;

        for (int i = n - 1; i >= 0; --i) {
            int c = s[i] - 'a';
            count[c]++;
            factorial = (factorial * count[c]) % MOD;

            long long permutations = factorial;
            for (int j = 0; j < c; ++j) {
                if (count[j] > 0) {
                    permutations = (permutations * modInverse(count[j], MOD)) % MOD;
                }
            }

            result = (result + permutations) % MOD;
        }

        return result;          
    }
};
