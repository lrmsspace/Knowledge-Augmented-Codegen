// Source: https://leetcode.com/problems/number-of-ways-to-split-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, you can split s into 3 non-empty strings s1, s2, and s3 where s1 + s2 + s3 = s.
//
// Return the number of ways s can be split such that the number of ones is the same in s1, s2, and s3. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "10101"
// Output: 4
// Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
// "1|010|1"
// "1|01|01"
// "10|10|1"
// "10|1|01"
//
// Constraints:
// 3 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

int numWays(char* s) {
    const int MOD = 1e9 + 7;
    int n = 0;
    for (char* p = s; *p; ++p) {
        if (*p == '1') {
            n++;
        }
    }
    if (n % 3 != 0) {
        return 0;
    }
    if (n == 0) {
        int len = strlen(s);
        return (int)(((long long)(len - 1) * (len - 2) / 2) % MOD);
    }
    int ones_per_part = n / 3;
    int first_cut_ways = 0;
    int second_cut_ways = 0;
    int count_ones = 0;
    for (char* p = s; *p; ++p) {
        if (*p == '1') {
            count_ones++;
        }
        if (count_ones == ones_per_part) {
            first_cut_ways++;
        } else if (count_ones == 2 * ones_per_part) {
            second_cut_ways++;
        }
    }
    return (int)(((long long)first_cut_ways * second_cut_ways) % MOD);      
}
