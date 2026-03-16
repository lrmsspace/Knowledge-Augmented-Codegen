// Source: https://leetcode.com/problems/count-substrings-divisible-by-last-digit/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of digits.
//
// Return the number of substrings of s divisible by their non-zero last digit.
//
// Note: A substring may contain leading zeros.
//
// Example:
// Input: s = "12936"
//
// Output: 11
//
// Explanation:
//
// Substrings "29", "129", "293" and "2936" are not divisible by their last digit. There are 15 substrings in total, so the answer is 15 - 4 = 11.
//
// Constraints:
// 1 <= s.length <= 105
//  s consists of digits only.
//

long long countSubstrings(char* s) {
    long long result = 0;
    int n = strlen(s);
    for (int i = 0; i < n; ++i) {
        int lastDigit = s[i] - '0';
        if (lastDigit == 0) continue; /* skip substrings ending with '0' */
        int num = 0;
        for (int j = i; j >= 0; --j) {
            num = (num + (s[j] - '0') * 1) % lastDigit;
            if (num == 0) result++;
            num = (num * 10) % lastDigit;
        }
    }
    return result;      
}
