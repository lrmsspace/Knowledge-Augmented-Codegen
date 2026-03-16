// Source: https://leetcode.com/problems/minimum-cost-of-a-path-with-special-roads/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array start where start = [startX, startY] represents your initial position (startX, startY) in a 2D space. You are also given the array target where target = [targetX, targetY] represents your target position (targetX, targetY).
//
// The cost of going from a position (x1, y1) to any other position in the space (x2, y2) is |x2 - x1| + |y2 - y1|.
//
// There are also some special roads. You are given a 2D array specialRoads where specialRoads[i] = [x1i, y1i, x2i, y2i, costi] indicates that the ith special road goes in one direction from (x1i, y1i) to (x2i, y2i) with a cost equal to costi. You can use each special road any number of times.
//
// Return the minimum cost required to go from (startX, startY) to (targetX, targetY).
//
// Example:
// Input: start = [1,1], target = [4,5], specialRoads = [[1,2,3,3,2],[3,4,4,5,1]]
//
// Output: 5
//
// Explanation:
//
//
// 	(1,1) to (1,2) with a cost of |1 - 1| + |2 - 1| = 1.
// 	(1,2) to (3,3). Use specialRoads[0] with the cost 2.
// 	(3,3) to (3,4) with a cost of |3 - 3| + |4 - 3| = 1.
// 	(3,4) to (4,5). Use specialRoads[1] with the cost 1.
//
//
// So the total cost is 1 + 2 + 1 + 1 = 5.
//
// Constraints:
// start.length == target.length == 2
// 	1 <= startX <= targetX <= 105
// 	1 <= startY <= targetY <= 105
// 	1 <= specialRoads.length <= 200
// 	specialRoads[i].length == 5
// 	startX <= x1i, x2i <= targetX
// 	startY <= y1i, y2i <= targetY
// 	1 <= costi <= 105
//
// Helpful references (internal KB):
// - Manhattan Distance (geometry, graph, sweep-line, mst-kruskal, coordinate-compress)
//   • When to use: Use this when finding the Minimum Spanning Tree for points in a 2D plane where edge weights are Manhattan distances, or when a geometric problem can be simplified by transforming Manhattan to Chebyshev distance.
//   • Idea: This algorithm finds the Minimum Spanning Tree for points in a 2D plane using Manhattan distance. It leverages a sweep-line approach to efficiently find nearest neighbors in specific octants, reducing the number of candidate edges for Kruskal's algorithm, achieving O(N log N) complexity.
//   • Invariants: For any point 's' in the active set, its nearest neighbor in the current octant has not yet been processed.; Points are processed in non-decreasing order of 'x + y' (or transformed coordinate), ensuring local optimality for distances.
//   • Tips: Consider transforming Manhattan distance problems into Chebyshev distance problems using (x+y, y-x) coordinates.; Divide the plane into 8 octants around each point to simplify nearest neighbor searches.
//   • Pitfalls: Incorrectly defining or handling the 8 octants, especially near boundaries or for points with equal coordinates.; Inefficiently managing the 'active set' during the sweep-line, leading to higher than O(N log N) complexity.
// - Finding the equation of a line for a segment (geometry, number, enumeration)
//   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
//   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
//   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
//   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
//   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
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
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        // This problem can be solved using Dijkstra's algorithm on a graph where nodes are the start, target, and endpoints of special roads. 
        // We will create a graph with these nodes and edges representing the cost of moving between them, including the special roads.
        
        // Step 1: Create a list of all nodes (start, target, and endpoints of special roads)
        vector<vector<int>> nodes = {start, target};
        for (const auto& road : specialRoads) {
            nodes.push_back({road[0], road[1]}); // start of the special road
            nodes.push_back({road[2], road[3]}); // end of the special road
        }
        
        // Step 2: Create a graph as an adjacency list
        unordered_map<int, vector<pair<int, int>>> graph; // node index -> list of (neighbor index, cost)
        
        // Add edges for direct movement between all pairs of nodes
        for (int i = 0; i < nodes.size(); ++i) {
            for (int j = i + 1; j < nodes.size(); ++j) {
                int cost = abs(nodes[i][0] - nodes[j][0]) + abs(nodes[i][1] - nodes[j][1]);
                graph[i].emplace_back(j, cost);
                graph[j].emplace_back(i, cost);
            }
        }
        
        // Add edges for special roads
        for (const auto& road : specialRoads) {
            int startNode = find(nodes.begin(), nodes.end(), vector<int>{road[0], road[1]}) - nodes.begin();
            int endNode = find(nodes.begin(), nodes.end(), vector<int>{road[2], road[3]}) - nodes.begin();
            graph[startNode].emplace_back(endNode, road[4]); // one-way from startNode to endNode
        }
        
        // Step 3: Use Dijkstra's algorithm to find the minimum cost from start to target
        int startIndex = 0; // index of start node
        int targetIndex = 1; // index of target node
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // (cost, node index)
        pq.emplace(0, startIndex);
        vector<int> minCost(nodes.size(), INT_MAX);
        minCost[startIndex] = 0;
              
        while (!pq.empty()) {
            auto [cost, node] = pq.top();
            pq.pop();
            
            if (node == targetIndex) {
                return cost;
            }
            
            if (cost > minCost[node]) {
                continue;
            }
            
            for (const auto& [neighbor, edgeCost] : graph[node]) {
                int newCost = cost + edgeCost;
                if (newCost < minCost[neighbor]) {
                    minCost[neighbor] = newCost;
                    pq.emplace(newCost, neighbor);
                }
            }
        }
        return -1; // If no path exists
    }
};
