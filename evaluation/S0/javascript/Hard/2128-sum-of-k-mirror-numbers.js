// Source: https://leetcode.com/problems/sum-of-k-mirror-numbers/   |   Difficulty: Hard
//
// Problem Description:
// A k-mirror number is a positive integer without leading zeros that reads the same both forward and backward in base-10 as well as in base-k.
//
//
// 	For example, 9 is a 2-mirror number. The representation of 9 in base-10 and base-2 are 9 and 1001 respectively, which read the same both forward and backward.
// 	On the contrary, 4 is not a 2-mirror number. The representation of 4 in base-2 is 100, which does not read the same both forward and backward.
//
//
// Given the base k and the number n, return the sum of the n smallest k-mirror numbers.
//
// Example:
// Input: k = 2, n = 5
// Output: 25
// Explanation:
// The 5 smallest 2-mirror numbers and their representations in base-2 are listed as follows:
//   base-10    base-2
//     1          1
//     3          11
//     5          101
//     7          111
//     9          1001
// Their sum = 1 + 3 + 5 + 7 + 9 = 25.
//
// Constraints:
// 2 <= k <= 9
// 	1 <= n <= 30
//

/**
 * @param {number} k
 * @param {number} n
 * @return {number}
 */
var kMirror = function(k, n) {
    const isKMirror = (num) => {
        const strNum = num.toString();
        const reversedStrNum = strNum.split('').reverse().join(''); 
        if (strNum !== reversedStrNum) {
            return false;
        }
        let x = num;
        let baseKStr = '';
        while (x > 0) {
            baseKStr = (x % k).toString() + baseKStr;
            x = Math.floor(x / k);
        }
        const reversedBaseKStr = baseKStr.split('').reverse().join('');
        return baseKStr === reversedBaseKStr;
    }
    const kMirrorNumbers = [];
    let num = 1;
    while (kMirrorNumbers.length < n) {
        if (isKMirror(num)) {
            kMirrorNumbers.push(num);
        }
        num += 1;
    }                                               
    return kMirrorNumbers.reduce((sum, x) => sum + x, 0);   
};
