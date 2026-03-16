// Source: https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of lowercase English letters, an integer t representing the number of transformations to perform, and an array nums of size 26. In one transformation, every character in s is replaced according to the following rules:
//
//
// 	Replace s[i] with the next nums[s[i] - 'a'] consecutive characters in the alphabet. For example, if s[i] = 'a' and nums[0] = 3, the character 'a' transforms into the next 3 consecutive characters ahead of it, which results in "bcd".
// 	The transformation wraps around the alphabet if it exceeds 'z'. For example, if s[i] = 'y' and nums[24] = 3, the character 'y' transforms into the next 3 consecutive characters ahead of it, which results in "zab".
//
//
// Return the length of the resulting string after exactly t transformations.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "abcyy", t = 2, nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
//
// Output: 7
//
// Explanation:
//
//
// 	
// 	First Transformation (t = 1):
//
// 	
// 		'a' becomes 'b' as nums[0] == 1
// 		'b' becomes 'c' as nums[1] == 1
// 		'c' becomes 'd' as nums[2] == 1
// 		'y' becomes 'z' as nums[24] == 1
// 		'y' becomes 'z' as nums[24] == 1
// 		String after the first transformation: "bcdzz"
// 	
// 	
// 	
// 	Second Transformation (t = 2):
//
// 	
// 		'b' becomes 'c' as nums[1] == 1
// 		'c' becomes 'd' as nums[2] == 1
// 		'd' becomes 'e' as nums[3] == 1
// 		'z' becomes 'ab' as nums[25] == 2
// 		'z' becomes 'ab' as nums[25] == 2
// 		String after the second transformation: "cdeabab"
// 	
// 	
// 	
// 	Final Length of the string: The string is "cdeabab", which has 7 characters.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
// 	1 <= t <= 109
// 	nums.length == 26
// 	1 <= nums[i] <= 25
//

/**
 * @param {string} s
 * @param {number} t
 * @param {number[]} nums
 * @return {number}
 */
var lengthAfterTransformations = function(s, t, nums) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: t + 1 }, () => Array(26).fill(0));
    for (let c = 0; c < 26; c++) {
        dp[0][c] = 1;
    }
    for (let step = 1; step <= t; step++) {                                 
        for (let c = 0; c < 26; c++) {
            let total = 0;
            const nextCharsCount = nums[c];
            for (let k = 1; k <= nextCharsCount; k++) {
                const nextChar = (c + k) % 26;
                total = (total + dp[step - 1][nextChar]) % MOD;
            }
            dp[step][c] = total;
        }
    }
    let result = 0;
    for (const char of s) {
        const c = char.charCodeAt(0) - 'a'.charCodeAt(0);
        result = (result + dp[t][c]) % MOD;
    }
    return result;  
};
