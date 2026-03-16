// Source: https://leetcode.com/problems/push-dominoes/   |   Difficulty: Medium
//
// Problem Description:
// There are n dominoes in a line, and we place each domino vertically upright. In the beginning, we simultaneously push some of the dominoes either to the left or to the right.
//
// After each second, each domino that is falling to the left pushes the adjacent domino on the left. Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.
//
// When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.
//
// For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.
//
// You are given a string dominoes representing the initial state where:
//
//
// 	dominoes[i] = 'L', if the ith domino has been pushed to the left,
// 	dominoes[i] = 'R', if the ith domino has been pushed to the right, and
// 	dominoes[i] = '.', if the ith domino has not been pushed.
//
//
// Return a string representing the final state.
//
// Example:
// Input: dominoes = "RR.L"
// Output: "RR.L"
// Explanation: The first domino expends no additional force on the second domino.
//
// Constraints:
// n == dominoes.length
// 	1 <= n <= 105
// 	dominoes[i] is either 'L', 'R', or '.'.
//
// Helpful references (internal KB):
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();
        string result = dominoes;
        int leftForce = 0;
        for (int i = 0; i < n; ++i) {
            if (dominoes[i] == 'R') {
                leftForce = n; // Assign a large force
            } else if (dominoes[i] == 'L') {
                leftForce = 0; // Reset force
            } else {
                leftForce = max(leftForce - 1, 0); // Decrease force over distance
            }
            result[i] += leftForce;
        }

        int rightForce = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (dominoes[i] == 'L') {
                rightForce = n; // Assign a large force
            } else if (dominoes[i] == 'R') {
                rightForce = 0; // Reset force
            } else {
                rightForce = max(rightForce - 1, 0); // Decrease force over distance
            }
            result[i] -= rightForce;
        }

        for (int i = 0; i < n; ++i) {
            if (result[i] > '0') {
                result[i] = 'R';
            } else if (result[i] < '0') {
                result[i] = 'L';
            } else {
                result[i] = '.';
            }
        }

        return result;          
    }
};
