// Source: https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n, you can do the following operation any number of times:
//
//
// 	Add or subtract a power of 2 from n.
//
//
// Return the minimum number of operations to make n equal to 0.
//
// A number x is power of 2 if x == 2i where i >= 0.
//
// Example:
// Input: n = 39
// Output: 3
// Explanation: We can do the following operations:
// - Add 20 = 1 to n, so now n = 40.
// - Subtract 23 = 8 from n, so now n = 32.
// - Subtract 25 = 32 from n, so now n = 0.
// It can be shown that 3 is the minimum number of operations we need to make n equal to 0.
//
// Constraints:
// 1 <= n <= 105
//
// Helpful references (internal KB):
// - Breadth-first search (graph, deque, array, 01-bfs)
//   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
//   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
//   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
//   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
//   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minOperations(int n) {
    int count = 0;
    while (n > 0) {
        if ((n & 1) == 0) {
            n >>= 1; // If n is even, divide by 2 (shift right)
        } else {
            if ((n & 2) == 0 || n == 1) {
                n -= 1; // If n is odd and the next bit is not set, subtract 1
            } else {
                n += 1; // If n is odd and the next bit is set, add 1
            }
        }
        count++; // Increment the operation count
    }
    return count;       
}
