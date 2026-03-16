// Source: https://leetcode.com/problems/count-beautiful-numbers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers, l and r. A positive integer is called beautiful if the product of its digits is divisible by the sum of its digits.
//
// Return the count of beautiful numbers between l and r, inclusive.
//
// Example:
// Input: l = 10, r = 20
//
// Output: 2
//
// Explanation:
//
// The beautiful numbers in the range are 10 and 20.
//
// Constraints:
// 1 <= l <= r < 109
//

/**
 * @param {number} l
 * @param {number} r
 * @return {number}
 */
var beautifulNumbers = function(l, r) {
    function countBeautifulUpTo(x) {
        const strX = x.toString();
        const n = strX.length;
        const memo = new Map();
        function dfs(pos, sum, product, isLimit, isNum) {
            if (pos === n) {
                return isNum && product % sum === 0 ? 1 : 0;
            }
            const key = `${pos},${sum},${product},${isLimit},${isNum}`;
            if (memo.has(key)) {
                return memo.get(key);
            }
            let total = 0;
            const limit = isLimit ? parseInt(strX[pos], 10) : 9;
            for (let digit = 0; digit <= limit; digit++) {
                const newIsLimit = isLimit && (digit === limit);
                const newIsNum = isNum || (digit !== 0);
                const newSum = newIsNum ? sum + digit : sum;
                const newProduct = newIsNum ? product * digit : product;
                total += dfs(pos + 1, newSum, newProduct, newIsLimit, newIsNum);
            }
            memo.set(key, total);
            return total;
        }
        return dfs(0, 0, 1, true, false);
    }
    return countBeautifulUpTo(r) - countBeautifulUpTo(l - 1);
};
