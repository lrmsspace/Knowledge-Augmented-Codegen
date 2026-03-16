// Source: https://leetcode.com/problems/longest-cycle-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.
//
// The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from node i to node edges[i]. If there is no outgoing edge from node i, then edges[i] == -1.
//
// Return the length of the longest cycle in the graph. If no cycle exists, return -1.
//
// A cycle is a path that starts and ends at the same node.
//
// Example:
// Input: edges = [3,3,4,2,3]
// Output: 3
// Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
// The length of this cycle is 3, so 3 is returned.
//
// Constraints:
// n == edges.length
// 	2 <= n <= 105
// 	-1 <= edges[i] < n
// 	edges[i] != i
//
// Helpful references (internal KB):
// - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
//   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
//   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
//   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
//   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Depth First Search (graph, dfs, scc, topo)
//   • When to use: Use DFS to systematically explore all reachable vertices from a starting point, identify graph components, or determine properties like cycles and topological orderings. It's suitable for problems requiring full graph traversal or tree-like structure analysis.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically runs in O(V + E) time for graphs represented with adjacency lists.
//   • Invariants: When a vertex 'u' is entered, it is marked as 'visiting' and its 'entry_time' is recorded.; When a vertex 'u' is exited, it is marked as 'visited' and its 'exit_time' is recorded.
//   • Tips: Use a 'visited' set or array to prevent infinite loops in cyclic graphs.; Recursion is natural for DFS, but an iterative approach with an explicit stack can prevent stack overflow.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect results.; Deep recursion can cause stack overflow errors on large graphs, necessitating an iterative approach.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int longestCycle(int[] edges) {
        int n = edges.length;
        boolean[] visited = new boolean[n];
        int longestCycleLength = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                longestCycleLength = Math.max(longestCycleLength, dfs(edges, visited, i));
            }
        }

        return longestCycleLength;          
    }
}
