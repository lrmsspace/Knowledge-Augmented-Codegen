// Source: https://leetcode.com/problems/minimum-levels-to-gain-more-points/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array possible of length n.
//
// Alice and Bob are playing a game that consists of n levels. Some of the levels in the game are impossible to clear while others can always be cleared. In particular, if possible[i] == 0, then the ith level is impossible to clear for both the players. A player gains 1 point on clearing a level and loses 1 point if the player fails to clear it.
//
// At the start of the game, Alice will play some levels in the given order starting from the 0th level, after which Bob will play for the rest of the levels.
//
// Alice wants to know the minimum number of levels she should play to gain more points than Bob, if both players play optimally to maximize their points.
//
// Return the minimum number of levels Alice should play to gain more points. If this is not possible, return -1.
//
// Note that each player must play at least 1 level.
//
// Example:
// Input: possible = [1,0,1,0]
//
// Output: 1
//
// Explanation:
//
// Let's look at all the levels that Alice can play up to:
//
//
// 	If Alice plays only level 0 and Bob plays the rest of the levels, Alice has 1 point, while Bob has -1 + 1 - 1 = -1 point.
// 	If Alice plays till level 1 and Bob plays the rest of the levels, Alice has 1 - 1 = 0 points, while Bob has 1 - 1 = 0 points.
// 	If Alice plays till level 2 and Bob plays the rest of the levels, Alice has 1 - 1 + 1 = 1 point, while Bob has -1 point.
//
//
// Alice must play a minimum of 1 level to gain more points.
//
// Constraints:
// 2 <= n == possible.length <= 105
// 	possible[i] is either 0 or 1.
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
//   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
//   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
//   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
//   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumLevels(int[] possible) {
        int n = possible.length;
        int alicePoints = 0, bobPoints = 0;

        // Calculate Bob's points if Alice plays all levels
        for (int i = 0; i < n; i++) {
            bobPoints += (possible[i] == 1) ? 1 : -1;
        }

        // If Bob already has more points than Alice, return -1
        if (bobPoints > 0) {
            return -1;
        }

        // Alice needs to play levels until she has more points than Bob
        for (int i = 0; i < n; i++) {
            alicePoints += (possible[i] == 1) ? 1 : -1;
            bobPoints -= (possible[i] == 1) ? 1 : -1;

            if (alicePoints > bobPoints) {
                return i + 1; // Return the number of levels Alice needs to play
            }
        }

        return -1; // If Alice cannot gain more points than Bob         
    }
}
