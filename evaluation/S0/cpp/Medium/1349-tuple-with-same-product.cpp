// Source: https://leetcode.com/problems/tuple-with-same-product/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of distinct positive integers, return the number of tuples (a, b, c, d) such that a * b = c * d where a, b, c, and d are elements of nums, and a != b != c != d.
//
// Example:
// Input: nums = [2,3,4,6]
// Output: 8
// Explanation: There are 8 valid tuples:
// (2,6,3,4) , (2,6,4,3) , (6,2,3,4) , (6,2,4,3)
// (3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 104
// 	All elements in nums are distinct.
//

class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int, int> productCount;
        int n = nums.size();
        
        // Count the occurrences of each product
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int product = nums[i] * nums[j];
                productCount[product]++;
            }
        }
        
        int result = 0;
        
        // Calculate the number of tuples for each product
        for (const auto& entry : productCount) {
            int count = entry.second;
            if (count > 1) {
                // For each pair of pairs, we can form 8 tuples
                result += count * (count - 1) * 4;
            }
        }
        
        return result;          
    }
};
