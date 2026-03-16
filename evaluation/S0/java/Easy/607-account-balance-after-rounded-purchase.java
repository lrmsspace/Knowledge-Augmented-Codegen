// Source: https://leetcode.com/problems/account-balance-after-rounded-purchase/   |   Difficulty: Easy
//
// Problem Description:
// Initially, you have a bank account balance of 100 dollars.
//
// You are given an integer purchaseAmount representing the amount you will spend on a purchase in dollars, in other words, its price.
//
// When making the purchase, first the purchaseAmount is rounded to the nearest multiple of 10. Let us call this value roundedAmount. Then, roundedAmount dollars are removed from your bank account.
//
// Return an integer denoting your final bank account balance after this purchase.
//
// Example:
// Input: purchaseAmount = 9
//
// Output: 90
//
// Explanation:
//
// The nearest multiple of 10 to 9 is 10. So your account balance becomes 100 - 10 = 90.
//
// Constraints:
// 0 <= purchaseAmount <= 100
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int accountBalanceAfterPurchase(int purchaseAmount) {
        int roundedAmount = Math.round(purchaseAmount / 10.0f) * 10;
        return 100 - roundedAmount;         
    }
}
