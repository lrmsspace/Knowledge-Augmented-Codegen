// Source: https://leetcode.com/problems/find-weighted-median-node-in-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an edge from node ui to vi with weight wi.
//
// The weighted median node is defined as the first node x on the path from ui to vi such that the sum of edge weights from ui to x is greater than or equal to half of the total path weight.
//
// You are given a 2D integer array queries. For each queries[j] = [uj, vj], determine the weighted median node along the path from uj to vj.
//
// Return an array ans, where ans[j] is the node index of the weighted median for queries[j].
//
// Example:
// Input: n = 2, edges = [[0,1,7]], queries = [[1,0],[0,1]]
//
// Output: [0,1]
//
// Explanation:
//
//
//
//
// 	
// 		
// 			Query
// 			Path
// 			Edge
// 			Weights
// 			Total
// 			Path
// 			Weight
// 			Half
// 			Explanation
// 			Answer
// 		
// 	
// 	
// 		
// 			[1, 0]
// 			1 → 0
// 			[7]
// 			7
// 			3.5
// 			Sum from 1 → 0 = 7 >= 3.5, median is node 0.
// 			0
// 		
// 		
// 			[0, 1]
// 			0 → 1
// 			[7]
// 			7
// 			3.5
// 			Sum from 0 → 1 = 7 >= 3.5, median is node 1.
// 			1
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	0 <= ui, vi < n
// 	1 <= wi <= 109
// 	1 <= queries.length <= 105
// 	queries[j] == [uj, vj]
// 	0 <= uj, vj < n
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Minimum spanning tree - Prim's algorithm (graph, mst-prim, greedy)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, undirected, weighted graph. It is often preferred for dense graphs due to its O(V^2) or O(E log V) complexity.
//   • Idea: Prim's algorithm is a greedy algorithm that builds a minimum spanning tree by iteratively adding the cheapest edge connecting a vertex in the growing tree to one outside it. It typically runs in O(E log V) time with a binary heap or O(V^2) with an adjacency matrix.
//   • Invariants: The set of vertices already included in the MST forms a connected component.; For any vertex not yet in the MST, its associated key/distance stores the minimum weight of an edge connecting it to a vertex already in the MST.
//   • Tips: Use a priority queue to efficiently retrieve the minimum weight edge connecting to the MST.; Initialize distances for all vertices to infinity, except the starting vertex (0).
//   • Pitfalls: Not suitable for disconnected graphs; it will only find an MST for the component of the starting vertex.; Forgetting to handle edge cases like graphs with no edges or a single vertex.
// - Lowest Common Ancestor (tree, segment-tree)
//   • When to use: Use this approach to efficiently answer multiple Lowest Common Ancestor queries on a static tree. It is suitable when precomputation time is acceptable for faster subsequent queries.
//   • Idea: This method transforms the LCA problem into a Range Minimum Query (RMQ) problem by constructing an Euler tour of the tree. It achieves O(N log N) precomputation and O(log N) query time by building a segment tree over the depths of nodes in the Euler tour.
//   • Invariants: The Euler tour array correctly records nodes in DFS entry and exit order.; The depth array stores the depth of each node as it appears in the Euler tour.
//   • Tips: Perform a DFS to generate an Euler tour of the tree, recording nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Incorrectly constructing the Euler tour or depth array, leading to wrong ranges for RMQ.; Off-by-one errors when mapping node indices to Euler tour indices or defining segment tree query ranges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

#include <vector>
#include <queue>
#include <utility>
#include <cstdint>

using namespace std;

class Solution {
public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // Build adjacency list for the weighted tree
        vector<vector<pair<int,long long>>> g(n);
        g.reserve(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            long long w = (long long)e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        // Binary lifting setup
        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        vector<vector<int>> up(n, vector<int>(LOG, 0));
        vector<vector<long long>> acc(n, vector<long long>(LOG, 0)); // accumulated weight to 2^k ancestor
        vector<int> depth(n, 0);
        vector<long long> dist(n, 0); // weighted distance from root 0

        // BFS from root to compute parent, depth, dist
        vector<int> visited(n, 0);
        queue<int> q;
        visited[0] = 1;
        up[0][0] = 0;
        acc[0][0] = 0;
        depth[0] = 0;
        dist[0] = 0;
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &pr : g[u]) {
                int v = pr.first; long long w = pr.second;
                if (visited[v]) continue;
                visited[v] = 1;
                up[v][0] = u;
                acc[v][0] = w;
                depth[v] = depth[u] + 1;
                dist[v] = dist[u] + w;
                q.push(v);
            }
        }

        // Precompute binary lifting tables
        for (int k = 1; k < LOG; ++k) {
            for (int v = 0; v < n; ++v) {
                int mid = up[v][k-1];
                up[v][k] = up[mid][k-1];
                acc[v][k] = acc[v][k-1] + acc[mid][k-1];
            }
        }

        auto lift_by_weight = [&](int node, long long wneed) -> int {
            // Move upwards from `node` accumulating weight, stopping at the first vertex
            // where cumulative sum >= wneed. If cumulative equals exactly wneed at a vertex,
            // return that vertex.
            if (wneed <= 0) return node;
            for (int k = LOG - 1; k >= 0; --k) {
                if (acc[node][k] <= wneed) {
                    wneed -= acc[node][k];
                    node = up[node][k];
                }
            }
            if (wneed == 0) return node;
            // Need one more edge to cross the threshold
            return up[node][0];
        };

        auto lca = [&](int a, int b) -> int {
            if (depth[a] < depth[b]) swap(a, b);
            int diff = depth[a] - depth[b];
            for (int k = LOG - 1; k >= 0; --k) {
                if (diff & (1 << k)) a = up[a][k];
            }
            if (a == b) return a;
            for (int k = LOG - 1; k >= 0; --k) {
                if (up[a][k] != up[b][k]) {
                    a = up[a][k];
                    b = up[b][k];
                }
            }
            return up[a][0];
        };

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto &qv : queries) {
            int u = qv[0], v = qv[1];
            if (u == v) { ans.push_back(u); continue; }
            int w = lca(u, v);
            long long total = dist[u] + dist[v] - 2LL * dist[w];
            long long half = (total + 1LL) / 2LL; // ceil(total/2)
            long long up_dist = dist[u] - dist[w];
            if (half <= up_dist) {
                ans.push_back(lift_by_weight(u, half));
            } else {
                long long rem = half - up_dist; // need to go down from LCA towards v
                long long down_total = dist[v] - dist[w];
                // Move up from v by (down_total - rem)
                long long back = down_total - rem;
                ans.push_back(lift_by_weight(v, back));
            }
        }

        return ans;
    }
};
