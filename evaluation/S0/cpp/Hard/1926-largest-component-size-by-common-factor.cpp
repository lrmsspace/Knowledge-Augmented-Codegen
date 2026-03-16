// Source: https://leetcode.com/problems/largest-component-size-by-common-factor/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array of unique positive integers nums. Consider the following graph:
//
//
// 	There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
// 	There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
//
//
// Return the size of the largest connected component in the graph.
//
// Example:
// Input: nums = [4,6,15,35]
// Output: 4
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 105
// 	All the values of nums are unique.
//

class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        int n = nums.size();
        int maxNum = *max_element(nums.begin(), nums.end());
        
        // Union-Find data structure
        vector<int> parent(maxNum + 1);
        for (int i = 0; i <= maxNum; i++) parent[i] = i;
        
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
        
        // For each number, connect it with its factors
        for (int num : nums) {
            for (int factor = 2; factor * factor <= num; factor++) {
                if (num % factor == 0) {
                    unite(num, factor);
                    unite(num, num / factor);
                }
            }
        }
        
        // Count the size of each component
        unordered_map<int, int> componentSize;
        int largestSize = 0;
        
        for (int num : nums) {
            int root = find(num);
            componentSize[root]++;
            largestSize = max(largestSize, componentSize[root]);
        }
        
        return largestSize;         
    }
};
