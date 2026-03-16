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
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} roads
 * @param {number} seats
 * @return {number}
 */
var minimumFuelCost = function(roads, seats) {
    const graph = Array.from({ length: roads.length + 1 }, () => []);
    
    for (const [u, v] of roads) {
        graph[u].push(v);
        graph[v].push(u);
    }
    
    let fuelCost = 0;
    
    const dfs = (node, parent) => {
        let representatives = 1; // Count the representative from the current city
        
        for (const neighbor of graph[node]) {
            if (neighbor !== parent) {
                representatives += dfs(neighbor, node); // Get representatives from the subtree
            }
        }
        
        if (node !== 0) { // If it's not the capital, calculate fuel cost
            fuelCost += Math.ceil(representatives / seats); // Calculate fuel cost for this node
        }
        
        return representatives; // Return total representatives in this subtree
    };
    
    dfs(0, -1); // Start DFS from the capital city
    
    return fuelCost;
};
