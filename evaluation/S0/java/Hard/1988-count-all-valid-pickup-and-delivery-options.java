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

class Solution {
    public int countOrders(int n) {
        long mod = 1_000_000_007;
        long result = 1;

        for (int i = 1; i <= n; i++) {
            result = (result * i) % mod; // ways to arrange pickups
            result = (result * (2 * i - 1)) % mod; // ways to arrange deliveries
        }

        return (int) result;                    
    }
}
