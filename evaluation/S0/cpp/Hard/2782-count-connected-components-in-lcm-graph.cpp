// Source: https://leetcode.com/problems/count-connected-components-in-lcm-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums of size n and a positive integer threshold.
//
// There is a graph consisting of n nodes with the ith node having a value of nums[i]. Two nodes i and j in the graph are connected via an undirected edge if lcm(nums[i], nums[j]) <= threshold.
//
// Return the number of connected components in this graph.
//
// A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// The term lcm(a, b) denotes the least common multiple of a and b.
//
// Example:
// Input: nums = [2,4,8,3,9], threshold = 5
//
// Output: 4
//
// Explanation: 
//
//
//
//  
//
// The four connected components are (2, 4), (3), (8), (9).
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	All elements of nums are unique.
// 	1 <= threshold <= 2 * 105
//

class Solution {
public:
    int countComponents(vector<int>& nums, int threshold) {
        int n = nums.size();
        vector<int> parent(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        auto unite = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                parent[rootY] = rootX;
            }
        };
        
        unordered_map<int, vector<int>> factorMap;
        
        for (int i = 0; i < n; i++) {
            int val = nums[i];
            for (int f = 1; f * f <= val; f++) {
                if (val % f == 0) {
                    if (f > threshold) continue;
                    factorMap[f].push_back(i);
                    int otherFactor = val / f;
                    if (otherFactor != f && otherFactor <= threshold) {
                        factorMap[otherFactor].push_back(i);
                    }
                }
            }
        }
        
        for (const auto& [factor, indices] : factorMap) {
            for (size_t i = 1; i < indices.size(); i++) {
                unite(indices[0], indices[i]);
            }
        }
        
        unordered_set<int> components;
        for (int i = 0; i < n; i++) {
            components.insert(find(i));
        }
        
        return components.size();           
    }
};
