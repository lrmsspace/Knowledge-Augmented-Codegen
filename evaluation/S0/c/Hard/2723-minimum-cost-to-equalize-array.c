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

int minCostToEqualizeArray(int* nums, int numsSize, int cost1, int cost2) {
    const int MOD = 1000000007;
    long long res = 0;
    int max = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > max) max = nums[i];
    }
    for (int target = max; target <= max + 1; ++target) {
        long long curr = 0;
        for (int i = 0; i < numsSize; ++i) {
            int diff = target - nums[i];
            if (cost2 < 2 * cost1) {
                curr += (diff / 2) * cost2 + (diff % 2) * cost1;
            } else {
                curr += diff * cost1;
            }
        }
        if (res == 0 || curr < res) res = curr;
    }
    return (int)(res % MOD);        
}
