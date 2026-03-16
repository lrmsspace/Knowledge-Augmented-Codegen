// Source: https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one contiguous segment of ones. Otherwise, return false.
//
// Example:
// Input: s = "1001"
// Output: false
// Explanation: The ones do not form a contiguous segment.
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i]​​​​ is either '0' or '1'.
// 	s[0] is '1'.
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

bool checkOnesSegment(char* s) {
    int i = 0;
    // Traverse the string until we find the first '0'
    while (s[i] != '\0' && s[i] == '1') {
        i++;
    }
    // After the first '0', check if there are any more '1's
    while (s[i] != '\0') {
        if (s[i] == '1') {
            return false; // Found another segment of '1's
        }
        i++;
    }
    return true; // At most one segment of '1's found       
}
