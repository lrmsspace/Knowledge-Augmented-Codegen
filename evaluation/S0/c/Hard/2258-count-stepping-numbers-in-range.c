// Source: https://leetcode.com/problems/count-stepping-numbers-in-range/   |   Difficulty: Hard
//
// Problem Description:
// Given two positive integers low and high represented as strings, find the count of stepping numbers in the inclusive range [low, high].
//
// A stepping number is an integer such that all of its adjacent digits have an absolute difference of exactly 1.
//
// Return an integer denoting the count of stepping numbers in the inclusive range [low, high]. 
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Note: A stepping number should not have a leading zero.
//
// Example:
// Input: low = "1", high = "11"
// Output: 10
// Explanation: The stepping numbers in the range [1,11] are 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10. There are a total of 10 stepping numbers in the range. Hence, the output is 10.
//
// Constraints:
// 1 <= int(low) <= int(high) < 10100
// 	1 <= low.length, high.length <= 100
// 	low and high consist of only digits.
// 	low and high don't have any leading zeros.
//

int countSteppingNumbers(char* low, char* high) {
    const int MOD = 1000000007;

    int dp[101][10][2][2] = {0}; // length, last_digit, is_tight, is_leading_zero
    int len_low = strlen(low);
    int len_high = strlen(high);

    int countSteppingUpTo(char* num) {
        int len = strlen(num);
        memset(dp, 0, sizeof(dp));
        dp[0][0][1][1] = 1; // Starting point

        for (int i = 0; i < len; ++i) {
            for (int last_digit = 0; last_digit <= 9; ++last_digit) {
                for (int is_tight = 0; is_tight <= 1; ++is_tight) {
                    for (int is_leading_zero = 0; is_leading_zero <= 1; ++is_leading_zero) {
                        int limit = is_tight ? (num[i] - '0') : 9;
                        for (int digit = 0; digit <= limit; ++digit) {
                            if (is_leading_zero && digit == 0) {
                                dp[i + 1][digit][is_tight && (digit == limit)][1] =
                                    (dp[i + 1][digit][is_tight && (digit == limit)][1] + dp[i][last_digit][is_tight][is_leading_zero]) % MOD;
                            } else {
                                if (is_leading_zero || abs(digit - last_digit) == 1) {
                                    dp[i + 1][digit][is_tight && (digit == limit)][0] =
                                        (dp[i + 1][digit][is_tight && (digit == limit)][0] + dp[i][last_digit][is_tight][is_leading_zero]) % MOD;
                                }
                            }
                        }
                    }
                }
            }
        }

        int total = 0;
        for (int last_digit = 0; last_digit <= 9; ++last_digit) {
            for (int is_tight = 0; is_tight <= 1; ++is_tight) {
                total = (total + dp[len][last_digit][is_tight][0]) % MOD;
            }
        }
        return total;
    }

    int count_low = countSteppingUpTo(low);
    int count_high = countSteppingUpTo(high);
    int result = (count_high - count_low + MOD) % MOD;
    // Check if low itself is a stepping number
    int is_stepping = 1;
    for (int i = 1; i < len_low; ++i) {
        if (abs(low[i] - low[i - 1]) != 1) {
            is_stepping = 0;
            break;
        }
    }
    if (is_stepping) {
        result = (result + 1) % MOD;
    }
    return result;
}
