// Source: https://leetcode.com/problems/count-of-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two numeric strings num1 and num2 and two integers max_sum and min_sum. We denote an integer x to be good if:
//
//
// 	num1 <= x <= num2
// 	min_sum <= digit_sum(x) <= max_sum.
//
//
// Return the number of good integers. Since the answer may be large, return it modulo 109 + 7.
//
// Note that digit_sum(x) denotes the sum of the digits of x.
//
// Example:
// Input: num1 = "1", num2 = "12", min_sum = 1, max_sum = 8
// Output: 11
// Explanation: There are 11 integers whose sum of digits lies between 1 and 8 are 1,2,3,4,5,6,7,8,10,11, and 12. Thus, we return 11.
//
// Constraints:
// 1 <= num1 <= num2 <= 1022
// 	1 <= min_sum <= max_sum <= 400
//

int count(char* num1, char* num2, int min_sum, int max_sum) {
    const int MOD = 1000000007;
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int dp[2][len2 + 1][max_sum + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 0; i < len2; i++) {
        int cur = i % 2;
        int next = 1 - cur;
        memset(dp[next], 0, sizeof(dp[next]));
        int limit = num2[i] - '0';
        for (int j = 0; j <= i && j <= len1; j++) {
            for (int s = 0; s <= max_sum; s++) {
                if (dp[cur][j][s] == 0) continue;
                for (int d = 0; d <= limit; d++) {
                    int ns = s + d;
                    if (ns > max_sum) continue;
                    int nj = j + (d == (num1[j] - '0') && j < len1 ? 1 : 0);
                    dp[next][nj][ns] = (dp[next][nj][ns] + dp[cur][j][s]) % MOD;
                }
            }
        }
    }
    int result = 0;
    for (int s = min_sum; s <= max_sum; s++) {
        result = (result + dp[len2 % 2][len1][s]) % MOD;
    }
    return result;      
}
