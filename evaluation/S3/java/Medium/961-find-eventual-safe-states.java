// Source: https://leetcode.com/problems/find-eventual-safe-states/   |   Difficulty: Medium
//
// Problem Description:
// There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].
//
// A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).
//
// Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.
//
// Example:
// Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
// Output: [2,4,5,6]
// Explanation: The given graph is shown above.
// Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
// Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.
//
// Constraints:
// n == graph.length
// 	1 <= n <= 104
// 	0 <= graph[i].length <= n
// 	0 <= graph[i][j] <= n - 1
// 	graph[i] is sorted in a strictly increasing order.
// 	The graph may contain self-loops.
// 	The number of edges in the graph will be in the range [1, 4 * 104].
//
// Helpful references (internal KB):
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Depth-first search (graph, array, stack, dfs)
//   • When to use: Use DFS when you need to explore all reachable nodes from a starting point, find paths, detect cycles, or perform topological sorting in a graph. It is suitable for problems requiring deep exploration before backtracking.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs.
//   • Invariants: All nodes currently on the recursion stack (or explicit stack) are part of the current path from the source.; Once a node `v` is marked `visited`, it will not be processed again by the main traversal logic.
//   • Tips: Use a `visited` array or set to track explored nodes.; Pass the parent node in recursive calls to correctly detect cycles.
//   • Pitfalls: Risk of stack overflow for very deep graphs with recursive implementations.; Failure to use a `visited` array leads to infinite loops in cyclic graphs.
// - Topological Sorting (graph, array, dfs, topo)
//   • When to use: Use for graph or tree traversal, pathfinding, cycle detection, or topological sorting in DAGs. It's also suitable for exploring all states in a search space.
//   • Idea: DFS explores as far as possible along each branch before backtracking, typically using recursion or an explicit stack. Topological sort orders nodes in a DAG such that for every directed edge u -> v, u comes before v, achievable with DFS in O(V+E) time.
//   • Invariants: All nodes reachable from the current path have been explored or are in the recursion stack.; A node is marked 'visited' only after all its descendants have been fully explored.
//   • Tips: Use a visited set/array to prevent infinite loops in graphs and redundant computations.; Recursion is natural for DFS, but an explicit stack can avoid recursion depth limits.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect results.; Exceeding recursion depth limits for very deep graphs or trees.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> eventualSafeNodes(int[][] graph) {
        int n = graph.length;
        List<Integer> safeNodes = new ArrayList<>();
        int[] state = new int[n]; // 0: unvisited, 1: visiting, 2: safe

        for (int i = 0; i < n; i++) {
            if (isSafe(i, graph, state)) {
                safeNodes.add(i);
            }
        }

        return safeNodes;           
    }
}
