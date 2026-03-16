// Source: https://leetcode.com/problems/shortest-impossible-sequence-of-rolls/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array rolls of length n and an integer k. You roll a k sided dice numbered from 1 to k, n times, where the result of the ith roll is rolls[i].
//
// Return the length of the shortest sequence of rolls so that there's no such subsequence in rolls.
//
// A sequence of rolls of length len is the result of rolling a k sided dice len times.
//
// Example:
// Input: rolls = [4,2,1,2,3,3,2,4,1], k = 4
// Output: 3
// Explanation: Every sequence of rolls of length 1, [1], [2], [3], [4], can be taken from rolls.
// Every sequence of rolls of length 2, [1, 1], [1, 2], ..., [4, 4], can be taken from rolls.
// The sequence [1, 4, 2] cannot be taken from rolls, so we return 3.
// Note that there are other sequences that cannot be taken from rolls.
//
// Constraints:
// n == rolls.length
// 	1 <= n <= 105
// 	1 <= rolls[i] <= k <= 105
//
// Helpful references (internal KB):
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Sparse Table (array, sparse-table, dp-2d)
//   • When to use: Use when you need to answer range queries, especially Range Minimum/Maximum Queries, on an immutable array very quickly. It is ideal for scenarios where the data does not change and query performance is critical.
//   • Idea: Sparse Table is a data structure that precomputes answers for all range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like Range Minimum/Maximum Queries on a static array, with O(N log N) precomputation.
//   • Invariants: st[k][i] holds the result for the segment starting at index i with length 2^k.; For any k > 0, st[k][i] combines the results of two adjacent segments of length 2^(k-1).
//   • Tips: Precompute log2 values to find the largest power of two in O(1).; Best suited for idempotent operations like minimum, maximum, or GCD.
//   • Pitfalls: Does not support array updates; any modification invalidates the structure.; Inefficient for non-idempotent operations like range sum or XOR in O(1).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int shortestSequence(int[] rolls, int k) {
        // The idea is to count how many complete sets of [1, 2, ..., k] we can find in rolls.
        // Each complete set corresponds to one sequence of length equal to the number of complete sets found + 1.
        // We can use a HashSet to track which numbers from 1 to k we have seen in the current set.

        Set<Integer> seen = new HashSet<>();
        int count = 0; // This will count how many complete sets we have found

        for (int roll : rolls) {
            seen.add(roll);
            if (seen.size() == k) { // We found a complete set
                count++;
                seen.clear(); // Start looking for the next set
            }
        }

        return count + 1; // The shortest impossible sequence length is one more than the number of complete sets found         
    }
}
