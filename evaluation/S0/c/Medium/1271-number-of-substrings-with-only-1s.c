// Source: https://leetcode.com/problems/number-of-substrings-with-only-1s/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, return the number of substrings with all characters 1's. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "0110111"
// Output: 9
// Explanation: There are 9 substring in total with only 1's characters.
// "1" -> 5 times.
// "11" -> 3 times.
// "111" -> 1 time.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

int numSub(char* s) {
    long long count = 0;
    long long result = 0;
    const int MOD = 1e9 + 7;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '1') {
            count++;
            result = (result + count) % MOD;
        } else {
            count = 0;
        }
    }

    return (int)result;     
}
