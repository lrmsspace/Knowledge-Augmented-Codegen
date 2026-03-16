// Source: https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph (the "original graph") with n nodes labeled from 0 to n - 1. You decide to subdivide each edge in the graph into a chain of nodes, with the number of new nodes varying between each edge.
//
// The graph is given as a 2D array of edges where edges[i] = [ui, vi, cnti] indicates that there is an edge between nodes ui and vi in the original graph, and cnti is the total number of new nodes that you will subdivide the edge into. Note that cnti == 0 means you will not subdivide the edge.
//
// To subdivide the edge [ui, vi], replace it with (cnti + 1) new edges and cnti new nodes. The new nodes are x1, x2, ..., xcnti, and the new edges are [ui, x1], [x1, x2], [x2, x3], ..., [xcnti-1, xcnti], [xcnti, vi].
//
// In this new graph, you want to know how many nodes are reachable from the node 0, where a node is reachable if the distance is maxMoves or less.
//
// Given the original graph and maxMoves, return the number of nodes that are reachable from node 0 in the new graph.
//
// Example:
// Input: edges = [[0,1,10],[0,2,1],[1,2,2]], maxMoves = 6, n = 3
// Output: 13
// Explanation: The edge subdivisions are shown in the image above.
// The nodes that are reachable are highlighted in yellow.
//
// Constraints:
// 0 <= edges.length <= min(n * (n - 1) / 2, 104)
// 	edges[i].length == 3
// 	0 <= ui < vi < n
// 	There are no multiple edges in the graph.
// 	0 <= cnti <= 104
// 	0 <= maxMoves <= 109
// 	1 <= n <= 3000
//
// Helpful references (internal KB):
// - Dijkstra Algorithm (graph, array, dijkstra, greedy)
//   • When to use: Use this algorithm to find the shortest paths from a single source to all other vertices in a graph. It is applicable when all edge weights are non-negative.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source vertex to all other vertices in a weighted graph with non-negative edge weights. It iteratively selects the unvisited vertex with the smallest known distance, relaxing its outgoing edges, achieving O(V^2 + E) or O(E log V) complexity.
//   • Invariants: For any marked vertex v, d[v] holds the true shortest path distance from s to v.; For any unmarked vertex v, d[v] holds the shortest path distance from s to v using only marked intermediate vertices.
//   • Tips: Use a priority queue for sparse graphs to optimize performance to O(E log V).; Initialize distances to infinity for all vertices except the source, which is zero.
//   • Pitfalls: Dijkstra's algorithm does not work correctly with negative edge weights; use Bellman-Ford or SPFA instead.; Failing to use an efficient data structure (like a priority queue) for vertex selection can lead to O(V^2) performance on sparse graphs.
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int reachableNodes(int[][] edges, int maxMoves, int n) {
        List<int[]>[] graph = new List[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }
        for (int[] edge : edges) {
            graph[edge[0]].add(new int[]{edge[1], edge[2] + 1});
            graph[edge[1]].add(new int[]{edge[0], edge[2] + 1});
        }

        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        pq.offer(new int[]{0, 0}); // moves, node
        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[0] = 0;

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int moves = curr[0];
            int node = curr[1];
            if (moves > dist[node]) {
                continue;
            }
            for (int[] neighbor : graph[node]) {
                int nextNode = neighbor[0];
                int weight = neighbor[1];
                int nextMoves = moves + weight;
                if (nextMoves < dist[nextNode] && nextMoves <= maxMoves) {
                    dist[nextNode] = nextMoves;
                    pq.offer(new int[]{nextMoves, nextNode});
                }
            }
        }

        int result = 0;
        for (int d : dist) {
            if (d <= maxMoves) {
                result++;
            }
        }

        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cnt = edge[2];

            int usedFromU = dist[u] <= maxMoves ? Math.min(cnt, maxMoves - dist[u]) : 0;
            int usedFromV = dist[v] <= maxMoves ? Math.min(cnt, maxMoves - dist[v]) : 0;

            result += Math.min(cnt, usedFromU + usedFromV);
        }

        return result;          
    }
}
