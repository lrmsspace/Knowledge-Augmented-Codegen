// Source: https://leetcode.com/problems/minimize-the-maximum-edge-weight-of-graph/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers, n and threshold, as well as a directed weighted graph of n nodes numbered from 0 to n - 1. The graph is represented by a 2D integer array edges, where edges[i] = [Ai, Bi, Wi] indicates that there is an edge going from node Ai to node Bi with weight Wi.
//
// You have to remove some edges from this graph (possibly none), so that it satisfies the following conditions:
//
//
// 	Node 0 must be reachable from all other nodes.
// 	The maximum edge weight in the resulting graph is minimized.
// 	Each node has at most threshold outgoing edges.
//
//
// Return the minimum possible value of the maximum edge weight after removing the necessary edges. If it is impossible for all conditions to be satisfied, return -1.
//
// Example:
// Input: n = 5, edges = [[1,0,1],[2,0,2],[3,0,1],[4,3,1],[2,1,1]], threshold = 2
//
// Output: 1
//
// Explanation:
//
//
//
// Remove the edge 2 -> 0. The maximum weight among the remaining edges is 1.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= threshold <= n - 1
// 	1 <= edges.length <= min(105, n * (n - 1) / 2).
// 	edges[i].length == 3
// 	0 <= Ai, Bi < n
// 	Ai != Bi
// 	1 <= Wi <= 106
// 	There may be multiple edges between a pair of nodes, but they must have unique weights.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, deque, array, 01-bfs)
//   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
//   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
//   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
//   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
//   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
// - Edge connectivity / Vertex connectivity (graph, enumeration)
//   • When to use: Used to quantify a graph's resilience by finding the minimum number of edges or vertices whose removal disconnects it, or separates a specific pair of nodes.
//   • Idea: Edge connectivity is the minimum edges to disconnect a graph, while vertex connectivity is for vertices. Both are often computed using max-flow min-cut theorems, typically in polynomial time.
//   • Invariants: The flow through any edge in the network does not exceed its capacity.; For any intermediate vertex (not source or sink), the total incoming flow equals the total outgoing flow.
//   • Tips: Edge connectivity between two specific vertices can be found using a max-flow min-cut algorithm.; To find global edge connectivity, iterate over all pairs of vertices or use specialized algorithms.
//   • Pitfalls: Confusing edge connectivity (edges) with vertex connectivity (vertices) requirements.; Incorrectly applying max-flow for global connectivity without considering all relevant source-sink pairs.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean canMakeAllNodesReachable(int n, int[][] edges, int threshold, int maxWeight) {
        List<List<Integer>> graph = new ArrayList<>();
        int[] outDegree = new int[n];
        
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (w <= maxWeight) {
                graph.get(v).add(u);
                outDegree[u]++;
            }
        }
        
        Deque<Integer> queue = new ArrayDeque<>();
        for (int i = 0; i < n; i++) {
            if (i != 0 && outDegree[i] <= threshold) {
                queue.offer(i);
            }
        }
        
        boolean[] visited = new boolean[n];
        visited[0] = true;
        
        while (!queue.isEmpty()) {
            int node = queue.poll();
            visited[node] = true;
            
            for (int neighbor : graph.get(node)) {
                outDegree[neighbor]--;
                if (!visited[neighbor] && neighbor != 0 && outDegree[neighbor] <= threshold) {
                    queue.offer(neighbor);
                }
            }
        }
        
        for (boolean v : visited) {
            if (!v) {
                return false;
            }
        }
        
        return true;
    }
    public int minMaxWeight(int n, int[][] edges, int threshold) {
        int left = 1, right = (int) 1e6, answer = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (canMakeAllNodesReachable(n, edges, threshold, mid)) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return answer;          
    }
}
