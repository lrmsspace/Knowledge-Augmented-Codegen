// Source: https://leetcode.com/problems/minimum-number-of-coins-for-fruits/   |   Difficulty: Medium
//
// Problem Description:
// You are given an 0-indexed integer array prices where prices[i] denotes the number of coins needed to purchase the (i + 1)th fruit.
//
// The fruit market has the following reward for each fruit:
//
//
// 	If you purchase the (i + 1)th fruit at prices[i] coins, you can get any number of the next i fruits for free.
//
//
// Note that even if you can take fruit j for free, you can still purchase it for prices[j - 1] coins to receive its reward.
//
// Return the minimum number of coins needed to acquire all the fruits.
//
// Example:
// Input: prices = [3,1,2]
//
// Output: 4
//
// Explanation:
//
//
// 	Purchase the 1st fruit with prices[0] = 3 coins, you are allowed to take the 2nd fruit for free.
// 	Purchase the 2nd fruit with prices[1] = 1 coin, you are allowed to take the 3rd fruit for free.
// 	Take the 3rd fruit for free.
//
//
// Note that even though you could take the 2nd fruit for free as a reward of buying 1st fruit, you purchase it to receive its reward, which is more optimal.
//
// Constraints:
// 1 <= prices.length <= 1000
// 	1 <= prices[i] <= 105
//

class Solution {
    public int minimumCoins(int[] prices) {
        int n = prices.length;
        boolean[] taken = new boolean[n];
        int coins = 0;

        for (int i = 0; i < n; i++) {
            if (taken[i]) {
                continue;
            }

            coins += prices[i];

            for (int j = 1; j <= i && i + j < n; j++) {
                taken[i + j] = true;
            }
        }

        return coins;           
    }
}
