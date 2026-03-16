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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int accountBalanceAfterPurchase(int purchaseAmount) {
        int roundedAmount = ((purchaseAmount + 5) / 10) * 10;
        return 100 - roundedAmount;         
    }
};
