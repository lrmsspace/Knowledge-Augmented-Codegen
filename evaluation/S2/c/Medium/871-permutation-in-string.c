// Source: https://leetcode.com/problems/permutation-in-string/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
//
// In other words, return true if one of s1's permutations is the substring of s2.
//
// Example:
// Input: s1 = "ab", s2 = "eidbaooo"
// Output: true
// Explanation: s2 contains one permutation of s1 ("ba").
//
// Constraints:
// 1 <= s1.length, s2.length <= 104
// 	s1 and s2 consist of lowercase English letters.
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

bool checkInclusion(char* s1, char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    if (len1 > len2) {
        return false;
    }
    
    int count[26] = {0};
    
    for (int i = 0; i < len1; i++) {
        count[s1[i] - 'a']++;
        count[s2[i] - 'a']--;
    }
    
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) {
            return false;
        }
    }
    
    for (int i = len1; i < len2; i++) {
        count[s2[i] - 'a']--;
        count[s2[i - len1] - 'a']++;
        
        bool valid = true;
        for (int j = 0; j < 26; j++) {
            if (count[j] != 0) {
                valid = false;
                break;
            }
        }
        
        if (valid) {
            return true;
        }
    }
    
    return false;       
}
