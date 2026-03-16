// Source: https://leetcode.com/problems/smallest-divisible-digit-product-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num which represents a positive integer, and an integer t.
//
// A number is called zero-free if none of its digits are 0.
//
// Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".
//
// Example:
// Input: num = "1234", t = 256
//
// Output: "1488"
//
// Explanation:
//
// The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.
//
// Constraints:
// 2 <= num.length <= 2 * 105
// 	num consists only of digits in the range ['0', '9'].
// 	num does not contain leading zeros.
// 	1 <= t <= 1014
//

/**
 * @param {string} num
 * @param {number} t
 * @return {string}
 */
var smallestNumber = function(num, t) {
    if (t === 0) return "-1";
    const tFactors = {};
    for (let d = 2; d <= 9; d++) {
        while (t % d === 0) {
            tFactors[d] = (tFactors[d] || 0) + 1;
            t /= d;
        }
    }
    if (t > 1) return "-1";
    const requiredDigits = [];
    for (const [digit, count] of Object.entries(tFactors)) {
        for (let i = 0; i < count; i++) {
            requiredDigits.push(digit);
        }
    }
    requiredDigits.sort((a, b) => a - b);
    const n = num.length;
    const m = requiredDigits.length;
    if (m > n) {
        return requiredDigits.join('') + '1'.repeat(m - n);
    }
    let result = '';
    let used = Array(m).fill(false);
    let found = false;
    function backtrack(pos, isEqual) {
        if (pos === n) {
            found = true;
            return true;
        }
        const startDigit = isEqual ? num[pos] : '1';
        for (let d = startDigit.charCodeAt(0) - '0'.charCodeAt(0); d <= 9; d++) {
            for (let i = 0; i < m; i++) {
                if (!used[i] && requiredDigits[i] == d.toString()) {
                    used[i] = true;
                    result += d.toString();
                    if (backtrack(pos + 1, isEqual && d.toString() === num[pos])) {
                        return true;
                    }
                    result = result.slice(0, -1);
                    used[i] = false;
                }
            }
            if (d > 9) break;
        }
        return false;
    }
    backtrack(0, true);
    if (found) {
        return result;
    } else {
        return "-1";
    }
        
};
