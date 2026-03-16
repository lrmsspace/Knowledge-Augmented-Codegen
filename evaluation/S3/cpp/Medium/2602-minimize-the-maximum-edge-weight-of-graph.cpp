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
// - Flows with demands (graph, binary-search-answer)
//   • When to use: Use when a problem involves finding a flow in a network where edges have both lower and upper capacity bounds, or nodes have supply/demand requirements, and an optimal value needs to be found.
//   • Idea: This technique transforms a network with lower and upper capacity bounds on edges (or node demands) into a standard max-flow problem. It often involves adding a new source and sink to handle demands, and then binary searching on the answer if an optimal value is sought, typically with O(MaxFlow * log(Range)) complexity.
//   • Invariants: The total flow out of the super source equals the total demand that needs to be satisfied.; For any node, the sum of incoming flow minus outgoing flow equals its net demand (0 for internal nodes in a circulation).
//   • Tips: Convert lower bounds to demands by adjusting capacities and adding a super source/sink.; A feasible flow exists if the max flow in the transformed network equals the total demand.
//   • Pitfalls: Incorrectly calculating residual capacities after demand satisfaction.; Forgetting to add a super source/sink for handling demands.
// - Breadth-first search (graph, deque, array, 01-bfs)
//   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
//   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
//   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
//   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
//   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        (void)threshold;

        vector<vector<pair<int, int>>> rev(n);
        vector<int> weights;
        weights.reserve(edges.size());

        for (const auto& edge : edges) {
            int from = edge[0];
            int to = edge[1];
            int weight = edge[2];
            rev[to].push_back({from, weight});
            weights.push_back(weight);
        }

        if (weights.empty()) {
            return -1;
        }

        sort(weights.begin(), weights.end());
        weights.erase(unique(weights.begin(), weights.end()), weights.end());

        auto canReachAll = [&](int limit) {
            vector<char> visited(n, 0);
            queue<int> q;
            visited[0] = 1;
            q.push(0);
            int reached = 1;

            while (!q.empty()) {
                int current = q.front();
                q.pop();

                for (const auto& next : rev[current]) {
                    int node = next.first;
                    int weight = next.second;
                    if (weight <= limit && !visited[node]) {
                        visited[node] = 1;
                        ++reached;
                        q.push(node);
                    }
                }
            }

            return reached == n;
        };

        if (!canReachAll(weights.back())) {
            return -1;
        }

        int left = 0;
        int right = static_cast<int>(weights.size()) - 1;
        int answer = weights.back();

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canReachAll(weights[mid])) {
                answer = weights[mid];
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return answer;
    }
};
