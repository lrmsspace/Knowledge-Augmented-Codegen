// Source: https://leetcode.com/problems/find-the-original-typed-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
//
// You are given a string word, which represents the final output displayed on Alice's screen. You are also given a positive integer k.
//
// Return the total number of possible original strings that Alice might have intended to type, if she was trying to type a string of size at least k.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: word = "aabbccdd", k = 7
//
// Output: 5
//
// Explanation:
//
// The possible strings are: "aabbccdd", "aabbccd", "aabbcdd", "aabccdd", and "abbccdd".
//
// Constraints:
// 1 <= word.length <= 5 * 105
//  word consists only of lowercase English letters.
//  1 <= k <= 2000
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private long modInverse(long a, int MOD) {
        long m0 = MOD, t, q;
        long x0 = 0, x1 = 1;

        if (MOD == 1) return 0;

        while (a > 1) {
            q = a / MOD;
            t = MOD;

            MOD = (int)(a % MOD);
            a = t;
            t = x0;

            x0 = x1 - q * x0;
            x1 = t;
        }

        if (x1 < 0) x1 += m0;

        return x1;
    }
    private long combination(int n, int k, int MOD) {
        if (k > n) return 0;
        long numerator = 1;
        long denominator = 1;
        for (int i = 0; i < k; i++) {
            numerator = (numerator * (n - i)) % MOD;
            denominator = (denominator * (i + 1)) % MOD;
        }
        return (numerator * modInverse(denominator, MOD)) % MOD;
    }
    public int possibleStringCount(String word, int k) {
        final int MOD = 1_000_000_007;
        int n = word.length();
        long result = 0;

        int count = 1;
        for (int i = 1; i <= n; i++) {
            if (i < n && word.charAt(i) == word.charAt(i - 1)) {
                count++;
            } else {
                // For a block of identical characters of length 'count',
                // we can choose to keep between 1 and 'count' characters.
                // We need to consider only those choices that keep the total
                // length of the string >= k.
                for (int take = 1; take <= count; take++) {
                    if (n - (count - take) >= k) {
                        result = (result + combination(count, take, MOD)) % MOD;
                    }
                }
                count = 1;
            }
        }

        return (int) result;            
    }
}
