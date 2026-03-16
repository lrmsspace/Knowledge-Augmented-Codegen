// Source: https://leetcode.com/problems/minimum-array-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and three integers k, op1, and op2.
//
// You can perform the following operations on nums:
//
//
// 	Operation 1: Choose an index i and divide nums[i] by 2, rounding up to the nearest whole number. You can perform this operation at most op1 times, and not more than once per index.
// 	Operation 2: Choose an index i and subtract k from nums[i], but only if nums[i] is greater than or equal to k. You can perform this operation at most op2 times, and not more than once per index.
//
//
// Note: Both operations can be applied to the same index, but at most once each.
//
// Return the minimum possible sum of all elements in nums after performing any number of operations.
//
// Example:
// Input: nums = [2,8,3,19,3], k = 3, op1 = 1, op2 = 1
//
// Output: 23
//
// Explanation:
//
//
// 	Apply Operation 2 to nums[1] = 8, making nums[1] = 5.
// 	Apply Operation 1 to nums[3] = 19, making nums[3] = 10.
// 	The resulting array becomes [2, 5, 3, 10, 3], which has the minimum possible sum of 23 after applying the operations.
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 105
// 	0 <= k <= 105
// 	0 <= op1, op2 <= nums.length
//

class Solution {
public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        vector<int> deltas;
        for (int num : nums) {
            int afterOp1 = (num + 1) / 2;
            int afterOp2 = (num >= k) ? (num - k) : num;
            int deltaOp1 = num - afterOp1;
            int deltaOp2 = num - afterOp2;
            int bestDelta = max(deltaOp1, deltaOp2);
            deltas.push_back(bestDelta);
        }

        sort(deltas.begin(), deltas.end(), greater<int>());

        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        int operations = min(op1 + op2, static_cast<int>(nums.size()));
        for (int i = 0; i < operations; ++i) {
            totalSum -= deltas[i];
        }

        return totalSum;            
    }
};
