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

class Solution {
    public int maximumANDSum(int[] nums, int numSlots) {
        int n = nums.length;
        int maxMask = 1 << (numSlots * 2);
        int[] dp = new int[maxMask];

        for (int mask = 0; mask < maxMask; mask++) {
            int count = Integer.bitCount(mask);
            if (count >= n) continue;

            for (int slot = 0; slot < numSlots; slot++) {
                int slotBit1 = 1 << (slot * 2);
                int slotBit2 = 1 << (slot * 2 + 1);

                if ((mask & slotBit1) == 0) {
                    int newMask = mask | slotBit1;
                    dp[newMask] = Math.max(dp[newMask], dp[mask] + (nums[count] & (slot + 1)));
                } else if ((mask & slotBit2) == 0) {
                    int newMask = mask | slotBit2;
                    dp[newMask] = Math.max(dp[newMask], dp[mask] + (nums[count] & (slot + 1)));
                }
            }
        }

        int result = 0;
        for (int val : dp) {
            result = Math.max(result, val);
        }
        return result;          
    }
}
