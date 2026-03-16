// Source: https://leetcode.com/problems/next-greater-numerically-balanced-number/   |   Difficulty: Medium
//
// Problem Description:
// An integer x is numerically balanced if for every digit d in the number x, there are exactly d occurrences of that digit in x.
//
// Given an integer n, return the smallest numerically balanced number strictly greater than n.
//
// Example:
// Input: n = 1
// Output: 22
// Explanation: 
// 22 is numerically balanced since:
// - The digit 2 occurs 2 times. 
// It is also the smallest numerically balanced number strictly greater than 1.
//
// Constraints:
// 0 <= n <= 106
//

/**
 * @param {number} n
 * @return {number}
 */
var nextBeautifulNumber = function(n) {
    const isBalanced = (num) => {
        const count = Array(10).fill(0);    
        while (num > 0) {
            const digit = num % 10;
            count[digit]++;
            num = Math.floor(num / 10);
        }
        for (let d = 1; d <= 9; d++) {
            if (count[d] !== 0 && count[d] !== d) {
                return false;
            }
        }
        return true;
    }
    let candidate = n + 1;
    while (true) {
        if (isBalanced(candidate)) {
            return candidate;
        }
        candidate++;
    }   
    
};
