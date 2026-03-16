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
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} purchaseAmount
 * @return {number}
 */
var accountBalanceAfterPurchase = function(purchaseAmount) {
    const roundedAmount = Math.round(purchaseAmount / 10) * 10;
    return 100 - roundedAmount; 
};
