// Source: https://leetcode.com/problems/minimum-cost-to-equalize-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers cost1 and cost2. You are allowed to perform either of the following operations any number of times:
//
//
// 	Choose an index i from nums and increase nums[i] by 1 for a cost of cost1.
// 	Choose two different indices i, j, from nums and increase nums[i] and nums[j] by 1 for a cost of cost2.
//
//
// Return the minimum cost required to make all elements in the array equal. 
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [4,1], cost1 = 5, cost2 = 2
//
// Output: 15
//
// Explanation: 
//
// The following operations can be performed to make the values equal:
//
//
// 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,2].
// 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,3].
// 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,4].
//
//
// The total cost is 15.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= cost1 <= 106
// 	1 <= cost2 <= 106
//

class Solution {
public:
    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        long long result = LLONG_MAX;
        
        // Try to equalize all elements to target value from min to max
        int minNum = *min_element(nums.begin(), nums.end());
        int maxNum = *max_element(nums.begin(), nums.end());
        
        for (int target = minNum; target <= maxNum; target++) {
            long long totalCost = 0;
            for (int num : nums) {
                int diff = target - num;
                if (diff <= 0) continue;
                
                // Calculate cost using both operations
                int pairs = diff / 2;
                int singles = diff % 2;
                
                long long costUsingPairs = (long long)pairs * cost2 + (long long)singles * cost1;
                long long costUsingSingles = (long long)diff * cost1;
                
                totalCost += min(costUsingPairs, costUsingSingles);
            }
            result = min(result, totalCost);
        }
        
        return result % MOD;            
    }
};
