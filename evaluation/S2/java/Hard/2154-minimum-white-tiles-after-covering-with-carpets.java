// Source: https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed binary string floor, which represents the colors of tiles on a floor:
//
//
// 	floor[i] = '0' denotes that the ith tile of the floor is colored black.
// 	On the other hand, floor[i] = '1' denotes that the ith tile of the floor is colored white.
//
//
// You are also given numCarpets and carpetLen. You have numCarpets black carpets, each of length carpetLen tiles. Cover the tiles with the given carpets such that the number of white tiles still visible is minimum. Carpets may overlap one another.
//
// Return the minimum number of white tiles still visible.
//
// Example:
// Input: floor = "10110101", numCarpets = 2, carpetLen = 2
// Output: 2
// Explanation: 
// The figure above shows one way of covering the tiles with the carpets such that only 2 white tiles are visible.
// No other way of covering the tiles with the carpets can leave less than 2 white tiles visible.
//
// Constraints:
// 1 <= carpetLen <= floor.length <= 1000
// 	floor[i] is either '0' or '1'.
// 	1 <= numCarpets <= 1000
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Rabin-Karp Algorithm for string matching (string, number, hashing, rolling-hash)
//   • When to use: To efficiently find all occurrences of a given pattern string within a larger text string, especially when multiple patterns might be searched or for average-case linear time performance.
//   • Idea: The Rabin-Karp algorithm finds occurrences of a pattern in a text by comparing their hash values, using a rolling hash function to efficiently update substring hashes. It achieves an average time complexity of O(|s| + |t|) and a worst-case of O(|s| * |t|).
//   • Invariants: The hash of the pattern string remains constant throughout the search.; The current window's hash value accurately represents the substring T[i...i+len(P)-1].
//   • Tips: Choose a large prime modulus to minimize hash collisions.; Select a suitable base (e.g., a prime greater than alphabet size) for polynomial hashing.
//   • Pitfalls: Hash collisions can lead to false positives and degrade worst-case performance to O(MN).; Poor choice of base or modulus can significantly increase collision frequency.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumWhiteTiles(String floor, int numCarpets, int carpetLen) {
        int n = floor.length();
        int[] prefixSum = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + (floor.charAt(i) - '0');
        }

        int[][] dp = new int[numCarpets + 1][n + 1];
        for (int i = 0; i <= numCarpets; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0) {
                    dp[i][j] = prefixSum[j];
                } else if (j == 0) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = Math.min(dp[i][j - 1] + (floor.charAt(j - 1) - '0'), dp[i - 1][Math.max(0, j - carpetLen)]);
                }
            }
        }

        return dp[numCarpets][n];           
    }
}
