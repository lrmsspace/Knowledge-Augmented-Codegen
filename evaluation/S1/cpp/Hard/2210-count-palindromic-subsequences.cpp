// Source: https://leetcode.com/problems/count-palindromic-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// Given a string of digits s, return the number of palindromic subsequences of s having length 5. Since the answer may be very large, return it modulo 109 + 7.
//
// Note:
//
//
// 	A string is palindromic if it reads the same forward and backward.
// 	A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: s = "103301"
// Output: 2
// Explanation: 
// There are 6 possible subsequences of length 5: "10330","10331","10301","10301","13301","03301". 
// Two of them (both equal to "10301") are palindromic.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of digits.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
// - Suffix Array (string, array, counting-sort, radix-sort)
//   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
//   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
//   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
//   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
//   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countPalindromes(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<vector<int>> leftCount(n, vector<int>(10, 0));
        vector<vector<int>> rightCount(n, vector<int>(10, 0));

        for (int i = 1; i < n; ++i) {
            leftCount[i] = leftCount[i - 1];
            leftCount[i][s[i - 1] - '0']++;
        }

        for (int i = n - 2; i >= 0; --i) {
            rightCount[i] = rightCount[i + 1];
            rightCount[i][s[i + 1] - '0']++;
        }

        long long result = 0;
        for (int mid = 2; mid <= n - 3; ++mid) {
            for (int d1 = 0; d1 < 10; ++d1) {
                for (int d2 = 0; d2 < 10; ++d2) {
                    long long leftPairs = leftCount[mid][d1] * leftCount[mid][d2];
                    long long rightPairs = rightCount[mid][d1] * rightCount[mid][d2];
                    result = (result + leftPairs * rightPairs) % MOD;
                }
            }
        }

        return static_cast<int>(result);            
    }
};
