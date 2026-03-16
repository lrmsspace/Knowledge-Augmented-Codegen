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

int checkRecord(int n) {
    const int MOD = 1000000007;
    // dp[day][absent_count][late_count]
    long dp[2][2][3];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1; // Day 0, 0 absents, 0 lates

    for (int day = 1; day <= n; day++) {
        int cur = day % 2;
        int prev = (day - 1) % 2;
        memset(dp[cur], 0, sizeof(dp[cur]));

        for (int a = 0; a <= 1; a++) {
            for (int l = 0; l <= 2; l++) {
                long count = dp[prev][a][l];
                if (count == 0) continue;

                // Add 'P'
                dp[cur][a][0] = (dp[cur][a][0] + count) % MOD;

                // Add 'A' if we have less than 1 absence
                if (a < 1) {
                    dp[cur][a + 1][0] = (dp[cur][a + 1][0] + count) % MOD;
                }

                // Add 'L' if we have less than 2 consecutive lates
                if (l < 2) {
                    dp[cur][a][l + 1] = (dp[cur][a][l + 1] + count) % MOD;
                }
            }
        }
    }

    long result = 0;
    int last = n % 2;
    for (int a = 0; a <= 1; a++) {
        for (int l = 0; l <= 2; l++) {
            result = (result + dp[last][a][l]) % MOD;
        }
    }

    return (int)result;     
}
