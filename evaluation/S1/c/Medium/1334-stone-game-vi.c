// Source: https://leetcode.com/problems/stone-game-vi/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob take turns playing a game, with Alice starting first.
//
// There are n stones in a pile. On each player's turn, they can remove a stone from the pile and receive points based on the stone's value. Alice and Bob may value the stones differently.
//
// You are given two integer arrays of length n, aliceValues and bobValues. Each aliceValues[i] and bobValues[i] represents how Alice and Bob, respectively, value the ith stone.
//
// The winner is the person with the most points after all the stones are chosen. If both players have the same amount of points, the game results in a draw. Both players will play optimally. Both players know the other's values.
//
// Determine the result of the game, and:
//
//
// 	If Alice wins, return 1.
// 	If Bob wins, return -1.
// 	If the game results in a draw, return 0.
//
// Example:
// Input: aliceValues = [1,3], bobValues = [2,1]
// Output: 1
// Explanation:
// If Alice takes stone 1 (0-indexed) first, Alice will receive 3 points.
// Bob can only choose stone 0, and will only receive 2 points.
// Alice wins.
//
// Constraints:
// n == aliceValues.length == bobValues.length
// 	1 <= n <= 105
// 	1 <= aliceValues[i], bobValues[i] <= 100
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
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int stoneGameVI(int* aliceValues, int aliceValuesSize, int* bobValues, int bobValuesSize) {
    int n = aliceValuesSize;
    int combinedValues[n][3];
    for (int i = 0; i < n; i++) {
        combinedValues[i][0] = aliceValues[i] + bobValues[i];
        combinedValues[i][1] = aliceValues[i];
        combinedValues[i][2] = bobValues[i];
    }

    // Sort stones by combined value in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (combinedValues[j][0] < combinedValues[j + 1][0]) {
                int temp0 = combinedValues[j][0];
                int temp1 = combinedValues[j][1];
                int temp2 = combinedValues[j][2];
                combinedValues[j][0] = combinedValues[j + 1][0];
                combinedValues[j][1] = combinedValues[j + 1][1];
                combinedValues[j][2] = combinedValues[j + 1][2];
                combinedValues[j + 1][0] = temp0;
                combinedValues[j + 1][1] = temp1;
                combinedValues[j + 1][2] = temp2;
            }
        }
    }

    int aliceScore = 0;
    int bobScore = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            aliceScore += combinedValues[i][1];
        } else {
            bobScore += combinedValues[i][2];
        }
    }

    if (aliceScore > bobScore) {
        return 1;
    } else if (aliceScore < bobScore) {
        return -1;
    } else {
        return 0;
    }       
}
