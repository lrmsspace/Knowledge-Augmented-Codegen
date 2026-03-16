// Source: https://leetcode.com/problems/find-the-count-of-numbers-which-are-not-special/   |   Difficulty: Medium
//
// Problem Description:
// You are given 2 positive integers l and r. For any number x, all positive divisors of x except x are called the proper divisors of x.
//
// A number is called special if it has exactly 2 proper divisors. For example:
//
//
// 	The number 4 is special because it has proper divisors 1 and 2.
// 	The number 6 is not special because it has proper divisors 1, 2, and 3.
//
//
// Return the count of numbers in the range [l, r] that are not special.
//
// Example:
// Input: l = 5, r = 7
//
// Output: 3
//
// Explanation:
//
// There are no special numbers in the range [5, 7].
//
// Constraints:
// 1 <= l <= r <= 109
//

/**
 * @param {number} l
 * @param {number} r
 * @return {number}
 */
var nonSpecialCount = function(l, r) {
    const isSpecial = (n) => {
        let divisorCount = 0;
        for (let i = 1; i <= Math.sqrt(n); i++) {
            if (n % i === 0) {
                divisorCount++;
                if (i !== n / i) {
                    divisorCount++;
                }
            }
            if (divisorCount > 2) {
                return false;
            }
        }
        return divisorCount === 2;
    }
    let count = 0;
    for (let i = l; i <= r; i++) {
        if (!isSpecial(i)) {
            count++;
        }
    }
    return count;   
};
