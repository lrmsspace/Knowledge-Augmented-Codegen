// Source: https://leetcode.com/problems/minimum-time-to-break-locks-i/   |   Difficulty: Medium
//
// Problem Description:
// Bob is stuck in a dungeon and must break n locks, each requiring some amount of energy to break. The required energy for each lock is stored in an array called strength where strength[i] indicates the energy needed to break the ith lock.
//
// To break a lock, Bob uses a sword with the following characteristics:
//
//
// 	The initial energy of the sword is 0.
// 	The initial factor x by which the energy of the sword increases is 1.
// 	Every minute, the energy of the sword increases by the current factor x.
// 	To break the ith lock, the energy of the sword must reach at least strength[i].
// 	After breaking a lock, the energy of the sword resets to 0, and the factor x increases by a given value k.
//
//
// Your task is to determine the minimum time in minutes required for Bob to break all n locks and escape the dungeon.
//
// Return the minimum time required for Bob to break all n locks.
//
// Example:
// Input: strength = [3,4,1], k = 1
//
// Output: 4
//
// Explanation:
//
//
// 	
// 		
// 			Time
// 			Energy
// 			x
// 			Action
// 			Updated x
// 		
// 		
// 			0
// 			0
// 			1
// 			Nothing
// 			1
// 		
// 		
// 			1
// 			1
// 			1
// 			Break 3rd Lock
// 			2
// 		
// 		
// 			2
// 			2
// 			2
// 			Nothing
// 			2
// 		
// 		
// 			3
// 			4
// 			2
// 			Break 2nd Lock
// 			3
// 		
// 		
// 			4
// 			3
// 			3
// 			Break 1st Lock
// 			3
// 		
// 	
//
//
// The locks cannot be broken in less than 4 minutes; thus, the answer is 4.
//
// Constraints:
// n == strength.length
// 	1 <= n <= 8
// 	1 <= K <= 10
// 	1 <= strength[i] <= 106
//
// Helpful references (internal KB):
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Continued fractions (number, array, enumeration)
//   • When to use: Use when representing real numbers as a sequence of integers for rational approximation, or when analyzing properties of irrational numbers. It's also useful for solving certain Diophantine equations and Pell's equation.
//   • Idea: Continued fractions represent a real number as a sum of an integer and the reciprocal of another number, which is then represented in the same way. This process generates a sequence of integers, and its complexity depends on the desired precision or the number's nature.
//   • Invariants: The current integer term `a_i` is `floor(x_i)`, where `x_i` is the current real value being expanded.; The next real value `x_{i+1}` is `1 / (x_i - a_i)` if `x_i - a_i` is non-zero.
//   • Tips: Understand the recursive definition of continued fractions.; The Euclidean algorithm forms the basis for computing finite continued fractions.
//   • Pitfalls: Floating-point precision issues can severely limit accuracy for irrational numbers.; Misinterpreting convergents as exact values instead of approximations.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findMinimumTime(vector<int>& strength, int k) {
        int n = strength.size();
        vector<int> dp(1 << n, 1e9);
        dp[0] = 0;

        for (int mask = 0; mask < (1 << n); mask++) {
            int x = 1;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    x += k;
                }
            }

            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) {
                    int energy_needed = strength[i];
                    int time_needed = (energy_needed + x - 1) / x; // ceil(energy_needed / x)
                    dp[mask | (1 << i)] = min(dp[mask | (1 << i)], dp[mask] + time_needed);
                }
            }
        }

        return dp[(1 << n) - 1];            
    }
};
