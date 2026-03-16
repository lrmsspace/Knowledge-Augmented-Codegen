// Source: https://leetcode.com/problems/interleaving-string/   |   Difficulty: Medium
//
// Problem Description:
// Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
//
// An interleaving of two strings s and t is a configuration where s and t are divided into n and m substrings respectively, such that:
//
//
// 	s = s1 + s2 + ... + sn
// 	t = t1 + t2 + ... + tm
// 	|n - m| <= 1
// 	The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
//
//
// Note: a + b is the concatenation of strings a and b.
//
// Example:
// Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
// Output: true
// Explanation: One way to obtain s3 is:
// Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
// Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac".
// Since s3 can be obtained by interleaving s1 and s2, we return true.
//
// Constraints:
// 0 <= s1.length, s2.length <= 100
// 	0 <= s3.length <= 200
// 	s1, s2, and s3 consist of lowercase English letters.
//
//
//  
// Follow up: Could you solve it using only O(s2.length) additional memory space?
//

/**
 * @param {string} s1
 * @param {string} s2
 * @param {string} s3
 * @return {boolean}
 */
var isInterleave = function(s1, s2, s3) {
    const m = s1.length;
    const n = s2.length;
    if (m + n !== s3.length) return false;
    const dp = new Array(n + 1).fill(false);
    dp[0] = true;
    for (let j = 1; j <= n; j++) {
        dp[j] = dp[j - 1] && s2[j - 1] === s3[j - 1];
    }
    for (let i = 1; i <= m; i++) {
        dp[0] = dp[0] && s1[i - 1] === s3[i - 1];
        for (let j = 1; j <= n; j++) {
            dp[j] = (dp[j] && s1[i - 1] === s3[i + j - 1]) || (dp[j - 1] && s2[j - 1] === s3[i + j - 1]);
        }
    }
    return dp[n];
};
