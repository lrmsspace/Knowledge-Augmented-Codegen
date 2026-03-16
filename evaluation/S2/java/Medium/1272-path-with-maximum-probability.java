// Source: https://leetcode.com/problems/path-with-maximum-probability/   |   Difficulty: Medium
//
// Problem Description:
// You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success of traversing that edge succProb[i].
//
// Given two nodes start and end, find the path with the maximum probability of success to go from start to end and return its success probability.
//
// If there is no path from start to end, return 0. Your answer will be accepted if it differs from the correct answer by at most 1e-5.
//
// Example:
// Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
// Output: 0.25000
// Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.
//
// Constraints:
// 2 <= n <= 10^4
// 	0 <= start, end < n
// 	start != end
// 	0 <= a, b < n
// 	a != b
// 	0 <= succProb.length == edges.length <= 2*10^4
// 	0 <= succProb[i] <= 1
// 	There is at most one edge between every two nodes.
//
// Helpful references (internal KB):
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
//   • When to use: Use when you need to find the Lowest Common Ancestor for multiple pairs of nodes in a tree, and all queries are known beforehand. It's an efficient offline approach for batch processing LCA queries.
//   • Idea: Tarjan's offline LCA algorithm uses a Depth-First Search (DFS) traversal combined with a Union-Find data structure to answer all LCA queries efficiently. It processes N nodes and Q queries in O(N + Q * alpha(N)) time, where alpha is the inverse Ackermann function.
//   • Invariants: After visiting a node 'u' and all its children, 'u' is marked as visited.; For any node 'v' whose subtree has been fully processed, 'find_set(v)' returns the representative of 'v''s component.
//   • Tips: Mark nodes as visited during DFS to track processed subtrees.; Use Union-Find's union operation to merge child subtrees with their parent after processing.
//   • Pitfalls: Forgetting to mark nodes as visited, leading to incorrect LCA identification.; Incorrectly updating the 'ancestor' array or 'find_set' logic in Union-Find.
// - Maximum flow - Ford-Fulkerson and Edmonds-Karp (graph, array, bfs)
//   • When to use: When needing to find the maximum possible flow from a source to a sink in a flow network. It is particularly useful for problems involving resource allocation, transportation, or matching.
//   • Idea: Ford-Fulkerson finds maximum flow by repeatedly augmenting paths in a residual graph. Edmonds-Karp uses BFS for shortest augmenting paths, ensuring O(VE^2) time complexity and termination.
//   • Invariants: The flow through any edge never exceeds its capacity.; For every vertex (except source and sink), total incoming flow equals total outgoing flow (flow conservation).
//   • Tips: Always construct a residual graph to represent remaining capacities and backward flow.; BFS ensures finding the shortest augmenting path, leading to the O(VE^2) complexity.
//   • Pitfalls: Incorrectly updating residual capacities for backward edges can lead to wrong results.; Using DFS for Ford-Fulkerson can lead to poor performance or non-termination with irrational capacities.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public double maxProbability(int n, int[][] edges, double[] succProb, int start_node, int end_node) {
        // Build the graph as an adjacency list
        List<List<Pair>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            double prob = succProb[i];
            graph.get(u).add(new Pair(v, prob));
            graph.get(v).add(new Pair(u, prob));
        }

        // Max-heap to store (probability, node)
        PriorityQueue<Pair> pq = new PriorityQueue<>((a, b) -> Double.compare(b.prob, a.prob));
        pq.offer(new Pair(start_node, 1.0)); // Start with probability 1 at the start node

        double[] maxProb = new double[n];
        Arrays.fill(maxProb, 0.0);
        maxProb[start_node] = 1.0;

        while (!pq.isEmpty()) {
            Pair current = pq.poll();
            int node = current.node;
            double prob = current.prob;

            if (node == end_node) {
                return prob; // Return the maximum probability to reach end_node
            }

            for (Pair neighbor : graph.get(node)) {
                double newProb = prob * neighbor.prob;
                if (newProb > maxProb[neighbor.node]) {
                    maxProb[neighbor.node] = newProb;
                    pq.offer(new Pair(neighbor.node, newProb));
                }
            }
        }

        return 0.0; // If end_node is unreachable           
    }
}
