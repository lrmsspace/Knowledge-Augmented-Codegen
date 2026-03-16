// Source: https://leetcode.com/problems/maximum-total-reward-using-operations-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array rewardValues of length n, representing the values of rewards.
//
// Initially, your total reward x is 0, and all indices are unmarked. You are allowed to perform the following operation any number of times:
//
//
// 	Choose an unmarked index i from the range [0, n - 1].
// 	If rewardValues[i] is greater than your current total reward x, then add rewardValues[i] to x (i.e., x = x + rewardValues[i]), and mark the index i.
//
//
// Return an integer denoting the maximum total reward you can collect by performing the operations optimally.
//
// Example:
// Input: rewardValues = [1,1,3,3]
//
// Output: 4
//
// Explanation:
//
// During the operations, we can choose to mark the indices 0 and 2 in order, and the total reward will be 4, which is the maximum.
//
// Constraints:
// 1 <= rewardValues.length <= 5 * 104
// 	1 <= rewardValues[i] <= 5 * 104
//

class Solution {
    public int maxTotalReward(int[] rewardValues) {
        Arrays.sort(rewardValues);
        int totalReward = 0;

        for (int reward : rewardValues) {
            if (reward > totalReward) {
                totalReward += reward;
            }
        }

        return totalReward;         
    }
}
