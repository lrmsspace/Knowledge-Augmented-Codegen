// Source: https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/   |   Difficulty: Hard
//
// Problem Description:
// A company is organizing a meeting and has a list of n employees, waiting to be invited. They have arranged for a large circular table, capable of seating any number of employees.
//
// The employees are numbered from 0 to n - 1. Each employee has a favorite person and they will attend the meeting only if they can sit next to their favorite person at the table. The favorite person of an employee is not themself.
//
// Given a 0-indexed integer array favorite, where favorite[i] denotes the favorite person of the ith employee, return the maximum number of employees that can be invited to the meeting.
//
// Example:
// Input: favorite = [2,2,1,2]
// Output: 3
// Explanation:
// The above figure shows how the company can invite employees 0, 1, and 2, and seat them at the round table.
// All employees cannot be invited because employee 2 cannot sit beside employees 0, 1, and 3, simultaneously.
// Note that the company can also invite employees 1, 2, and 3, and give them their desired seats.
// The maximum number of employees that can be invited to the meeting is 3.
//
// Constraints:
// n == favorite.length
// 	2 <= n <= 105
// 	0 <= favorite[i] <= n - 1
// 	favorite[i] != i
//
// Helpful references (internal KB):
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
//   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
//   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
//   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
//   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumInvitations(int* favorite, int favoriteSize) {
    // This problem can be solved by analyzing the structure of the graph formed by the favorite relationships.
    // We need to find the longest cycle in the graph and also consider pairs of employees who are mutual favorites.
    
    int n = favoriteSize;
    int* visited = (int*)calloc(n, sizeof(int));
    int* depth = (int*)calloc(n, sizeof(int));
    int maxCycleLength = 0;
    int mutualPairs = 0;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int current = i;
            int currentDepth = 0;
            while (!visited[current]) {
                visited[current] = 1;
                depth[current] = currentDepth++;
                current = favorite[current];
            }
            if (current == i) {
                maxCycleLength = max(maxCycleLength, currentDepth);
            } else {
                int cycleLength = currentDepth - depth[current];
                maxCycleLength = max(maxCycleLength, cycleLength);
            }
        }
    }
    
    // Check for mutual pairs
    for (int i = 0; i < n; i++) {
        if (favorite[favorite[i]] == i) {
            mutualPairs += 2; // Each pair contributes 2 employees
        }
    }
    
    free(visited);
    free(depth);
    
    return max(maxCycleLength, mutualPairs);        
}
