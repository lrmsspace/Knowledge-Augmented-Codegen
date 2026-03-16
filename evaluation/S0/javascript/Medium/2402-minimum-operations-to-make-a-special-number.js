// Source: https://leetcode.com/problems/minimum-operations-to-make-a-special-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string num representing a non-negative integer.
//
// In one operation, you can pick any digit of num and delete it. Note that if you delete all the digits of num, num becomes 0.
//
// Return the minimum number of operations required to make num special.
//
// An integer x is considered special if it is divisible by 25.
//
// Example:
// Input: num = "2245047"
// Output: 2
// Explanation: Delete digits num[5] and num[6]. The resulting number is "22450" which is special since it is divisible by 25.
// It can be shown that 2 is the minimum number of operations required to get a special number.
//
// Constraints:
// 1 <= num.length <= 100
// 	num only consists of digits '0' through '9'.
// 	num does not contain any leading zeros.
//

/**
 * @param {string} num
 * @return {number}
 */
var minimumOperations = function(num) {
    const targets = ["00", "25", "50", "75"];
    let minOps = Infinity;
    for (const target of targets) {
        let i = num.length - 1;
        let j = target.length - 1;
        let ops = 0;
        while (i >= 0 && j >= 0) {
            if (num[i] === target[j]) {
                j--;
            } else {
                ops++;
            }
            i--;
        }
        if (j < 0) {
            minOps = Math.min(minOps, ops);
        }
    }
    return minOps === Infinity ? num.length : minOps;
};