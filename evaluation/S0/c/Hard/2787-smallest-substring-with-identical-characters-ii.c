// Source: https://leetcode.com/problems/smallest-substring-with-identical-characters-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s of length n and an integer numOps.
//
// You are allowed to perform the following operation on s at most numOps times:
//
//
// 	Select any index i (where 0 <= i < n) and flip s[i]. If s[i] == '1', change s[i] to '0' and vice versa.
//
//
// You need to minimize the length of the longest substring of s such that all the characters in the substring are identical.
//
// Return the minimum length after the operations.
//
// Example:
// Input: s = "000001", numOps = 1
//
// Output: 2
//
// Explanation: 
//
// By changing s[2] to '1', s becomes "001001". The longest substrings with identical characters are s[0..1] and s[3..4].
//
// Constraints:
// 1 <= n == s.length <= 105
// 	s consists only of '0' and '1'.
// 	0 <= numOps <= n
//

int minLength(char* s, int numOps) {
    int n = strlen(s);
    int left = 1, right = n;

    while (left < right) {
        int mid = left + (right - left) / 2;
        int maxAllowedOps = numOps;

        /* Check for '0' */
        int ops = 0;
        for (int i = 0; i < mid; ++i) {
            if (s[i] == '1') ops++;
        }
        if (ops <= maxAllowedOps) {
            right = mid;
            continue;
        }
        for (int i = mid; i < n; ++i) {
            if (s[i - mid] == '1') ops--;
            if (s[i] == '1') ops++;
            if (ops <= maxAllowedOps) break;
        }
        if (ops <= maxAllowedOps) {
            right = mid;
            continue;
        }

        /* Check for '1' */
        ops = 0;
        for (int i = 0; i < mid; ++i) {
            if (s[i] == '0') ops++;
        }
        if (ops <= maxAllowedOps) {
            right = mid;
            continue;
        }
        for (int i = mid; i < n; ++i) {
            if (s[i - mid] == '0') ops--;
            if (s[i] == '0') ops++;
            if (ops <= maxAllowedOps) break;
        }
        if (ops <= maxAllowedOps) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;        
}
