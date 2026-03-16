// Source: https://leetcode.com/problems/valid-anagram/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and t, return true if t is an anagram of s, and false otherwise.
//
// Example:
// Input: s = "anagram", t = "nagaram"
//
// Output: true
//
// Constraints:
// 1 <= s.length, t.length <= 5 * 104
// 	s and t consist of lowercase English letters.
//
//
//  
// Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
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

bool isAnagram(char* s, char* t) {
    int count[26] = {0}; // Assuming only lowercase English letters

    // Count characters in string s
    for (int i = 0; s[i] != '\0'; i++) {
        count[s[i] - 'a']++;
    }

    // Subtract counts based on characters in string t
    for (int i = 0; t[i] != '\0'; i++) {
        count[t[i] - 'a']--;
    }

    // Check if all counts are zero
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) {
            return false;
        }
    }

    return true;        
}
