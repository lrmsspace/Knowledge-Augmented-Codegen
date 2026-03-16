// Source: https://leetcode.com/problems/count-numbers-with-non-decreasing-digits/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers, l and r, represented as strings, and an integer b. Return the count of integers in the inclusive range [l, r] whose digits are in non-decreasing order when represented in base b.
//
// An integer is considered to have non-decreasing digits if, when read from left to right (from the most significant digit to the least significant digit), each digit is greater than or equal to the previous one.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: l = "23", r = "28", b = 8
//
// Output: 3
//
// Explanation:
//
//
// 	The numbers from 23 to 28 in base 8 are: 27, 30, 31, 32, 33, and 34.
// 	Out of these, 27, 33, and 34 have non-decreasing digits. Hence, the output is 3.
//
// Constraints:
// 1 <= l.length <= r.length <= 100
// 	2 <= b <= 10
// 	l and r consist only of digits.
// 	The value represented by l is less than or equal to the value represented by r.
// 	l and r do not contain leading zeros.
//

int countNumbers(char* l, char* r, int b) {
    const int MOD = 1000000007;

    int dp[102][12][2]; // dp[position][last_digit][is_tight]
    int lenL = strlen(l);
    int lenR = strlen(r);

    // Function to count non-decreasing numbers up to a given limit
    int countUpTo(char* limit) {
        int len = strlen(limit);
        memset(dp, 0, sizeof(dp));
        dp[0][0][1] = 1; // Start with position 0, last_digit 0, tight constraint

        for (int pos = 0; pos < len; pos++) {
            for (int last = 0; last < b; last++) {
                for (int tight = 0; tight <= 1; tight++) {
                    int limitDigit = tight ? (limit[pos] - '0') : (b - 1);
                    for (int digit = last; digit <= limitDigit; digit++) {
                        int newTight = (tight && (digit == limitDigit)) ? 1 : 0;
                        dp[pos + 1][digit][newTight] = (dp[pos + 1][digit][newTight] + dp[pos][last][tight]) % MOD;
                    }
                }
            }
        }

        int total = 0;
        for (int last = 0; last < b; last++) {
            for (int tight = 0; tight <= 1; tight++) {
                total = (total + dp[len][last][tight]) % MOD;
            }
        }
        return total;
    }

    int countR = countUpTo(r);
    int countLMinus1 = countUpTo(l);

    // Check if l itself is non-decreasing
    int isNonDecreasing = 1;
    for (int i = 1; i < lenL; i++) {
        if (l[i] < l[i - 1]) {
            isNonDecreasing = 0;
            break;
        }
    }

    int result = (countR - countLMinus1 + MOD) % MOD;
    if (isNonDecreasing) {
        result = (result + 1) % MOD;
    }

    return result;      
}
