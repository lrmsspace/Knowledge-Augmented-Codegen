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
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
// - Minimum-cost flow - Successive shortest path algorithm (graph, array, number, greedy, dijkstra, bellman-ford)
//   • When to use: When you need to find a flow of a certain amount (or maximum possible flow) through a network while minimizing the total cost associated with sending flow along edges. It is suitable for problems involving resource allocation with varying costs.
//   • Idea: The successive shortest path algorithm finds a minimum-cost flow by repeatedly finding a shortest augmenting path in the residual graph and pushing flow along it. Its complexity depends on the shortest path algorithm used (Bellman-Ford for general costs, Dijkstra with potentials for non-negative residual costs).
//   • Invariants: At the start of each iteration, the current flow is a valid flow from source to sink.; The residual graph correctly represents remaining capacities and reverse edges for the current flow.
//   • Tips: Use potentials (reduced costs) with Dijkstra to efficiently handle non-negative edge costs in the residual graph.; Initialize potentials to zero and update them after each shortest path computation.
//   • Pitfalls: Incorrectly updating residual capacities or reverse edge costs can lead to wrong results.; Failing to use potentials with Dijkstra can lead to incorrect shortest paths in graphs with negative edges.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        const long long INF = 1e15;
        auto dijkstra = [&](const vector<vector<pair<int, long long>>>& graph, int start) {
            vector<long long> dist(n, INF);
            dist[start] = 0;
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
            pq.emplace(0, start);

            while (!pq.empty()) {
                auto [currentDist, u] = pq.top();
                pq.pop();
                if (currentDist > dist[u]) continue;

                for (const auto& [v, weight] : graph[u]) {
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        pq.emplace(dist[v], v);
                    }
                }
            }
            return dist;
        };

        auto buildGraph = [&](long long replaceWeight) {
            vector<vector<pair<int, long long>>> graph(n);
            for (const auto& edge : edges) {
                int u = edge[0], v = edge[1];
                long long weight = (edge[2] == -1) ? replaceWeight : edge[2];
                graph[u].emplace_back(v, weight);
                graph[v].emplace_back(u, weight);
            }
            return graph;
        };

        // First check with minimum weights
        auto graphMin = buildGraph(1);
        auto distMin = dijkstra(graphMin, source);
        if (distMin[destination] > target) return {};

        // Then check with maximum weights
        auto graphMax = buildGraph(2e9);
        auto distMax = dijkstra(graphMax, source);
        if (distMax[destination] < target) return {};

        // Binary search for the right replacement weight
        long long left = 1, right = 2e9;
        long long bestWeight = -1;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            auto graphMid = buildGraph(mid);
            auto distMid = dijkstra(graphMid, source);
            if (distMid[destination] <= target) {
                bestWeight = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // Build final graph with bestWeight and adjust edges to meet target    
        auto finalGraph = buildGraph(bestWeight);
        auto finalDist = dijkstra(finalGraph, source);
        long long diff = target - finalDist[destination];
        for (auto& edge : edges) {
            if (edge[2] == -1 && diff > 0) {
                long long newWeight = bestWeight + diff;
                edge[2] = static_cast<int>(newWeight);
                diff = 0; // Only adjust once
            } else if (edge[2] == -1) {
                edge[2] = static_cast<int>(bestWeight);
            }
        }
        return edges;
    }
};
