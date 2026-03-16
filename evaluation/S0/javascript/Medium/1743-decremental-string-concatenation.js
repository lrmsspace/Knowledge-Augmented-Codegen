// Source: https://leetcode.com/problems/decremental-string-concatenation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array words containing n strings.
//
// Let's define a join operation join(x, y) between two strings x and y as concatenating them into xy. However, if the last character of x is equal to the first character of y, one of them is deleted.
//
// For example join("ab", "ba") = "aba" and join("ab", "cde") = "abcde".
//
// You are to perform n - 1 join operations. Let str0 = words[0]. Starting from i = 1 up to i = n - 1, for the ith operation, you can do one of the following:
//
//
// 	Make stri = join(stri - 1, words[i])
// 	Make stri = join(words[i], stri - 1)
//
//
// Your task is to minimize the length of strn - 1.
//
// Return an integer denoting the minimum possible length of strn - 1.
//
// Example:
// Input: words = ["aa","ab","bc"]
// Output: 4
// Explanation: In this example, we can perform join operations in the following order to minimize the length of str2: 
// str0 = "aa"
// str1 = join(str0, "ab") = "aab"
// str2 = join(str1, "bc") = "aabc" 
// It can be shown that the minimum possible length of str2 is 4.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 50
// 	Each character in words[i] is an English lowercase letter
//

/**
 * @param {string[]} words
 * @return {number}
 */
var minimizeConcatenatedLength = function(words) {
    const n = words.length;
    const dp = Array.from({ length: n }, () => Array(2).fill(Infinity));    
    dp[0][0] = words[0].length;
    dp[0][1] = words[0].length;
    for (let i = 1; i < n; i++) {
        const len = words[i].length;
        const firstChar = words[i][0];
        const lastChar = words[i][words[i].length - 1];
        for (let prevState = 0; prevState <= 1; prevState++) {
            const prevLastChar = prevState === 0 ? words[i - 1][words[i - 1].length - 1] : words[i - 1][0];
            const cost = (prevLastChar === firstChar) ? len - 1 : len;
            dp[i][0] = Math.min(dp[i][0], dp[i - 1][prevState] + cost);
            const prevFirstChar = prevState === 0 ? words[i - 1][0] : words[i - 1][words[i - 1].length - 1];
            const costReversed = (prevFirstChar === lastChar) ? len - 1 : len;
            dp[i][1] = Math.min(dp[i][1], dp[i - 1][prevState] + costReversed);
        }
    }
    return Math.min(dp[n - 1][0], dp[n - 1][1]);
};
