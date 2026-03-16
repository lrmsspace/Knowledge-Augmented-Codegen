// Source: https://leetcode.com/problems/numbers-with-repeated-digits/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the number of positive integers in the range [1, n] that have at least one repeated digit.
//
// Example:
// Input: n = 20
// Output: 1
// Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
//
// Constraints:
// 1 <= n <= 109
//

int numDupDigitsAtMostN(int n) {
    int digits[10];
    int d = 0, originalN = n;
    while (n > 0) {
        digits[d++] = n % 10;
        n /= 10;
    }
    int res = 0;

    // Count numbers with fewer digits than originalN
    for (int len = 1; len < d; len++) {
        int count = 9;
        for (int i = 1; i < len; i++) {
            count *= (10 - i);
        }
        res += count;
    }

    // Count numbers with the same number of digits
    int used[10] = {0};
    for (int i = d - 1; i >= 0; i--) {
        for (int j = (i == d - 1) ? 1 : 0; j < digits[i]; j++) {
            if (!used[j]) {
                int count = 1;
                for (int k = 1; k < i; k++) {
                    count *= (10 - k - __builtin_popcount((1 << j) | ((1 << j) - 1)));
                }
                res += count;
            }
        }
        if (used[digits[i]]) break;
        used[digits[i]] = 1;
        if (i == 0) res++; // Count the number itself if all digits are unique
    }

    return originalN - res;     
}
