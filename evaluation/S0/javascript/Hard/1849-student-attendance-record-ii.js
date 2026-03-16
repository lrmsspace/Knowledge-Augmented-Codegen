// Source: https://leetcode.com/problems/student-attendance-record-ii/   |   Difficulty: Hard
//
// Problem Description:
// An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:
//
//
// 	'A': Absent.
// 	'L': Late.
// 	'P': Present.
//
//
// Any student is eligible for an attendance award if they meet both of the following criteria:
//
//
// 	The student was absent ('A') for strictly fewer than 2 days total.
// 	The student was never late ('L') for 3 or more consecutive days.
//
//
// Given an integer n, return the number of possible attendance records of length n that make a student eligible for an attendance award. The answer may be very large, so return it modulo 109 + 7.
//
// Example:
// Input: n = 2
// Output: 8
// Explanation: There are 8 records with length 2 that are eligible for an award:
// "PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
// Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).
//
// Constraints:
// 1 <= n <= 105
//

/**
 * @param {number} n
 * @return {number}
 */
var checkRecord = function(n) {
        const mod = 1e9 + 7;        
        const dp = Array.from({ length: n + 1 }, () => new Array(3).fill(0));   
        dp[0][0] = 1; // Base case: 1 way to have an empty record
        for (let i = 1; i <= n; i++) {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % mod;
            dp[i][1] = dp[i - 1][0] % mod;
            dp[i][2] = dp[i - 1][1] % mod;
        }
        let total = (dp[n][0] + dp[n][1] + dp[n][2]) % mod;
        for (let i = 1; i <= n; i++) {
            total = (total + (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % mod) % mod;
        }
        return total;
            
};
