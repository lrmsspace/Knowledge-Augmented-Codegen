// Source: https://leetcode.com/problems/count-the-number-of-inversions/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and a 2D array requirements, where requirements[i] = [endi, cnti] represents the end index and the inversion count of each requirement.
//
// A pair of indices (i, j) from an integer array nums is called an inversion if:
//
//
// 	i < j and nums[i] > nums[j]
//
//
// Return the number of permutations perm of [0, 1, 2, ..., n - 1] such that for all requirements[i], perm[0..endi] has exactly cnti inversions.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, requirements = [[2,2],[0,0]]
//
// Output: 2
//
// Explanation:
//
// The two permutations are:
//
//
// 	[2, 0, 1]
//
// 	
// 		Prefix [2, 0, 1] has inversions (0, 1) and (0, 2).
// 		Prefix [2] has 0 inversions.
// 	
// 	
// 	[1, 2, 0]
// 	
// 		Prefix [1, 2, 0] has inversions (0, 2) and (1, 2).
// 		Prefix [1] has 0 inversions.
//
// Constraints:
// 2 <= n <= 300
// 	1 <= requirements.length <= n
// 	requirements[i] = [endi, cnti]
// 	0 <= endi <= n - 1
// 	0 <= cnti <= 400
// 	The input is generated such that there is at least one i such that endi == n - 1.
// 	The input is generated such that all endi are unique.
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
            const int MOD = 1000000007;
            vector<vector<int>> dp(n, vector<int>(n * (n - 1) / 2 + 1, 0));
            dp[0][0] = 1;
            for (int i = 1; i < n; ++i) {
                for (int j = 0; j <= i * (i - 1) / 2; ++j) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
                    if (j >= i) {
                        dp[i][j] = (dp[i][j] + dp[i][j - i]) % MOD;
                    }
                }
            }
            unordered_map<int, int> reqMap;
            for (const auto& req : requirements) {
                reqMap[req[0]] = req[1];
            }
            long long result = 0;
            for (int j = 0; j <= n * (n - 1) / 2; ++j) {
                if (reqMap.count(n - 1) == 0 || reqMap[n - 1] == j) {
                    result = (result + dp[n - 1][j]) % MOD;
                }
            }
            return result;
    }
};
