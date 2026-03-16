// Source: https://leetcode.com/problems/number-of-ways-to-earn-points/   |   Difficulty: Hard
//
// Problem Description:
// There is a test that has n types of questions. You are given an integer target and a 0-indexed 2D integer array types where types[i] = [counti, marksi] indicates that there are counti questions of the ith type, and each one of them is worth marksi points.
//
//
//
//
// Return the number of ways you can earn exactly target points in the exam. Since the answer may be too large, return it modulo 109 + 7.
//
// Note that questions of the same type are indistinguishable.
//
//
// 	For example, if there are 3 questions of the same type, then solving the 1st and 2nd questions is the same as solving the 1st and 3rd questions, or the 2nd and 3rd questions.
//
// Example:
// Input: target = 6, types = [[6,1],[3,2],[2,3]]
// Output: 7
// Explanation: You can earn 6 points in one of the seven ways:
// - Solve 6 questions of the 0th type: 1 + 1 + 1 + 1 + 1 + 1 = 6
// - Solve 4 questions of the 0th type and 1 question of the 1st type: 1 + 1 + 1 + 1 + 2 = 6
// - Solve 2 questions of the 0th type and 2 questions of the 1st type: 1 + 1 + 2 + 2 = 6
// - Solve 3 questions of the 0th type and 1 question of the 2nd type: 1 + 1 + 1 + 3 = 6
// - Solve 1 question of the 0th type, 1 question of the 1st type and 1 question of the 2nd type: 1 + 2 + 3 = 6
// - Solve 3 questions of the 1st type: 2 + 2 + 2 = 6
// - Solve 2 questions of the 2nd type: 3 + 3 = 6
//
// Constraints:
// 1 <= target <= 1000
// 	n == types.length
// 	1 <= n <= 50
// 	types[i].length == 2
// 	1 <= counti, marksi <= 50
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Binomial Coefficients (array, number, dp-1d, mod-exp)
//   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
//   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
//   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
//   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
//   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int waysToReachTarget(int target, int[][] types) {
        int mod = (int) 1e9 + 7;
        int n = types.length;
        int[] dp = new int[target + 1];
        dp[0] = 1;

        for (int i = 0; i < n; i++) {
            int count = types[i][0];
            int marks = types[i][1];

            // We will use a monotonic queue to optimize the transition for the current type of questions
            for (int r = 0; r < marks; r++) {
                Deque<Integer> deque = new ArrayDeque<>();
                for (int c = r; c <= target; c += marks) {
                    // Remove indices from the front of the deque that are out of the window of size count
                    while (!deque.isEmpty() && deque.peekFirst() < c - count * marks) {
                        deque.pollFirst();
                    }

                    // Add the current index to the deque while maintaining the decreasing order of dp values
                    while (!deque.isEmpty() && dp[deque.peekLast()] <= dp[c]) {
                        deque.pollLast();
                    }
                    deque.offerLast(c);

                    // The maximum value for dp[c] is now at the front of the deque
                    dp[c] = (dp[c] + dp[deque.peekFirst()]) % mod;
                }
            }
        }

        return dp[target];          
    }
}
