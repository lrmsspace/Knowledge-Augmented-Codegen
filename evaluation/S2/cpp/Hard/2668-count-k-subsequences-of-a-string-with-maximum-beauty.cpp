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
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
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
        const int MOD = 1e9 + 7;
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        sort(freq.rbegin(), freq.rend());
        long long max_beauty = 0;
        for (int i = 0; i < k; i++) {
            max_beauty += freq[i];
        }
        long long count = 1;
        for (int i = k; i < 26 && freq[i] > 0; i++) {
            count = (count * (freq[i] + 1)) % MOD;
        }
        return count;           
    }
};
