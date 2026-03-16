// Source: https://leetcode.com/problems/maximum-score-of-a-node-sequence/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph with n nodes, numbered from 0 to n - 1.
//
// You are given a 0-indexed integer array scores of length n where scores[i] denotes the score of node i. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A node sequence is valid if it meets the following conditions:
//
//
// 	There is an edge connecting every pair of adjacent nodes in the sequence.
// 	No node appears more than once in the sequence.
//
//
// The score of a node sequence is defined as the sum of the scores of the nodes in the sequence.
//
// Return the maximum score of a valid node sequence with a length of 4. If no such sequence exists, return -1.
//
// Example:
// Input: scores = [5,2,9,8,4], edges = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
// Output: 24
// Explanation: The figure above shows the graph and the chosen node sequence [0,1,2,3].
// The score of the node sequence is 5 + 2 + 9 + 8 = 24.
// It can be shown that no other node sequence has a score of more than 24.
// Note that the sequences [3,1,2,0] and [1,0,2,3] are also valid and have a score of 24.
// The sequence [0,3,2,4] is not valid since no edge connects nodes 0 and 3.
//
// Constraints:
// n == scores.length
// 	4 <= n <= 5 * 104
// 	1 <= scores[i] <= 108
// 	0 <= edges.length <= 5 * 104
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no duplicate edges.
//
// Helpful references (internal KB):
// - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
//   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
//   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
//   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
//   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
//   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Kuhn's Algorithm for Maximum Bipartite Matching (graph, array, greedy, dfs)
//   • When to use: Use when finding a maximum matching in a bipartite graph, particularly when performance on random graphs can be improved by heuristic pre-matching.
//   • Idea: This algorithm finds a maximum matching in a bipartite graph by iteratively searching for augmenting paths using Depth-First Search. An improved version incorporates greedy heuristics to find an initial matching, potentially speeding up practical runtime while maintaining the O(V*E) worst-case complexity.
//   • Invariants: After each successful DFS call, the size of the current matching increases by one.; The 'mt' array correctly stores the current matching pairs for all vertices.
//   • Tips: Pre-calculate an initial matching using a simple heuristic to reduce DFS calls.; Consider heuristics like iterating over vertices or selecting from smallest degree vertices first.
//   • Pitfalls: Forgetting to reset the 'visited' array for each new DFS search in the main loop.; Incorrectly modifying the main loop logic when integrating heuristic pre-matching.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maximumScore(int[] scores, int[][] edges) {
        int n = scores.length;
        List<Integer>[] graph = new List[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }
        for (int[] edge : edges) {
            graph[edge[0]].add(edge[1]);
            graph[edge[1]].add(edge[0]);
        }

        // For each node, keep the top 3 neighbors with the highest scores
        List<Integer>[] topNeighbors = new List[n];
        for (int i = 0; i < n; i++) {
            PriorityQueue<Integer> pq = new PriorityQueue<>((a, b) -> scores[a] - scores[b]);
            for (int neighbor : graph[i]) {
                pq.offer(neighbor);
                if (pq.size() > 3) {
                    pq.poll();
                }
            }
            topNeighbors[i] = new ArrayList<>(pq);
        }

        int maxScore = -1;
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            for (int a : topNeighbors[u]) {
                if (a == v) continue; // Skip if it's the same node
                for (int b : topNeighbors[v]) {
                    if (b == u || b == a) continue; // Skip if it's the same node
                    maxScore = Math.max(maxScore, scores[u] + scores[v] + scores[a] + scores[b]);
                }
            }
        }

        return maxScore;            
    }
}
