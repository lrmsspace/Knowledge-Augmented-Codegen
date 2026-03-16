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
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Undirected Graphs (graph, matrix, simulation)
//   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
//   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
//   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
//   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
//   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
// - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
//   • When to use: Use when you need to find the Lowest Common Ancestor for multiple pairs of nodes in a tree, and all queries are known beforehand. It's an efficient offline approach for batch processing LCA queries.
//   • Idea: Tarjan's offline LCA algorithm uses a Depth-First Search (DFS) traversal combined with a Union-Find data structure to answer all LCA queries efficiently. It processes N nodes and Q queries in O(N + Q * alpha(N)) time, where alpha is the inverse Ackermann function.
//   • Invariants: After visiting a node 'u' and all its children, 'u' is marked as visited.; For any node 'v' whose subtree has been fully processed, 'find_set(v)' returns the representative of 'v''s component.
//   • Tips: Mark nodes as visited during DFS to track processed subtrees.; Use Union-Find's union operation to merge child subtrees with their parent after processing.
//   • Pitfalls: Forgetting to mark nodes as visited, leading to incorrect LCA identification.; Incorrectly updating the 'ancestor' array or 'find_set' logic in Union-Find.
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
        List<int[]>[] topNeighbors = new List[n];
        for (int i = 0; i < n; i++) {
            topNeighbors[i] = new ArrayList<>();
            for (int neighbor : graph[i]) {
                topNeighbors[i].add(new int[]{neighbor, scores[neighbor]});
            }
            topNeighbors[i].sort((a, b) -> Integer.compare(b[1], a[1]));
            if (topNeighbors[i].size() > 3) {
                topNeighbors[i] = topNeighbors[i].subList(0, 3);
            }
        }

        int maxScore = -1;
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            for (int[] neighborU : topNeighbors[u]) {
                for (int[] neighborV : topNeighbors[v]) {
                    if (neighborU[0] != v && neighborV[0] != u && neighborU[0] != neighborV[0]) {
                        int score = scores[u] + scores[v] + neighborU[1] + neighborV[1];
                        maxScore = Math.max(maxScore, score);
                    }
                }
            }
        }

        return maxScore;            
    }
}
