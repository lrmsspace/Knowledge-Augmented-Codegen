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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int accountBalanceAfterPurchase(int purchaseAmount) {
    int roundedAmount;
    int remainder = purchaseAmount % 10;

    if (remainder < 5) {
        roundedAmount = purchaseAmount - remainder;
    } else {
        roundedAmount = purchaseAmount + (10 - remainder);
    }

    return 100 - roundedAmount;     
}
