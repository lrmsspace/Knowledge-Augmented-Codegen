// Source: https://leetcode.com/problems/find-the-punishment-number-of-an-integer/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, return the punishment number of n.
//
// The punishment number of n is defined as the sum of the squares of all integers i such that:
//
//
// 	1 <= i <= n
// 	The decimal representation of i * i can be partitioned into contiguous substrings such that the sum of the integer values of these substrings equals i.
//
// Example:
// Input: n = 10
// Output: 182
// Explanation: There are exactly 3 integers i in the range [1, 10] that satisfy the conditions in the statement:
// - 1 since 1 * 1 = 1
// - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 and 1 with a sum equal to 8 + 1 == 9.
// - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 and 0 with a sum equal to 10 + 0 == 10.
// Hence, the punishment number of 10 is 1 + 81 + 100 = 182
//
// Constraints:
// 1 <= n <= 1000
//

int punishmentNumber(int n) {
    int result = 0;

    for (int i = 1; i <= n; i++) {
        int square = i * i;
        char str[20];
        sprintf(str, "%d", square);
        int len = strlen(str);

        // DP array to check if we can partition the string to sum up to i
        int dp[len + 1];
        memset(dp, 0, sizeof(dp));
        dp[0] = 1; // Base case: empty string can form sum 0

        for (int j = 1; j <= len; j++) {
            for (int k = j - 1; k >= 0; k--) {
                // Extract substring str[k..j-1]
                char substr[20];
                strncpy(substr, str + k, j - k);
                substr[j - k] = '\0';
                int num = atoi(substr);

                if (num > i) continue;

                if (dp[k] && (i - num) >= 0) {
                    dp[j] = 1;
                    break;
                }
            }
        }

        if (dp[len]) {
            result += square;
        }
    }

    return result;      
}
