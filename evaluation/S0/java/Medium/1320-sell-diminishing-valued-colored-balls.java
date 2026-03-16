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
    public int maxProfit(int[] inventory, int orders) {
        Arrays.sort(inventory);
        int n = inventory.length;
        long mod = 1_000_000_007;
        long result = 0;
        int index = n - 1;

        while (orders > 0) {
            int currentValue = inventory[index];
            int nextValue = index > 0 ? inventory[index - 1] : 0;
            int count = n - index;

            long totalBalls = (long) count * (currentValue - nextValue);

            if (orders >= totalBalls) {
                result += count * sumOfArithmeticSeries(nextValue + 1, currentValue);
                orders -= totalBalls;
            } else {
                long fullRows = orders / count;
                long remainder = orders % count;

                result += count * sumOfArithmeticSeries(currentValue - fullRows + 1, currentValue);
                result += remainder * (currentValue - fullRows);
                orders = 0;
            }

            result %= mod;
            index--;
        }

        return (int) result;            
    }
}
