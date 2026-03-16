// Source: https://leetcode.com/problems/greatest-common-divisor-traversal/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums, and you are allowed to traverse between its indices. You can traverse between index i and index j, i != j, if and only if gcd(nums[i], nums[j]) > 1, where gcd is the greatest common divisor.
//
// Your task is to determine if for every pair of indices i and j in nums, where i < j, there exists a sequence of traversals that can take us from i to j.
//
// Return true if it is possible to traverse between all such pairs of indices, or false otherwise.
//
// Example:
// Input: nums = [2,3,6]
// Output: true
// Explanation: In this example, there are 3 possible pairs of indices: (0, 1), (0, 2), and (1, 2).
// To go from index 0 to index 1, we can use the sequence of traversals 0 -> 2 -> 1, where we move from index 0 to index 2 because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1, and then move from index 2 to index 1 because gcd(nums[2], nums[1]) = gcd(6, 3) = 3 > 1.
// To go from index 0 to index 2, we can just go directly because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1. Likewise, to go from index 1 to index 2, we can just go directly because gcd(nums[1], nums[2]) = gcd(3, 6) = 3 > 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
public:
    bool canTraverseAllPairs(vector<int>& nums) {
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
            int px = find(x);
            int py = find(y);
            if (px != py) {
                parent[py] = px;
            }
        };
        
        unordered_map<int, vector<int>> factorMap;
        
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            for (int f = 2; f * f <= num; f++) {
                if (num % f == 0) {
                    factorMap[f].push_back(i);
                    while (num % f == 0) {
                        num /= f;
                    }
                }
            }
            if (num > 1) {
                factorMap[num].push_back(i);
            }
        }
        
        for (const auto& [factor, indices] : factorMap) {
            for (int i = 1; i < indices.size(); i++) {
                unite(indices[0], indices[i]);
            }
        }
        
        int root = find(0);
        for (int i = 1; i < n; i++) {
            if (find(i) != root) {
                return false;
            }
        }
        
        return true;            
    }
};
