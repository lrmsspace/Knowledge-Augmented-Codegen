// Source: https://leetcode.com/problems/find-palindrome-with-fixed-length/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array queries and a positive integer intLength, return an array answer where answer[i] is either the queries[i]th smallest positive palindrome of length intLength or -1 if no such palindrome exists.
//
// A palindrome is a number that reads the same backwards and forwards. Palindromes cannot have leading zeros.
//
// Example:
// Input: queries = [1,2,3,4,5,90], intLength = 3
// Output: [101,111,121,131,141,999]
// Explanation:
// The first few palindromes of length 3 are:
// 101, 111, 121, 131, 141, 151, 161, 171, 181, 191, 202, ...
// The 90th palindrome of length 3 is 999.
//
// Constraints:
// 1 <= queries.length <= 5 * 104
// 	1 <= queries[i] <= 109
// 	1 <= intLength <= 15
//

/**
 * @param {number[]} queries
 * @param {number} intLength
 * @return {number[]}
 */
var kthPalindrome = function(queries, intLength) {
    const results = [];
    const halfLength = Math.floor((intLength + 1) / 2);
    const start = 10 ** (halfLength - 1);
    const end = 10 ** halfLength - 1;
    for (const q of queries) {
        const halfNum = start + q - 1;
        if (halfNum > end) {
            results.push(-1);
            continue;
        }
        let halfStr = halfNum.toString();
        let revStr = halfStr.split('').reverse().join('');
        if (intLength % 2 === 1) {
            revStr = revStr.slice(1);
        }
        const palindromeStr = halfStr + revStr;
        results.push(Number(palindromeStr));
    }   
    return results;
};
