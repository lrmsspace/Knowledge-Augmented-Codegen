// Source: https://leetcode.com/problems/super-washing-machines/   |   Difficulty: Hard
//
// Problem Description:
// You have n super washing machines on a line. Initially, each washing machine has some dresses or is empty.
//
// For each move, you could choose any m (1 <= m <= n) washing machines, and pass one dress of each washing machine to one of its adjacent washing machines at the same time.
//
// Given an integer array machines representing the number of dresses in each washing machine from left to right on the line, return the minimum number of moves to make all the washing machines have the same number of dresses. If it is not possible to do it, return -1.
//
// Example:
// Input: machines = [1,0,5]
// Output: 3
// Explanation:
// 1st move:    1     0 <-- 5    =>    1     1     4
// 2nd move:    1 <-- 1 <-- 4    =>    2     1     3
// 3rd move:    2     1 <-- 3    =>    2     2     2
//
// Constraints:
// n == machines.length
// 	1 <= n <= 104
// 	0 <= machines[i] <= 105
//
// Helpful references (internal KB):
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Range Minimum Query (array, sparse-table)
//   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
//   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
//   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
//   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
//   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
// - Finding a negative cycle in the graph (graph, matrix, floyd-warshall)
//   • When to use: Use when you need to find if a negative cycle exists in a graph, especially when dealing with all-pairs shortest paths or when edge weights can be negative. It is suitable for dense graphs.
//   • Idea: The Floyd-Warshall algorithm can detect negative cycles by checking if any vertex has a negative distance to itself after all iterations. It computes all-pairs shortest paths in O(V^3) time.
//   • Invariants: After k iterations, dist[i][j] stores the shortest path from i to j using only intermediate vertices from 0 to k-1.; For any i, dist[i][i] remains 0 unless a negative cycle involving i is found.
//   • Tips: Initialize distance matrix with edge weights or infinity for non-existent edges.; Set dist[i][i] to 0 for all i initially.
//   • Pitfalls: Incorrect initialization of the distance matrix, especially dist[i][i].; Forgetting to check the main diagonal for negative values after computation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findMinMoves(int* machines, int machinesSize) {
    int total = 0;
    for (int i = 0; i < machinesSize; ++i) {
        total += machines[i];
    }
    if (total % machinesSize != 0) {
        return -1; // Cannot balance if total dresses is not divisible by number of machines
    }
    
    int target = total / machinesSize;
    int maxMoves = 0;
    int cumulative = 0;
    
    for (int i = 0; i < machinesSize; ++i) {
        cumulative += machines[i] - target; // Cumulative excess or deficit
        int movesNeeded = abs(cumulative); // Moves needed to balance up to this point
        if (movesNeeded > maxMoves) {
            maxMoves = movesNeeded; // Update max moves needed
        }
    }
    
    return maxMoves;        
}
