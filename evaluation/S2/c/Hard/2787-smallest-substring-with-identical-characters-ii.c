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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minLength(char* s, int numOps) {
    int n = 0;
    while (s[n]) n++;

    int left = 1, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;

        int count0 = 0, count1 = 0;
        for (int i = 0; i < mid; i++) {
            if (s[i] == '0') count0++;
            else count1++;
        }

        int maxCount = count0 > count1 ? count0 : count1;
        if (maxCount + numOps >= mid) {
            right = mid;
        } else {
            left = mid + 1;
        }

        for (int i = mid; i < n; i++) {
            if (s[i] == '0') count0++;
            else count1++;

            if (s[i - mid] == '0') count0--;
            else count1--;

            maxCount = count0 > count1 ? count0 : count1;
            if (maxCount + numOps >= mid) {
                right = mid;
                break;
            }
        }
    }

    return left;        
}
