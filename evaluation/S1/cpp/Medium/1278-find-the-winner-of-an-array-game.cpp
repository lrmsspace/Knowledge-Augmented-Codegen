// Source: https://leetcode.com/problems/find-the-winner-of-an-array-game/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr of distinct integers and an integer k.
//
// A game will be played between the first two elements of the array (i.e. arr[0] and arr[1]). In each round of the game, we compare arr[0] with arr[1], the larger integer wins and remains at position 0, and the smaller integer moves to the end of the array. The game ends when an integer wins k consecutive rounds.
//
// Return the integer which will win the game.
//
// It is guaranteed that there will be a winner of the game.
//
// Example:
// Input: arr = [2,1,3,5,4,6,7], k = 2
// Output: 5
// Explanation: Let's see the rounds of the game:
// Round |       arr       | winner | win_count
//   1   | [2,1,3,5,4,6,7] | 2      | 1
//   2   | [2,3,5,4,6,7,1] | 3      | 1
//   3   | [3,5,4,6,7,1,2] | 5      | 1
//   4   | [5,4,6,7,1,2,3] | 5      | 2
// So we can see that 4 rounds will be played and 5 is the winner because it wins 2 consecutive games.
//
// Constraints:
// 2 <= arr.length <= 105
// 	1 <= arr[i] <= 106
// 	arr contains distinct integers.
// 	1 <= k <= 109
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
    int getWinner(vector<int>& arr, int k) {
        int n = arr.size();
        int winner = arr[0];
        if (k >= n - 1) {
            // If k is large enough, the maximum element will eventually win
            for (int i = 1; i < n; ++i) {
                if (arr[i] > winner) {
                    winner = arr[i];
                }
            }
            return winner;
        }

        int winCount = 0;
        for (int i = 1; i < n; ++i) {
            if (winner > arr[i]) {
                winCount++;
            } else {
                winner = arr[i];
                winCount = 1;
            }
            if (winCount == k) {
                return winner;
            }
        }
        return winner;          
    }
};
