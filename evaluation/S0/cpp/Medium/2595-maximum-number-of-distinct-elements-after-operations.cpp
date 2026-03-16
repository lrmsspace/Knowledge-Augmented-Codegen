// Source: https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// You are allowed to perform the following operation on each element of the array at most once:
//
//
// 	Add an integer in the range [-k, k] to the element.
//
//
// Return the maximum possible number of distinct elements in nums after performing the operations.
//
// Example:
// Input: nums = [1,2,2,3,3,4], k = 2
//
// Output: 6
//
// Explanation:
//
// nums changes to [-1, 0, 1, 2, 3, 4] after performing operations on the first four elements.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	0 <= k <= 109
//

class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        unordered_set<int> distinctSet;
        
        for (const int& num : nums) {
            if (distinctSet.find(num) == distinctSet.end()) {
                distinctSet.insert(num);
            } else if (k > 0 && distinctSet.find(num - 1) == distinctSet.end()) {
                distinctSet.insert(num - 1);
                k--;
            } else if (k > 0 && distinctSet.find(num + 1) == distinctSet.end()) {
                distinctSet.insert(num + 1);
                k--;
            }
        }
        
        return distinctSet.size();          
    }
};
