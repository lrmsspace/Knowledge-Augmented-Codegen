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

class Solution {
public:
    int checkRecord(int n) {
        const int MOD = 1e9 + 7;
        // dp[length][A_count][L_consecutive]
        long long dp[n + 1][2][3];
        memset(dp, 0, sizeof(dp));
        
        dp[0][0][0] = 1;  // base case: empty record
        
        for (int len = 1; len <= n; len++) {
            for (int A = 0; A <= 1; A++) {
                for (int L = 0; L <= 2; L++) {
                    // Add 'P'
                    dp[len][A][0] = (dp[len][A][0] + dp[len - 1][A][L]) % MOD;
                    
                    // Add 'A'
                    if (A == 0) {
                        dp[len][1][0] = (dp[len][1][0] + dp[len - 1][0][L]) % MOD;
                    }
                    
                    // Add 'L'
                    if (L < 2) {
                        dp[len][A][L + 1] = (dp[len][A][L + 1] + dp[len - 1][A][L]) % MOD;
                    }
                }
            }
        }
        
        long long result = 0;
        for (int A = 0; A <= 1; A++) {
            for (int L = 0; L <= 2; L++) {
                result = (result + dp[n][A][L]) % MOD;
            }
        }
        
        return (int)result;         
    }
};
