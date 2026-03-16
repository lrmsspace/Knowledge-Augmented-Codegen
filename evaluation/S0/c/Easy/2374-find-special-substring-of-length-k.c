// Source: https://leetcode.com/problems/find-special-substring-of-length-k/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s and an integer k.
//
// Determine if there exists a substring of length exactly k in s that satisfies the following conditions:
//
//
// 	The substring consists of only one distinct character (e.g., "aaa" or "bbb").
// 	If there is a character immediately before the substring, it must be different from the character in the substring.
// 	If there is a character immediately after the substring, it must also be different from the character in the substring.
//
//
// Return true if such a substring exists. Otherwise, return false.
//
// Example:
// Input: s = "aaabaaa", k = 3
//
// Output: true
//
// Explanation:
//
// The substring s[4..6] == "aaa" satisfies the conditions.
//
//
// 	It has a length of 3.
// 	All characters are the same.
// 	The character before "aaa" is 'b', which is different from 'a'.
// 	There is no character after "aaa".
//
// Constraints:
// 1 <= k <= s.length <= 100
// 	s consists of lowercase English letters only.
//

bool hasSpecialSubstring(char* s, int k) {
    int count = 1;
    for (int i = 1; s[i] != '\0'; i++) {
        if (s[i] == s[i - 1]) {
            count++;
        } else {
            count = 1;
        }

        if (count == k) {
            if ((i - k < 0 || s[i - k] != s[i]) &&
                (s[i + 1] == '\0' || s[i + 1] != s[i])) {
                return true;
            }
        }
    }
    return false;       
}
