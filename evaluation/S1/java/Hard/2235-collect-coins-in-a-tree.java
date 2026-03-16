// Source: https://leetcode.com/problems/collect-coins-in-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected and unrooted tree with n nodes indexed from 0 to n - 1. You are given an integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given an array coins of size n where coins[i] can be either 0 or 1, where 1 indicates the presence of a coin in the vertex i.
//
// Initially, you choose to start at any vertex in the tree. Then, you can perform the following operations any number of times: 
//
//
//  Collect all the coins that are at a distance of at most 2 from the current vertex, or
//  Move to any adjacent vertex in the tree.
//
//
// Find the minimum number of edges you need to go through to collect all the coins and go back to the initial vertex.
//
// Note that if you pass an edge several times, you need to count it into the answer several times.
//
// Example:
// Input: coins = [1,0,0,0,0,1], edges = [[0,1],[1,2],[2,3],[3,4],[4,5]]
// Output: 2
// Explanation: Start at vertex 2, collect the coin at vertex 0, move to vertex 3, collect the coin at vertex 5 then move back to vertex 2.
//
// Constraints:
// n == coins.length
//  1 <= n <= 3 * 104
//  0 <= coins[i] <= 1
//  edges.length == n - 1
//  edges[i].length == 2
//  0 <= ai, bi < n
//  ai != bi
//  edges represents a valid tree.
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int collectTheCoins(int[] coins, int[][] edges) {
        int n = coins.length;
        List<Set<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new HashSet<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        // Prune leaves without coins twice
        for (int t = 0; t < 2; t++) {
            Queue<Integer> queue = new LinkedList<>();
            for (int i = 0; i < n; i++) {
                if (graph.get(i).size() == 1 && coins[i] == 0) {
                    queue.offer(i);
                }
            }
            while (!queue.isEmpty()) {
                int node = queue.poll();
                for (int neighbor : graph.get(node)) {
                    graph.get(neighbor).remove(node);
                    if (graph.get(neighbor).size() == 1 && coins[neighbor] == 0) {
                        queue.offer(neighbor);
                    }
                }
                graph.get(node).clear();
            }
        }

        // Count remaining edges
        int remainingEdges = 0;
        for (Set<Integer> neighbors : graph) {
            remainingEdges += neighbors.size();
        }

        return remainingEdges == 0 ? 0 : (remainingEdges - 1) * 2;          
    }
}
