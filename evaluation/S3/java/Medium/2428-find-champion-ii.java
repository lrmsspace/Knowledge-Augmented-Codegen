// Source: https://leetcode.com/problems/find-champion-ii/   |   Difficulty: Medium
//
// Problem Description:
// There are n teams numbered from 0 to n - 1 in a tournament; each team is also a node in a DAG.
//
// You are given the integer n and a 0-indexed 2D integer array edges of length m representing the DAG, where edges[i] = [ui, vi] indicates that there is a directed edge from team ui to team vi in the graph.
//
// A directed edge from a to b in the graph means that team a is stronger than team b and team b is weaker than team a.
//
// Team a will be the champion of the tournament if there is no team b that is stronger than team a.
//
// Return the team that will be the champion of the tournament if there is a unique champion, otherwise, return -1.
//
// Notes
//
//
// 	A cycle is a series of nodes a1, a2, ..., an, an+1 such that node a1 is the same node as node an+1, the nodes a1, a2, ..., an are distinct, and there is a directed edge from the node ai to node ai+1 for every i in the range [1, n].
// 	A DAG is a directed graph that does not have any cycle.
//
// Example:
// Input: n = 3, edges = [[0,1],[1,2]]
// Output: 0
// Explanation: Team 1 is weaker than team 0. Team 2 is weaker than team 1. So the champion is team 0.
//
// Constraints:
// 1 <= n <= 100
// 	m == edges.length
// 	0 <= m <= n * (n - 1) / 2
// 	edges[i].length == 2
// 	0 <= edge[i][j] <= n - 1
// 	edges[i][0] != edges[i][1]
// 	The input is generated such that if team a is stronger than team b, team b is not stronger than team a.
// 	The input is generated such that if team a is stronger than team b and team b is stronger than team c, then team a is stronger than team c.
//
// Helpful references (internal KB):
// - Directed Graphs (graph, array, dfs, bfs)
//   • When to use: Use when modeling relationships with a specific flow direction between entities. It is ideal for determining reachability or finding paths from one or more sources.
//   • Idea: Directed graphs represent connections where edges have a specific direction, often implemented using adjacency lists. Depth-first search (DFS) and breadth-first search (BFS) are fundamental algorithms for traversing these graphs to find paths and determine reachability in O(V+E) time.
//   • Invariants: The 'visited' set accurately reflects all nodes for which traversal has been initiated.; For DFS, all nodes reachable from the current node via unvisited paths will eventually be explored.
//   • Tips: Always use a 'visited' set or array to prevent infinite loops in cycles and redundant processing.; Adjacency list representation is generally preferred for sparse graphs due to better space and time complexity for traversal.
//   • Pitfalls: Forgetting to handle cycles can lead to infinite loops or stack overflows in DFS.; Incorrectly applying algorithms designed for undirected graphs to directed graphs without modification.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int findChampion(int n, int[][] edges) {
        // Create an adjacency list to represent the graph
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
        }

        // Check for each team if it can be the champion
        int champion = -1;
        for (int i = 0; i < n; i++) {
            if (isChampion(graph, i, new boolean[n])) {
                if (champion != -1) {
                    return -1; // More than one champion found
                }
                champion = i;
            }
        }
        return champion;            
    }
}
