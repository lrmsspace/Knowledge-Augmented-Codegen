// Source: https://leetcode.com/problems/minimum-fuel-cost-to-report-to-the-capital/   |   Difficulty: Medium
//
// Problem Description:
// There is a tree (i.e., a connected, undirected graph with no cycles) structure country network consisting of n cities numbered from 0 to n - 1 and exactly n - 1 roads. The capital city is city 0. You are given a 2D integer array roads where roads[i] = [ai, bi] denotes that there exists a bidirectional road connecting cities ai and bi.
//
// There is a meeting for the representatives of each city. The meeting is in the capital city.
//
// There is a car in each city. You are given an integer seats that indicates the number of seats in each car.
//
// A representative can use the car in their city to travel or change the car and ride with another representative. The cost of traveling between two cities is one liter of fuel.
//
// Return the minimum number of liters of fuel to reach the capital city.
//
// Example:
// Input: roads = [[0,1],[0,2],[0,3]], seats = 5
// Output: 3
// Explanation: 
// - Representative1 goes directly to the capital with 1 liter of fuel.
// - Representative2 goes directly to the capital with 1 liter of fuel.
// - Representative3 goes directly to the capital with 1 liter of fuel.
// It costs 3 liters of fuel at minimum. 
// It can be proven that 3 is the minimum number of liters of fuel needed.
//
// Constraints:
// 1 <= n <= 105
// 	roads.length == n - 1
// 	roads[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	roads represents a valid tree.
// 	1 <= seats <= 105
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Minimum-cost flow - Successive shortest path algorithm (graph, array, greedy, dijkstra, bellman-ford)
//   • When to use: This algorithm finds a minimum-cost flow of a given amount from a source to a sink in a flow network. It is suitable when both flow capacity and edge costs are present.
//   • Idea: The successive shortest path algorithm iteratively finds augmenting paths with minimum cost in a residual graph, using shortest path algorithms like Bellman-Ford or Dijkstra with potentials, until the desired flow is achieved. Its complexity depends on the shortest path algorithm used and the number of augmentations.
//   • Invariants: The total flow pushed from source to sink never exceeds the sum of capacities of edges leaving the source.; For any edge (u, v) with flow f_uv, 0 <= f_uv <= capacity_uv.
//   • Tips: Use potentials with Dijkstra for non-negative edge costs in the residual graph.; Bellman-Ford is necessary if initial edge costs can be negative or if potentials are not used.
//   • Pitfalls: Incorrectly updating potentials can lead to wrong shortest paths.; Forgetting to add reverse edges with negative costs in the residual graph.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        int n = roads.size() + 1;
        std::vector<std::vector<int>> graph(n);
        for (const auto& road : roads) {
            int u = road[0], v = road[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        long long totalFuel = 0;

        std::function<int(int, int)> dfs = [&](int node, int parent) -> int {
            int representatives = 1; // Count the representative of the current city
            for (int neighbor : graph[node]) {
                if (neighbor == parent) continue; // Avoid going back to parent
                representatives += dfs(neighbor, node);
            }
            if (node != 0) { // If not the capital
                long long trips = (representatives + seats - 1) / seats; // Ceiling division
                totalFuel += trips; // Each trip costs 1 liter of fuel
            }
            return representatives;
        };

        dfs(0, -1); // Start DFS from the capital city (node 0)

        return totalFuel;           
    }
};
