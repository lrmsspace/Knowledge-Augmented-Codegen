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
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int beautifulSubstrings(String s, int k) {
        int count = 0;
        for (int i = 0; i < s.length(); i++) {
            int vowels = 0, consonants = 0;
            for (int j = i; j < s.length(); j++) {
                char c = s.charAt(j);
                if (isVowel(c)) {
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
