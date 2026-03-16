// Source: https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/   |   Difficulty: Hard
//
// Problem Description:
// Given n orders, each order consists of a pickup and a delivery service.
//
// Count all valid pickup/delivery possible sequences such that delivery(i) is always after of pickup(i). 
//
// Since the answer may be too large, return it modulo 10^9 + 7.
//
// Example:
// Input: n = 1
// Output: 1
// Explanation: Unique order (P1, D1), Delivery 1 always is after of Pickup 1.
//
// Constraints:
// 1 <= n <= 500
//

/**
 * @param {number} n
 * @return {number}
 */
var countOrders = function(n) {
    const MOD = 1e9 + 7;
    let result = 1;
    for (let i = 1; i <= n; i++) {
        result = (result * i * (2 * i - 1)) % MOD;
    }
    return result;
};
