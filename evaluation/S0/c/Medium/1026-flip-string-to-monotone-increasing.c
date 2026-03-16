// Source: https://leetcode.com/problems/flip-string-to-monotone-increasing/   |   Difficulty: Medium
//
// Problem Description:
// A binary string is monotone increasing if it consists of some number of 0's (possibly none), followed by some number of 1's (also possibly none).
//
// You are given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0.
//
// Return the minimum number of flips to make s monotone increasing.
//
// Example:
// Input: s = "00110"
// Output: 1
// Explanation: We flip the last digit to get 00111.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

int minFlipsMonoIncr(char* s) {
    int n = strlen(s);
    int dp0 = 0; // Minimum flips to make the string ending with '0'
    int dp1 = 0; // Minimum flips to make the string ending with '1'

    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            // If current char is '0', dp1 can come from either dp0 or dp1
            dp1 = fmin(dp0, dp1) + 1; // Flip '0' to '1'
        } else {
            // If current char is '1', dp0 must flip it to '0'
            dp0 += 1; // Flip '1' to '0'
            dp1 = fmin(dp0 - 1, dp1); // No flip needed for dp1
        }
    }

    return fmin(dp0, dp1);      
}
