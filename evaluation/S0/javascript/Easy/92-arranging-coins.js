// Source: https://leetcode.com/problems/arranging-coins/   |   Difficulty: Easy
//
// Problem Description:
// You have n coins and you want to build a staircase with these coins. The staircase consists of k rows where the ith row has exactly i coins. The last row of the staircase may be incomplete.
//
// Given the integer n, return the number of complete rows of the staircase you will build.
//
// Example:
// Input: n = 5
// Output: 2
// Explanation: Because the 3rd row is incomplete, we return 2.
//
// Constraints:
// 1 <= n <= 231 - 1
//

/**
 * @param {number} n
 * @return {number}
 */
var arrangeCoins = function(n) {
    let left = 0;
    let right = n;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        const coins = (mid * (mid + 1)) / 2;
        if (coins === n) {
            return mid;
        } else if (coins < n) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
};