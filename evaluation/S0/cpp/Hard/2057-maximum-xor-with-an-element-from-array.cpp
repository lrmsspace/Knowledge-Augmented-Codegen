// Source: https://leetcode.com/problems/maximum-xor-with-an-element-from-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].
//
// The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.
//
// Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.
//
// Example:
// Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
// Output: [3,3,7]
// Explanation:
// 1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
// 2) 1 XOR 2 = 3.
// 3) 5 XOR 2 = 7.
//
// Constraints:
// 1 <= nums.length, queries.length <= 105
// 	queries[i].length == 2
// 	0 <= nums[j], xi, mi <= 109
//

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        struct TrieNode {
            TrieNode* children[2];
            TrieNode() {
                children[0] = nullptr;
                children[1] = nullptr;
            }
        };
        
        auto insert = [](TrieNode* root, int num) {
            TrieNode* node = root;
            for (int i = 31; i >= 0; --i) {
                int bit = (num >> i) & 1;
                if (!node->children[bit]) {
                    node->children[bit] = new TrieNode();
                }
                node = node->children[bit];
            }
        };
        
        auto getMaxXor = [](TrieNode* root, int num) {
            TrieNode* node = root;
            int maxXor = 0;
            for (int i = 31; i >= 0; --i) {
                int bit = (num >> i) & 1;
                int toggledBit = 1 - bit;
                if (node->children[toggledBit]) {
                    maxXor |= (1 << i);
                    node = node->children[toggledBit];
                } else if (node->children[bit]) {
                    node = node->children[bit];
                } else {
                    return -1;
                }
            }
            return maxXor;
        };
        
        sort(nums.begin(), nums.end());
        int qSize = queries.size();
        vector<int> result(qSize, -1);
        vector<tuple<int, int, int>> sortedQueries; // (mi, xi, index)
        
        for (int i = 0; i < qSize; ++i) {
            sortedQueries.emplace_back(queries[i][1], queries[i][0], i);
        }
        
        sort(sortedQueries.begin(), sortedQueries.end());
        
        TrieNode* root = new TrieNode();
        int idx = 0;
        int nSize = nums.size();
        
        for (const auto& [mi, xi, qIdx] : sortedQueries) {
            while (idx < nSize && nums[idx] <= mi) {
                insert(root, nums[idx]);
                ++idx;
            }
            if (idx > 0) { // At least one number <= mi
                result[qIdx] = getMaxXor(root, xi);
            } else {
                result[qIdx] = -1;
            }
        }  
        return result;         
    }
};
