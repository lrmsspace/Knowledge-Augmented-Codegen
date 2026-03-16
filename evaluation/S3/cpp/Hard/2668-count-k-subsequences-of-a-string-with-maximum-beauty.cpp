// Source: https://leetcode.com/problems/count-k-subsequences-of-a-string-with-maximum-beauty/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k.
//
// A k-subsequence is a subsequence of s, having length k, and all its characters are unique, i.e., every character occurs once.
//
// Let f(c) denote the number of times the character c occurs in s.
//
// The beauty of a k-subsequence is the sum of f(c) for every character c in the k-subsequence.
//
// For example, consider s = "abbbdd" and k = 2:
//
//
// 	f('a') = 1, f('b') = 3, f('d') = 2
// 	Some k-subsequences of s are:
// 	
// 		"abbbdd" -> "ab" having a beauty of f('a') + f('b') = 4
// 		"abbbdd" -> "ad" having a beauty of f('a') + f('d') = 3
// 		"abbbdd" -> "bd" having a beauty of f('b') + f('d') = 5
// 	
// 	
//
//
// Return an integer denoting the number of k-subsequences whose beauty is the maximum among all k-subsequences. Since the answer may be too large, return it modulo 109 + 7.
//
// A subsequence of a string is a new string formed from the original string by deleting some (possibly none) of the characters without disturbing the relative positions of the remaining characters.
//
// Notes
//
//
// 	f(c) is the number of times a character c occurs in s, not a k-subsequence.
// 	Two k-subsequences are considered different if one is formed by an index that is not present in the other. So, two k-subsequences may form the same string.
//
// Example:
// Input: s = "bcca", k = 2
// Output: 4
// Explanation: From s we have f('a') = 1, f('b') = 1, and f('c') = 2.
// The k-subsequences of s are: 
// bcca having a beauty of f('b') + f('c') = 3 
// bcca having a beauty of f('b') + f('c') = 3 
// bcca having a beauty of f('b') + f('a') = 2 
// bcca having a beauty of f('c') + f('a') = 3
// bcca having a beauty of f('c') + f('a') = 3 
// There are 4 k-subsequences that have the maximum beauty, 3. 
// Hence, the answer is 4.
//
// Constraints:
// 1 <= s.length <= 2 * 105
// 	1 <= k <= s.length
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countKSubsequencesWithMaxBeauty(string s, int k) {
        const int MOD = 1000000007;
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        sort(freq.rbegin(), freq.rend());
        long long result = 1;
        for (int i = 0; i < k; ++i) {
            result = (result * freq[i]) % MOD;
        }
        return result;
    }
};
