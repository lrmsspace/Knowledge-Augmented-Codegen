// Source: https://leetcode.com/problems/maximum-ice-cream-bars/   |   Difficulty: Medium
//
// Problem Description:
// It is a sweltering summer day, and a boy wants to buy some ice cream bars.
//
// At the store, there are n ice cream bars. You are given an array costs of length n, where costs[i] is the price of the ith ice cream bar in coins. The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible. 
//
// Note: The boy can buy the ice cream bars in any order.
//
// Return the maximum number of ice cream bars the boy can buy with coins coins.
//
// You must solve the problem by counting sort.
//
// Example:
// Input: costs = [1,3,2,4,1], coins = 7
// Output: 4
// Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.
//
// Constraints:
// costs.length == n
// 	1 <= n <= 105
// 	1 <= costs[i] <= 105
// 	1 <= coins <= 108
//

class Solution {
    public int maxIceCream(int[] costs, int coins) {
        int maxCost = 100000;
        int[] count = new int[maxCost + 1];

        // Count the occurrences of each cost
        for (int cost : costs) {
            count[cost]++;
        }

        int iceCreamBars = 0;

        // Iterate through each possible cost
        for (int cost = 1; cost <= maxCost; cost++) {
            if (count[cost] == 0) {
                continue; // No ice cream bars at this cost
            }

            // Determine how many bars can be bought at this cost
            int maxBarsAtThisCost = Math.min(count[cost], coins / cost);
            iceCreamBars += maxBarsAtThisCost;
            coins -= maxBarsAtThisCost * cost;

            // If we run out of coins, break early
            if (coins < cost) {
                break;
            }
        }

        return iceCreamBars;            
    }
}
