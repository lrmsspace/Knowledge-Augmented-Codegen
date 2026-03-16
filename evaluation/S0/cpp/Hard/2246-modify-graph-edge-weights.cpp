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

class Solution {
public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        // Build adjacency list
        vector<vector<pair<int, long long>>> graph(n);
        vector<int> negEdges;
        
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1];
            long long w = (edges[i][2] == -1) ? INF : edges[i][2];
            
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
            
            if (edges[i][2] == -1) {
                negEdges.push_back(i);
            }
        }
        
        // Try all combinations of -1 edge weights using greedy approach
        // First, assign all -1 edges to 1
        for (int i = 0; i < edges.size(); i++) {
            if (edges[i][2] == -1) {
                edges[i][2] = 1;
            }
        }
        
        // Rebuild graph with weights=1 for -1 edges
        for (int i = 0; i < n; i++) {
            graph[i].clear();
        }
        
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1];
            long long w = edges[i][2];
            
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }
        
        // Check initial shortest path with all -1 edges set to 1
        long long dist1 = dijkstra(n, source, destination, graph);
        
        if (dist1 < target) {
            // Impossible
            return {};
        }
        
        bool found = false;
        
        for (int edgeIdx : negEdges) {
            if (found) break;
            
            long long dist1 = dijkstra(n, source, destination, graph);
            if (dist1 <= target) break;
            
            long long increase = dist1 - target;
            
            // Modify this edge
            long long oldWeight = edges[edgeIdx][2];
            edges[edgeIdx][2] = oldWeight + increase;
            
            // Rebuild graph
            for (int j = 0; j < n; j++) {
                graph[j].clear();
            }
            
            for (int j = 0; j < edges.size(); j++) {
                int u = edges[j][0], v = edges[j][1];
                long long w = edges[j][2];
                
                graph[u].emplace_back(v, w);
                graph[v].emplace_back(u, w);
            }

            long long newDist = dijkstra(n, source, destination, graph);
            if (newDist == target) {
                found = true;
            }
        }

        if (!found) {
            long long finalDist = dijkstra(n, source, destination, graph);
            if (finalDist != target) {
                return {};
            }
        }

        return edges;
    }
};
