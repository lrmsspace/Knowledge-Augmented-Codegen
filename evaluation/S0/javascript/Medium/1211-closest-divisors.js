// Source: https://leetcode.com/problems/closest-divisors/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer num, find the closest two integers in absolute difference whose product equals num + 1 or num + 2.
//
// Return the two integers in any order.
//
// Example:
// Input: num = 8
// Output: [3,3]
// Explanation: For num + 1 = 9, the closest divisors are 3 & 3, for num + 2 = 10, the closest divisors are 2 & 5, hence 3 & 3 is chosen.
//
// Constraints:
// 1 <= num <= 10^9
//

/**
 * @param {number} num
 * @return {number[]}
 */
var closestDivisors = function(num) {
    function findClosestDivisors(n) {
        let sqrtN = Math.floor(Math.sqrt(n));
        for (let i = sqrtN; i >= 1; i--) {
            if (n % i === 0) {
                return [i, n / i];
            }
        }
    }
    const divisors1 = findClosestDivisors(num + 1);
    const divisors2 = findClosestDivisors(num + 2);
    return Math.abs(divisors1[0] - divisors1[1]) <= Math.abs(divisors2[0] - divisors2[1]) ? divisors1 : divisors2;  
};
