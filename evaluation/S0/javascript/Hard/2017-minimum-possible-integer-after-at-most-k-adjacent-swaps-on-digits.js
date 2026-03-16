// Source: https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num representing the digits of a very large integer and an integer k. You are allowed to swap any two adjacent digits of the integer at most k times.
//
// Return the minimum integer you can obtain also as a string.
//
// Example:
// Input: num = "4321", k = 4
// Output: "1342"
// Explanation: The steps to obtain the minimum integer from 4321 with 4 adjacent swaps are shown.
//
// Constraints:
// 1 <= num.length <= 3 * 104
// 	num consists of only digits and does not contain leading zeros.
// 	1 <= k <= 109
//

/**
 * @param {string} num
 * @param {number} k
 * @return {string}
 */
var minInteger = function(num, k) {
    const n = num.length;
    const pos = Array.from({ length: 10 }, () => []);
    for (let i = 0; i < n; i++) {
        pos[num.charCodeAt(i) - 48].push(i);
    }
    const bit = new FenwickTree(n);
    let result = '';
    for (let i = 0; i < n; i++) {
        for (let d = 0; d < 10; d++) {
            if (pos[d].length > 0) {
                const idx = pos[d][0];
                const swapsNeeded = idx + bit.query(idx) - i;   
                if (swapsNeeded <= k) {
                    k -= swapsNeeded;
                    result += String.fromCharCode(d + 48);
                    bit.update(idx, 1);
                    pos[d].shift();
                    break;
                }
            }
        }
    }
    return result;
        

};
