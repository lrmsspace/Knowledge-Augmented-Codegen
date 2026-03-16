// Source: https://leetcode.com/problems/distribute-repeating-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities, quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:
//
//
// 	The ith customer gets exactly quantity[i] integers,
// 	The integers the ith customer gets are all equal, and
// 	Every customer is satisfied.
//
//
// Return true if it is possible to distribute nums according to the above conditions.
//
// Example:
// Input: nums = [1,2,3,4], quantity = [2]
// Output: false
// Explanation: The 0th customer cannot be given two different integers.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i] <= 1000
// 	m == quantity.length
// 	1 <= m <= 10
// 	1 <= quantity[i] <= 105
// 	There are at most 50 unique values in nums.
//
// Helpful references (internal KB):
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        vector<int> counts;
        for (const auto& entry : freq) {
            counts.push_back(entry.second);
        }

        int m = quantity.size();
        int totalStates = 1 << m;
        vector<int> subsetSums(totalStates, 0);
        for (int state = 1; state < totalStates; ++state) {
            int lastBit = state & -state;
            int prevState = state - lastBit;
            int idx = __builtin_ctz(lastBit);
            subsetSums[state] = subsetSums[prevState] + quantity[idx];
        }

        vector<bool> dp(totalStates, false);
        dp[0] = true;

        for (int count : counts) {
            vector<bool> nextDp = dp;
            for (int state = 0; state < totalStates; ++state) {
                if (!dp[state]) continue;
                int remaining = ((1 << m) - 1) ^ state;
                for (int subState = remaining; subState > 0; subState = (subState - 1) & remaining) {
                    if (subsetSums[subState] <= count) {
                        nextDp[state | subState] = true;
                    }
                }
            }
            dp = move(nextDp);
        }

        return dp[totalStates - 1];         
    }
};
