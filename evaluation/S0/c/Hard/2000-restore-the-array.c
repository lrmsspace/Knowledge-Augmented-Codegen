// Source: https://leetcode.com/problems/restore-the-array/   |   Difficulty: Hard
//
// Problem Description:
// A program was supposed to print an array of integers. The program forgot to print whitespaces and the array is printed as a string of digits s and all we know is that all integers in the array were in the range [1, k] and there are no leading zeros in the array.
//
// Given the string s and the integer k, return the number of the possible arrays that can be printed as s using the mentioned program. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "1000", k = 10000
// Output: 1
// Explanation: The only possible array is [1000]
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only digits and does not contain leading zeros.
// 	1 <= k <= 109
//

int numberOfArrays(char* s, int k) {
    int n = strlen(s);
    int mod = 1000000007;
    int *dp = (int*)calloc(n + 1, sizeof(int));
    dp[n] = 1; /* base case: one way to decode an empty string */

    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') {
            dp[i] = 0; /* no valid number starts with '0' */
            continue;
        }
        long num = 0;
        for (int j = i; j < n; j++) {
            num = num * 10 + (s[j] - '0');
            if (num > k) break; /* exceed the limit */
            dp[i] = (dp[i] + dp[j + 1]) % mod;
        }
    }

    int result = dp[0];
    free(dp);
    return result;      
}
