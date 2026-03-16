// Source: https://leetcode.com/problems/maximum-and-sum-of-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n and an integer numSlots such that 2 * numSlots >= n. There are numSlots slots numbered from 1 to numSlots.
//
// You have to place all n integers into the slots such that each slot contains at most two numbers. The AND sum of a given placement is the sum of the bitwise AND of every number with its respective slot number.
//
//
// 	For example, the AND sum of placing the numbers [1, 3] into slot 1 and [4, 6] into slot 2 is equal to (1 AND 1) + (3 AND 1) + (4 AND 2) + (6 AND 2) = 1 + 1 + 0 + 2 = 4.
//
//
// Return the maximum possible AND sum of nums given numSlots slots.
//
// Example:
// Input: nums = [1,2,3,4,5,6], numSlots = 3
// Output: 9
// Explanation: One possible placement is [1, 4] into slot 1, [2, 6] into slot 2, and [3, 5] into slot 3. 
// This gives the maximum AND sum of (1 AND 1) + (4 AND 1) + (2 AND 2) + (6 AND 2) + (3 AND 3) + (5 AND 3) = 1 + 0 + 2 + 2 + 3 + 1 = 9.
//
// Constraints:
// n == nums.length
// 	1 <= numSlots <= 9
// 	1 <= n <= 2 * numSlots
// 	1 <= nums[i] <= 15
//

int maximumANDSum(int* nums, int numsSize, int numSlots) {
    int maxState = 1 << (numSlots * 2);
    int *dp = (int*)calloc(maxState, sizeof(int));
    if (!dp) return 0;

    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        for (int state = maxState - 1; state >= 0; --state) {
            if (__builtin_popcount(state) != i) continue; // only consider states with i numbers placed
            for (int slot = 0; slot < numSlots; ++slot) {
                int pos1 = slot * 2;
                int pos2 = slot * 2 + 1;
                if (((state >> pos1) & 1) == 0) {
                    int newState = state | (1 << pos1);
                    int val = dp[state] + (num & (slot + 1));
                    if (val > dp[newState]) dp[newState] = val;
                } else if (((state >> pos2) & 1) == 0) {
                    int newState = state | (1 << pos2);
                    int val = dp[state] + (num & (slot + 1));
                    if (val > dp[newState]) dp[newState] = val;
                }
            }
        }
    }

    int result = dp[maxState - 1];
    free(dp);
    return result;      
}
