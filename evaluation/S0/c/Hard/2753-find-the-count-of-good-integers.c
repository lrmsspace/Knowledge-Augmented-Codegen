// Source: https://leetcode.com/problems/find-the-count-of-good-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers n and k.
//
// An integer x is called k-palindromic if:
//
//
// 	x is a palindrome.
// 	x is divisible by k.
//
//
// An integer is called good if its digits can be rearranged to form a k-palindromic integer. For example, for k = 2, 2020 can be rearranged to form the k-palindromic integer 2002, whereas 1010 cannot be rearranged to form a k-palindromic integer.
//
// Return the count of good integers containing n digits.
//
// Note that any integer must not have leading zeros, neither before nor after rearrangement. For example, 1010 cannot be rearranged to form 101.
//
// Example:
// Input: n = 3, k = 5
//
// Output: 27
//
// Explanation:
//
// Some of the good integers are:
//
//
// 	551 because it can be rearranged to form 515.
// 	525 because it is already k-palindromic.
//
// Constraints:
// 1 <= n <= 10
// 	1 <= k <= 9
//

long long countGoodIntegers(int n, int k) {
    int i, j;
    long long dp[11][1024]; /* dp[pos][mask] = count */
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < 1024; j++) {
            int d;
            for (d = 0; d <= 9; d++) {
                if (i == 0 && d == 0) continue; /* leading zero not allowed */
                int newMask = j ^ (1 << d);
                dp[i + 1][newMask] += dp[i][j];
            }
        }
    }
    long long result = 0;
    for (j = 0; j < 1024; j++) {
        int valid = 1;
        int oddCount = 0;
        for (i = 0; i <= 9; i++) {
            if (j & (1 << i)) oddCount++;
        }
        if (n % 2 == 0) {
            if (oddCount != 0) valid = 0;
        } else {
            if (oddCount != 1) valid = 0;
        }
        if (!valid) continue;
        /* Check divisibility by k */
        int sumModK = 0;
        for (i = 0; i <= 9; i++) {
            if (j & (1 << i)) {
                sumModK = (sumModK + i) % k;
            }
        }
        if (sumModK != 0) continue;
        result += dp[n][j];
    }
    return result;      
}
