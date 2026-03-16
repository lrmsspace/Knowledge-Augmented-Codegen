// Source: https://leetcode.com/problems/count-beautiful-numbers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers, l and r. A positive integer is called beautiful if the product of its digits is divisible by the sum of its digits.
//
// Return the count of beautiful numbers between l and r, inclusive.
//
// Example:
// Input: l = 10, r = 20
//
// Output: 2
//
// Explanation:
//
// The beautiful numbers in the range are 10 and 20.
//
// Constraints:
// 1 <= l <= r < 109
//

int beautifulNumbers(int l, int r) {
    int dp[20][2][82][730]; // pos, tight, sum, product
    memset(dp, 0, sizeof(dp));
    int digits[20];
    int len = 0;
    for (long long x = r; x > 0; x /= 10) {
        digits[len++] = x % 10;
    }
    dp[0][1][0][1] = 1;
    for (int pos = 0; pos < len; pos++) {
        for (int tight = 0; tight <= 1; tight++) {
            for (int sum = 0; sum <= 81; sum++) {
                for (int product = 1; product <= 729; product++) {
                    if (dp[pos][tight][sum][product] == 0) continue;
                    int limit = tight ? digits[len - 1 - pos] : 9;
                    for (int dig = 0; dig <= limit; dig++) {
                        int newTight = (tight && (dig == limit)) ? 1 : 0;
                        int newSum = sum + dig;
                        int newProduct = product * (dig == 0 ? 1 : dig);
                        dp[pos + 1][newTight][newSum][newProduct] += dp[pos][tight][sum][product];
                    }
                }
            }
        }
    }
    int resultR = 0;
    for (int sum = 1; sum <= 81; sum++) {
        for (int product = 1; product <= 729; product++) {
            if (product % sum == 0) {
                resultR += dp[len][0][sum][product];
                resultR += dp[len][1][sum][product];
            }
        }
    }

    // Repeat the same process for l-1
    memset(dp, 0, sizeof(dp));
    len = 0;
    for (long long x = l - 1; x > 0; x /= 10) {
        digits[len++] = x % 10;
    }
    dp[0][1][0][1] = 1;
    for (int pos = 0; pos < len; pos++) {
        for (int tight = 0; tight <= 1; tight++) {
            for (int sum = 0; sum <= 81; sum++) {
                for (int product = 1; product <= 729; product++) {
                    if (dp[pos][tight][sum][product] == 0) continue;
                    int limit = tight ? digits[len - 1 - pos] : 9;
                    for (int dig = 0; dig <= limit; dig++) {
                        int newTight = (tight && (dig == limit)) ? 1 : 0;
                        int newSum = sum + dig;
                        int newProduct = product * (dig == 0 ? 1 : dig);
                        dp[pos + 1][newTight][newSum][newProduct] += dp[pos][tight][sum][product];
                    }
                }
            }
        }
    }
    int resultL = 0;
    for (int sum = 1; sum <= 81; sum++) {
        for (int product = 1; product <= 729; product++) {
            if (product % sum == 0) {
                resultL += dp[len][0][sum][product];
                resultL += dp[len][1][sum][product];
            }
        }
    }
    return resultR - resultL;
}
