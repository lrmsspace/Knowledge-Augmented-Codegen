// Source: https://leetcode.com/problems/digit-operations-to-make-two-integers-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers n and m that consist of the same number of digits.
//
// You can perform the following operations any number of times:
//
//
// 	Choose any digit from n that is not 9 and increase it by 1.
// 	Choose any digit from n that is not 0 and decrease it by 1.
//
//
// The integer n must not be a prime number at any point, including its original value and after each operation.
//
// The cost of a transformation is the sum of all values that n takes throughout the operations performed.
//
// Return the minimum cost to transform n into m. If it is impossible, return -1.
//
// Example:
// Input: n = 10, m = 12
//
// Output: 85
//
// Explanation:
//
// We perform the following operations:
//
//
// 	Increase the first digit, now n = 20.
// 	Increase the second digit, now n = 21.
// 	Increase the second digit, now n = 22.
// 	Decrease the first digit, now n = 12.
//
// Constraints:
// 1 <= n, m < 104
// 	n and m consist of the same number of digits.
//

/**
 * @param {number} n
 * @param {number} m
 * @return {number}
 */
var minOperations = function(n, m) {
    const isPrime = (num) => {
        if (num <= 1) return false;
        for (let i = 2; i <= Math.sqrt(num); i++) {
            if (num % i === 0) return false;
        }
        return true;
    };
    
    const nStr = n.toString();
    const mStr = m.toString();
    let totalCost = n;
    for (let i = 0; i < nStr.length; i++) {
        const digitN = parseInt(nStr[i]);
        const digitM = parseInt(mStr[i]);
        if (digitN < digitM) {
            for (let d = digitN; d <= digitM; d++) {
                const newNum = parseInt(nStr.slice(0, i) + d + nStr.slice(i + 1));
                if (isPrime(newNum)) return -1;
                totalCost += newNum;
            }
        } else if (digitN > digitM) {
            for (let d = digitN; d >= digitM; d--) {
                const newNum = parseInt(nStr.slice(0, i) + d + nStr.slice(i + 1));
                if (isPrime(newNum)) return -1;
                totalCost += newNum;
            }
        }
    }   
    return totalCost;   
};
