// Source: https://leetcode.com/problems/number-of-beautiful-integers-in-the-range/   |   Difficulty: Hard
//
// Problem Description:
// You are given positive integers low, high, and k.
//
// A number is beautiful if it meets both of the following conditions:
//
//
// 	The count of even digits in the number is equal to the count of odd digits.
// 	The number is divisible by k.
//
//
// Return the number of beautiful integers in the range [low, high].
//
// Example:
// Input: low = 10, high = 20, k = 3
// Output: 2
// Explanation: There are 2 beautiful integers in the given range: [12,18]. 
// - 12 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
// - 18 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
// Additionally we can see that:
// - 16 is not beautiful because it is not divisible by k = 3.
// - 15 is not beautiful because it does not contain equal counts even and odd digits.
// It can be shown that there are only 2 beautiful integers in the given range.
//
// Constraints:
// 0 < low <= high <= 109
// 	0 < k <= 20
//

int numberOfBeautifulIntegers(int low, int high, int k) {
    int dp[11][11][20][2]; /* even, odd, mod, tight */
    int digits[11];
    int i, j, m, t, pos, limit, even, odd, mod, resHigh, resLow;

    /* Helper function to compute count of beautiful integers <= bound */
    int countBeautiful(int bound) {
        if (bound < 0) return 0;
        if (bound == 0) return 0;
        int dcount = 0;
        while (bound > 0) {
            digits[dcount++] = bound % 10;
            bound /= 10;
        }
        memset(dp, 0, sizeof(dp));
        dp[0][0][0][1] = 1; /* base case */
        for (pos = dcount - 1; pos >= 0; pos--) {
            for (even = 0; even <= dcount; even++) {
                for (odd = 0; odd <= dcount; odd++) {
                    for (mod = 0; mod < k; mod++) {
                        for (t = 0; t <= 1; t++) {
                            limit = t ? digits[pos] : 9;
                            for (i = 0; i <= limit; i++) {
                                int neven = even + ((i % 2) == 0 ? 1 : 0);
                                int nodd = odd + ((i % 2) == 1 ? 1 : 0);
                                int nmod = (mod * 10 + i) % k;
                                int nt = (t && (i == limit)) ? 1 : 0;
                                dp[neven][nodd][nmod][nt] += dp[even][odd][mod][t];
                            }
                        }
                    }
                }
            }
        }
        int total = 0;
        for (t = 0; t <= 1; t++) {
            total += dp[dcount / 2][dcount / 2][0][t];
        }
        return total;
    }

    resHigh = countBeautiful(high);
    resLow = countBeautiful(low - 1);
    return resHigh - resLow;        
}
