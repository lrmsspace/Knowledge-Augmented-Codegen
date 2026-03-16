// Source: https://leetcode.com/problems/super-pow/   |   Difficulty: Medium
//
// Problem Description:
// Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.
//
// Example:
// Input: a = 2, b = [3]
// Output: 8
//
// Constraints:
// 1 <= a <= 231 - 1
// 	1 <= b.length <= 2000
// 	0 <= b[i] <= 9
// 	b does not contain leading zeros.
//

/**
 * @param {number} a
 * @param {number[]} b
 * @return {number}
 */
var superPow = function(a, b) {
    const MOD = 1337;

    const modPow = (x, n) => {
        if (n === 0) return 1;
        if (n === 1) return x % MOD;
        const half = modPow(x, Math.floor(n / 2));
        const halfSquared = (half * half) % MOD;
        return n % 2 === 0 ? halfSquared : (halfSquared * x) % MOD;
    };
    let result = 1;
    for (const digit of b) {
        result = (modPow(result, 10) * modPow(a, digit)) % MOD;
    }
    return result;
};  