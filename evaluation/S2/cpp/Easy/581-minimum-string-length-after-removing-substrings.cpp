// Source: https://leetcode.com/problems/minimum-string-length-after-removing-substrings/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting only of uppercase English letters.
//
// You can apply some operations to this string where, in one operation, you can remove any occurrence of one of the substrings "AB" or "CD" from s.
//
// Return the minimum possible length of the resulting string that you can obtain.
//
// Note that the string concatenates after removing the substring and could produce new "AB" or "CD" substrings.
//
// Example:
// Input: s = "ABFCACDB"
// Output: 2
// Explanation: We can do the following operations:
// - Remove the substring "ABFCACDB", so s = "FCACDB".
// - Remove the substring "FCACDB", so s = "FCAB".
// - Remove the substring "FCAB", so s = "FC".
// So the resulting length of the string is 2.
// It can be shown that it is the minimum length that we can obtain.
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists only of uppercase English letters.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minLength(string s) {
        int count = 0;
        for (char c : s) {
            if (c == 'B' && count > 0) {
                count--;
            } else if (c == 'D' && count > 0) {
                count--;
            } else if (c == 'A' || c == 'C') {
                count++;
            }
        }
        return count;           
    }
};
