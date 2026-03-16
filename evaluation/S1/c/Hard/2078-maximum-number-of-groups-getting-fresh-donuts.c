// Source: https://leetcode.com/problems/maximum-number-of-groups-getting-fresh-donuts/   |   Difficulty: Hard
//
// Problem Description:
// There is a donuts shop that bakes donuts in batches of batchSize. They have a rule where they must serve all of the donuts of a batch before serving any donuts of the next batch. You are given an integer batchSize and an integer array groups, where groups[i] denotes that there is a group of groups[i] customers that will visit the shop. Each customer will get exactly one donut.
//
// When a group visits the shop, all customers of the group must be served before serving any of the following groups. A group will be happy if they all get fresh donuts. That is, the first customer of the group does not receive a donut that was left over from the previous group.
//
// You can freely rearrange the ordering of the groups. Return the maximum possible number of happy groups after rearranging the groups.
//
// Example:
// Input: batchSize = 3, groups = [1,2,3,4,5,6]
// Output: 4
// Explanation: You can arrange the groups as [6,2,4,5,1,3]. Then the 1st, 2nd, 4th, and 6th groups will be happy.
//
// Constraints:
// 1 <= batchSize <= 9
// 	1 <= groups.length <= 30
// 	1 <= groups[i] <= 109
//
// Helpful references (internal KB):
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxHappyGroups(int batchSize, int* groups, int groupsSize) {
    int remainderCount[9] = {0}; // since batchSize <= 9
    int happyGroups = 0;

    // Count groups that are already happy and count remainders
    for (int i = 0; i < groupsSize; i++) {
        int rem = groups[i] % batchSize;
        if (rem == 0) {
            happyGroups++;
        } else {
            remainderCount[rem]++;
        }
    }

    // DP state: bitmask representing counts of remainders
    int memo[1 << (batchSize * 3)]; // each remainder can be from 0 to 2 (3 bits)
    for (int i = 0; i < (1 << (batchSize * 3)); i++) {
        memo[i] = -1;
    }

    // Helper function for DFS with memoization
    int dfs(int state, int currentRem) {
        if (memo[state] != -1) {
            return memo[state];
        }

        int maxHappy = 0;
        for (int r = 1; r < batchSize; r++) {
            int count = (state >> (r * 3)) & 0x7; // get count of remainder r
            if (count > 0) {
                int newState = state - (1 << (r * 3));
                int newRem = (currentRem + r) % batchSize;
                int addHappy = (newRem == 0) ? 1 : 0;
                maxHappy = fmax(maxHappy, dfs(newState, newRem) + addHappy);
            }
        }

        memo[state] = maxHappy;
        return maxHappy;
    }

    // Construct initial state
    int initialState = 0;
    for (int r = 1; r < batchSize; r++) {
        initialState |= (remainderCount[r] << (r * 3));
    }

    happyGroups += dfs(initialState, 0);
    return happyGroups;     
}
