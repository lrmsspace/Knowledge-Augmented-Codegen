// Source: https://leetcode.com/problems/minimum-time-to-remove-all-cars-containing-illegal-goods/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed binary string s which represents a sequence of train cars. s[i] = '0' denotes that the ith car does not contain illegal goods and s[i] = '1' denotes that the ith car does contain illegal goods.
//
// As the train conductor, you would like to get rid of all the cars containing illegal goods. You can do any of the following three operations any number of times:
//
//
// 	Remove a train car from the left end (i.e., remove s[0]) which takes 1 unit of time.
// 	Remove a train car from the right end (i.e., remove s[s.length - 1]) which takes 1 unit of time.
// 	Remove a train car from anywhere in the sequence which takes 2 units of time.
//
//
// Return the minimum time to remove all the cars containing illegal goods.
//
// Note that an empty sequence of cars is considered to have no cars containing illegal goods.
//
// Example:
// Input: s = "1100101"
// Output: 5
// Explanation: 
// One way to remove all the cars containing illegal goods from the sequence is to
// - remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
// - remove a car from the right end. Time taken is 1.
// - remove the car containing illegal goods found in the middle. Time taken is 2.
// This obtains a total time of 2 + 1 + 2 = 5. 
//
// An alternative way is to
// - remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
// - remove a car from the right end 3 times. Time taken is 3 * 1 = 3.
// This also obtains a total time of 2 + 3 = 5.
//
// 5 is the minimum time taken to remove all the cars containing illegal goods. 
// There are no other ways to remove them with less time.
//
// Constraints:
// 1 <= s.length <= 2 * 105
// 	s[i] is either '0' or '1'.
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
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
    int minimumTime(string s) {
        int n = s.size();
        vector<int> dp(n + 1, 0); // dp[i]: min time to remove illegal goods from first i cars

        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] == '0') {
                dp[i] = dp[i - 1]; // No illegal goods, no extra time needed
            } else {
                // Option 1: Remove this car from the left end
                int option1 = dp[i - 1] + 1;
                // Option 2: Remove this car from the right end
                int option2 = i; // Removing all cars up to i from the left
                // Option 3: Remove this car from anywhere in the sequence
                int option3 = dp[i - 1] + 2;

                dp[i] = min({option1, option2, option3});
            }
        }

        return dp[n];           
    }
};
