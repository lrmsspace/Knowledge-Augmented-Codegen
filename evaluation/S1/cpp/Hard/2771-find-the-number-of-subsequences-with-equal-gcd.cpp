// Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums.
//
// Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
//
//
// 	The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
// 	The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
//
//
// Return the total number of such pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 10
//
// Explanation:
//
// The subsequence pairs which have the GCD of their elements equal to 1 are:
//
//
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 200
//
// Helpful references (internal KB):
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        const int MAX_N = 200;
        
        // Precompute gcd
        int gcdTable[MAX_N + 1][MAX_N + 1];
        for (int i = 1; i <= MAX_N; ++i) {
            for (int j = 1; j <= MAX_N; ++j) {
                gcdTable[i][j] = std::__gcd(i, j);
            }
        }
        
        // Count frequency of each number
        int freq[MAX_N + 1] = {0};
        for (int num : nums) {
            freq[num]++;
        }
        
        // DP table: dp[g][k] = number of subsequences with GCD g and length k
        long long dp[MAX_N + 1][nums.size() + 1] = {0};
        
        // Fill DP table
        for (int g = MAX_N; g >= 1; --g) {
            long long totalSubseq = 1; // empty subsequence
            for (int multiple = g; multiple <= MAX_N; multiple += g) {
                if (freq[multiple] > 0) {
                    long long ways = (pow(2, freq[multiple], MOD) - 1 + MOD) % MOD;
                    totalSubseq = (totalSubseq * (ways + 1)) % MOD;
                }
            }
            totalSubseq = (totalSubseq - 1 + MOD) % MOD; // exclude empty subsequence
            
            dp[g][0] = 1; // empty subsequence
            
            for (int k = 1; k <= nums.size(); ++k) {
                dp[g][k] = totalSubseq;
                for (int multiple = 2 * g; multiple <= MAX_N; multiple += g) {
                    dp[g][k] = (dp[g][k] - dp[multiple][k] + MOD) % MOD;
                }
            }
        }
        
        // Calculate result
        long long result = 0;
        for (int g = 1; g <= MAX_N; ++g) {
            for (int k = 1; k <= nums.size(); ++k) {
                result = (result + (dp[g][k] * dp[g][k]) % MOD) % MOD;
            }
        }
        return static_cast<int>(result);
    }
};
