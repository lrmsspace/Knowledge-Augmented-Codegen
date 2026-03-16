// Source: https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/   |   Difficulty: Hard
//
// Problem Description:
// There is a family tree rooted at 0 consisting of n nodes numbered 0 to n - 1. You are given a 0-indexed integer array parents, where parents[i] is the parent for node i. Since node 0 is the root, parents[0] == -1.
//
// There are 105 genetic values, each represented by an integer in the inclusive range [1, 105]. You are given a 0-indexed integer array nums, where nums[i] is a distinct genetic value for node i.
//
// Return an array ans of length n where ans[i] is the smallest genetic value that is missing from the subtree rooted at node i.
//
// The subtree rooted at a node x contains node x and all of its descendant nodes.
//
// Example:
// Input: parents = [-1,0,0,2], nums = [1,2,3,4]
// Output: [5,1,1,1]
// Explanation: The answer for each subtree is calculated as follows:
// - 0: The subtree contains nodes [0,1,2,3] with values [1,2,3,4]. 5 is the smallest missing value.
// - 1: The subtree contains only node 1 with value 2. 1 is the smallest missing value.
// - 2: The subtree contains nodes [2,3] with values [3,4]. 1 is the smallest missing value.
// - 3: The subtree contains only node 3 with value 4. 1 is the smallest missing value.
//
// Constraints:
// n == parents.length == nums.length
// 	2 <= n <= 105
// 	0 <= parents[i] <= n - 1 for i != 0
// 	parents[0] == -1
// 	parents represents a valid tree.
// 	1 <= nums[i] <= 105
// 	Each nums[i] is distinct.
//

class Solution {
public:
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = parents.size();
        vector<vector<int>> tree(n);
        for (int i = 1; i < n; ++i) {
            tree[parents[i]].push_back(i);
        }
        
        vector<int> ans(n, 1);
        vector<bool> present(100002, false);
        
        function<void(int)> dfs = [&](int node) {
            present[nums[node]] = true;
            for (int child : tree[node]) {
                dfs(child);
            }
        };
        
        int missing = 1;
        int current = 0;
        
        while (current < n) {
            if (nums[current] == 1) {
                dfs(current);
                while (present[missing]) {
                    ++missing;
                }
            }
            ans[current] = missing;
            ++current;
        }
        
        return ans;         
    }
};
