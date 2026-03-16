// Source: https://leetcode.com/problems/decode-ways-ii/   |   Difficulty: Hard
//
// Problem Description:
// A message containing letters from A-Z can be encoded into numbers using the following mapping:
//
//
// 'A' -> "1"
// 'B' -> "2"
// ...
// 'Z' -> "26"
//
//
// To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped into:
//
//
// 	"AAJF" with the grouping (1 1 10 6)
// 	"KJF" with the grouping (11 10 6)
//
//
// Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is different from "06".
//
// In addition to the mapping above, an encoded message may contain the '*' character, which can represent any digit from '1' to '9' ('0' is excluded). For example, the encoded message "1*" may represent any of the encoded messages "11", "12", "13", "14", "15", "16", "17", "18", or "19". Decoding "1*" is equivalent to decoding any of the encoded messages it can represent.
//
// Given a string s consisting of digits and '*' characters, return the number of ways to decode it.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "*"
// Output: 9
// Explanation: The encoded message can represent any of the encoded messages "1", "2", "3", "4", "5", "6", "7", "8", or "9".
// Each of these can be decoded to the strings "A", "B", "C", "D", "E", "F", "G", "H", and "I" respectively.
// Hence, there are a total of 9 ways to decode "*".
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is a digit or '*'.
//

/**
 * @param {string} s
 * @return {number}
 */
var numDecodings = function(s) {
    


    const MOD = 1e9 + 7;
    const n = s.length;
    const dp = new Array(n + 1).fill(0);
    dp[0] = 1; // Base case: there's one way to decode an empty string

    for (let i = 1; i <= n; i++) {
        const currentChar = s[i - 1];
        // Single character decoding
        if (currentChar === '*') {
            dp[i] = (dp[i] + 9 * dp[i - 1]) % MOD; // '*' can represent '1' to '9'
        } else if (currentChar !== '0') {
            dp[i] = (dp[i] + dp[i - 1]) % MOD; // Valid single digit
        }
        // Two character decoding
        if (i > 1) {
            const prevChar = s[i - 2];
            if (prevChar === '1') {
                if (currentChar === '*') {
                    dp[i] = (dp[i] + 9 * dp[i - 2]) % MOD; // '1*' can represent '11' to '19'
                } else {
                    dp[i] = (dp[i] + dp[i - 2]) % MOD; // '1' followed by a valid digit
                }
            } else if (prevChar === '2') {
                if (currentChar === '*') {
                    dp[i] = (dp[i] + 6 * dp[i - 2]) % MOD; // '2*' can represent '21' to '26'
                } else if (currentChar >= '0' && currentChar <= '6') {
                    dp[i] = (dp[i] + dp[i - 2]) % MOD; // '2' followed by a valid digit
       
            }     } else if (prevChar === '*') {
                if (currentChar === '*') {
                    dp[i] = (dp[i] + 15 * dp[i - 2]) % MOD; // '**' can represent '11' to '19' and '21' to '26'
                } else if (currentChar >= '0' && currentChar <= '6') {
                    dp[i] = (dp[i] + 2 * dp[i - 2]) % MOD; // '*' can represent '1' or '2'
                } else {
                    dp[i] = (dp[i] + dp[i - 2]) % MOD; // '*' can represent '1'
                }
            }
        }
    }
    return dp[n];   

};
