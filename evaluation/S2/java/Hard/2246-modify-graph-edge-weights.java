// Source: https://leetcode.com/problems/modify-graph-edge-weights/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted connected graph containing n nodes labeled from 0 to n - 1, and an integer array edges where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.
//
// Some edges have a weight of -1 (wi = -1), while others have a positive weight (wi > 0).
//
// Your task is to modify all edges with a weight of -1 by assigning them positive integer values in the range [1, 2 * 109] so that the shortest distance between the nodes source and destination becomes equal to an integer target. If there are multiple modifications that make the shortest distance between source and destination equal to target, any of them will be considered correct.
//
// Return an array containing all edges (even unmodified ones) in any order if it is possible to make the shortest distance from source to destination equal to target, or an empty array if it's impossible.
//
// Note: You are not allowed to modify the weights of edges with initial positive weights.
//
// Example:
// Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
// Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
// Explanation: The graph above shows a possible modification to the edges, making the distance from 0 to 1 equal to 5.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= edges.length <= n * (n - 1) / 2
// 	edges[i].length == 3
// 	0 <= ai, bi < n
// 	wi = -1 or 1 <= wi <= 107
// 	ai != bi
// 	0 <= source, destination < n
// 	source != destination
// 	1 <= target <= 109
// 	The graph is connected, and there are no self-loops or repeated edges
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
// - Second Best Minimum Spanning Tree (graph, tree, mst-kruskal, lca, binary-lifting, enumeration)
//   • When to use: When you need to find a spanning tree with the second smallest total edge weight, typically after finding the primary Minimum Spanning Tree.
//   • Idea: This algorithm finds the second best Minimum Spanning Tree by iterating through non-MST edges, adding each to the MST to form a cycle, and then removing the maximum weight edge on that cycle (excluding the added edge). It leverages Kruskal's for the initial MST and LCA with binary lifting for efficient path maximum queries, achieving an overall time complexity of O(E log E + E log V).
//   • Invariants: The initial MST is always a valid spanning tree with minimum total weight.; For any non-MST edge (u, v) added, a unique cycle is formed in the current graph.
//   • Tips: Precompute LCA and maximum edge weights on paths using binary lifting for efficiency.; The initial MST can be found using Kruskal's or Prim's algorithm.
//   • Pitfalls: Incorrectly identifying the maximum weight edge on the cycle when adding a non-MST edge.; Forgetting to exclude the newly added edge itself when finding the maximum edge on the cycle.
// - Finding a negative cycle in the graph (graph, matrix, floyd-warshall)
//   • When to use: Use when you need to find if a negative cycle exists in a graph, especially when dealing with all-pairs shortest paths or when edge weights can be negative. It is suitable for dense graphs.
//   • Idea: The Floyd-Warshall algorithm can detect negative cycles by checking if any vertex has a negative distance to itself after all iterations. It computes all-pairs shortest paths in O(V^3) time.
//   • Invariants: After k iterations, dist[i][j] stores the shortest path from i to j using only intermediate vertices from 0 to k-1.; For any i, dist[i][i] remains 0 unless a negative cycle involving i is found.
//   • Tips: Initialize distance matrix with edge weights or infinity for non-existent edges.; Set dist[i][i] to 0 for all i initially.
//   • Pitfalls: Incorrect initialization of the distance matrix, especially dist[i][i].; Forgetting to check the main diagonal for negative values after computation.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[][] modifiedGraphEdges(int n, int[][] edges, int source, int destination, int target) {
        // Step 1: Build the graph and identify edges with weight -1
        List<List<int[]>> graph = new ArrayList<>();
        List<int[]> negativeEdges = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (w == -1) {
                negativeEdges.add(edge);
                w = 1; // Temporarily treat -1 as 1 for initial shortest path calculation
            }
            graph.get(u).add(new int[]{v, w});
            graph.get(v).add(new int[]{u, w});
        }

        // Step 2: Use Dijkstra's algorithm to find the shortest path from source to destination
        int[] dist = dijkstra(graph, source, n);
        if (dist[destination] > target) {
            return new int[0][];
        }

        // Step 3: If the shortest path is less than target, we need to increase some weights
        if (dist[destination] < target) {
            int diff = target - dist[destination];
            for (int[] edge : negativeEdges) {
                if (diff <= 0) break;
                edge[2] += diff; // Increase the weight of this edge by the remaining difference
                diff = 0; // After adjusting one edge, we can stop
            }
        }

        return edges;           
    }
}
