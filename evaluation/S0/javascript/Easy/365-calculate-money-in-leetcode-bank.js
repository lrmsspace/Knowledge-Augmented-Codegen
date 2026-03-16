// Source: https://leetcode.com/problems/calculate-money-in-leetcode-bank/   |   Difficulty: Easy
//
// Problem Description:
// Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.
//
// He starts by putting in $1 on Monday, the first day. Every day from Tuesday to Sunday, he will put in $1 more than the day before. On every subsequent Monday, he will put in $1 more than the previous Monday. 
//
// Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth day.
//
// Example:
// Input: n = 4
// Output: 10
// Explanation: After the 4th day, the total is 1 + 2 + 3 + 4 = 10.
//
// Constraints:
// 1 <= n <= 1000
//

/**
 * @param {number} n
 * @return {number}
 */
var totalMoney = function(n) {
    let total = 0;
    for (let day = 1; day <= n; day++) {
        const week = Math.floor((day - 1) / 7);
        const dayOfWeek = (day - 1) % 7;
        total += week + dayOfWeek + 1;
    }
    return total;
};
