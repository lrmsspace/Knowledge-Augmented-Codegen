// Source: https://leetcode.com/problems/number-of-good-paths/   |   Difficulty: Hard
//
// Problem Description:
// There is a tree (i.e. a connected, undirected graph with no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges.
//
// You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A good path is a simple path that satisfies the following conditions:
//
//
// 	The starting node and the ending node have the same value.
// 	All nodes between the starting node and the ending node have values less than or equal to the starting node (i.e. the starting node's value should be the maximum value along the path).
//
//
// Return the number of distinct good paths.
//
// Note that a path and its reverse are counted as the same path. For example, 0 -> 1 is considered to be the same as 1 -> 0. A single node is also considered as a valid path.
//
// Example:
// Input: vals = [1,3,2,1,3], edges = [[0,1],[0,2],[2,3],[2,4]]
// Output: 6
// Explanation: There are 5 good paths consisting of a single node.
// There is 1 additional good path: 1 -> 0 -> 2 -> 4.
// (The reverse path 4 -> 2 -> 0 -> 1 is treated as the same as 1 -> 0 -> 2 -> 4.)
// Note that 0 -> 2 -> 3 is not a good path because vals[2] > vals[0].
//
// Constraints:
// n == vals.length
// 	1 <= n <= 3 * 104
// 	0 <= vals[i] <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
//

class Solution {
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        // Group nodes by their values
        map<int, vector<int>> valToNodes;
        for (int i = 0; i < n; i++) {
            valToNodes[vals[i]].push_back(i);
        }
        
        // Union-Find structure
        vector<int> parent(n), size(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        };
        
        auto unionSets = [&](int a, int b) {
            a = find(a);
            b = find(b);
            if (a != b) {
                if (size[a] < size[b]) swap(a, b);
                parent[b] = a;
                size[a] += size[b];
            }
        };
        
        int goodPaths = 0;
        
        // Process nodes in order of their values
        for (auto& [val, nodes] : valToNodes) {
            // Union adjacent nodes with values <= current value
            for (int node : nodes) {
                for (int neighbor : adj[node]) {
                    if (vals[neighbor] <= val) {
                        unionSets(node, neighbor);
                    }
                }
            }
            
            // Count the number of nodes in each connected component
            unordered_map<int, int> groupCount;
            for (int node : nodes) {
                int root = find(node);
                groupCount[root]++;
            }
            
            // Calculate the number of good paths
            for (auto& [root, count] : groupCount) {
                goodPaths += count * (count + 1) / 2; // count single nodes and pairs
            }
        }
        
        return goodPaths;           
    }
};
