// Source: https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s and a positive integer k.
//
// Return the length of the longest subsequence of s that makes up a binary number less than or equal to k.
//
// Note:
//
//
// 	The subsequence can contain leading zeroes.
// 	The empty string is considered to be equal to 0.
// 	A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: s = "1001010", k = 5
// Output: 5
// Explanation: The longest subsequence of s that makes up a binary number less than or equal to 5 is "00010", as this number is equal to 2 in decimal.
// Note that "00100" and "00101" are also possible, which are equal to 4 and 5 in decimal, respectively.
// The length of this subsequence is 5, so 5 is returned.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
// 	1 <= k <= 109
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, greedy, dp-1d)
//   • When to use: Use when finding the longest sequence of elements in a given array such that each element is greater than the preceding one, without changing their relative order. It's applicable for optimizing problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of an array where elements are in strictly increasing order. It can be solved in O(N log N) time using a greedy approach with binary search, or O(N^2) using dynamic programming.
//   • Invariants: The 'tails' array elements are always in strictly increasing order.; tails[i] stores the smallest possible ending element of an increasing subsequence of length i+1.
//   • Tips: Prefer the O(N log N) greedy approach with binary search for better performance.; The 'tails' array in the greedy approach stores the smallest tail of all increasing subsequences of a certain length.
//   • Pitfalls: Confusing LIS with Longest Common Subsequence (LCS) or contiguous subarrays.; Incorrectly handling duplicate elements when 'strictly increasing' is required.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int longestSubsequence(string s, int k) {
        int n = s.size();
        int countZeros = 0;
        int length = 0;
        // Count all '0's since they can always be included
        for (char c : s) {
            if (c == '0') {
                countZeros++;
            }
        }
        length += countZeros;

        // Now consider '1's from the end, checking if they can fit within k
        long long currentValue = 0;
        long long powerOfTwo = 1; // Represents 2^i
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '1') {
                // Check if adding this '1' would exceed k
                if (currentValue + powerOfTwo <= k) {
                    currentValue += powerOfTwo;
                    length++;
                }
            }
            // Update powerOfTwo for the next bit to the left
            powerOfTwo <<= 1;
            // If powerOfTwo exceeds k, no need to consider further bits
            if (powerOfTwo > k) {
                break;
            }
        }

        return length;          
    }
};
