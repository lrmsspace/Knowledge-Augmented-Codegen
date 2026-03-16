// Source: https://leetcode.com/problems/maximize-the-profit-as-the-salesman/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the number of houses on a number line, numbered from 0 to n - 1.
//
// Additionally, you are given a 2D integer array offers where offers[i] = [starti, endi, goldi], indicating that ith buyer wants to buy all the houses from starti to endi for goldi amount of gold.
//
// As a salesman, your goal is to maximize your earnings by strategically selecting and selling houses to buyers.
//
// Return the maximum amount of gold you can earn.
//
// Note that different buyers can't buy the same house, and some houses may remain unsold.
//
// Example:
// Input: n = 5, offers = [[0,0,1],[0,2,2],[1,3,2]]
// Output: 3
// Explanation: There are 5 houses numbered from 0 to 4 and there are 3 purchase offers.
// We sell houses in the range [0,0] to 1st buyer for 1 gold and houses in the range [1,3] to 3rd buyer for 2 golds.
// It can be proven that 3 is the maximum amount of gold we can achieve.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= offers.length <= 105
// 	offers[i].length == 3
// 	0 <= starti <= endi <= n - 1
// 	1 <= goldi <= 103
//
// Helpful references (internal KB):
// - Introduction to Dynamic Programming (array, dp-1d)
//   • When to use: When a problem can be broken down into smaller, overlapping subproblems and an optimal solution to the larger problem can be constructed from optimal solutions to its subproblems. It's suitable for optimizing recursive solutions with repeated computations.
//   • Idea: Dynamic Programming (DP) solves complex problems by breaking them into simpler overlapping subproblems and storing the results to avoid redundant computations. It typically achieves polynomial time complexity, often O(N) or O(N^2) for 1D DP, by trading space for time.
//   • Invariants: dp[i] stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been correctly computed before dp[i] is calculated.
//   • Tips: Clearly define the DP state and its meaning.; Identify the base cases for the recurrence relation.
//   • Pitfalls: Incorrectly defining the DP state or recurrence relation.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maximizeTheProfit(int n, List<List<Integer>> offers) {
        // Sort offers by their end index
        offers.sort(Comparator.comparingInt(o -> o.get(1)));

        // DP array to store maximum profit up to each house
        int[] dp = new int[n];
        int offerIndex = 0;

        for (int house = 0; house < n; house++) {
            // Carry forward the maximum profit from the previous house
            if (house > 0) {
                dp[house] = dp[house - 1];
            }

            // Process all offers that end at the current house
            while (offerIndex < offers.size() && offers.get(offerIndex).get(1) == house) {
                List<Integer> offer = offers.get(offerIndex);
                int start = offer.get(0);
                int gold = offer.get(2);

                // Calculate profit if we accept this offer
                int profitIfAccepted = gold;
                if (start > 0) {
                    profitIfAccepted += dp[start - 1];
                }

                // Update dp for the current house
                dp[house] = Math.max(dp[house], profitIfAccepted);
                offerIndex++;
            }
        }

        return dp[n - 1];           
    }
}
