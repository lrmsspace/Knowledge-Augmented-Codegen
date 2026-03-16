// Source: https://leetcode.com/problems/sell-diminishing-valued-colored-balls/   |   Difficulty: Medium
//
// Problem Description:
// You have an inventory of different colored balls, and there is a customer that wants orders balls of any color.
//
// The customer weirdly values the colored balls. Each colored ball's value is the number of balls of that color you currently have in your inventory. For example, if you own 6 yellow balls, the customer would pay 6 for the first yellow ball. After the transaction, there are only 5 yellow balls left, so the next yellow ball is then valued at 5 (i.e., the value of the balls decreases as you sell more to the customer).
//
// You are given an integer array, inventory, where inventory[i] represents the number of balls of the ith color that you initially own. You are also given an integer orders, which represents the total number of balls that the customer wants. You can sell the balls in any order.
//
// Return the maximum total value that you can attain after selling orders colored balls. As the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: inventory = [2,5], orders = 4
// Output: 14
// Explanation: Sell the 1st color 1 time (2) and the 2nd color 3 times (5 + 4 + 3).
// The maximum total value is 2 + 5 + 4 + 3 = 14.
//
// Constraints:
// 1 <= inventory.length <= 105
// 	1 <= inventory[i] <= 109
// 	1 <= orders <= min(sum(inventory[i]), 109)
//

class Solution {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        const int MOD = 1e9 + 7;
        sort(inventory.rbegin(), inventory.rend());
        inventory.push_back(0); // Sentinel

        long long result = 0;
        int n = inventory.size();
        for (int i = 0; i < n - 1 && orders > 0; ++i) {
            int count = i + 1;
            int heightDiff = inventory[i] - inventory[i + 1];

            long long totalBalls = (long long)count * heightDiff;
            if (totalBalls <= orders) {
                // Sell all balls from inventory[i] down to inventory[i + 1] + 1
                long long sellFrom = inventory[i];
                long long sellTo = inventory[i + 1] + 1;
                long long profit = count * (sellFrom + sellTo) * heightDiff / 2;
                result = (result + profit) % MOD;
                orders -= totalBalls;
            } else {
                // Sell only a portion of the balls
                long long fullRows = orders / count;
                long long remainder = orders % count;

                long long sellFrom = inventory[i];
                long long sellTo = inventory[i] - fullRows + 1;
                long long profit = count * (sellFrom + sellTo) * fullRows / 2;
                result = (result + profit) % MOD;

                // Sell the remainder
                sellFrom = inventory[i] - fullRows;
                profit = remainder * sellFrom;
                result = (result + profit) % MOD;

                orders = 0; // All orders fulfilled
            }
        }

        return result;          
    }
};
