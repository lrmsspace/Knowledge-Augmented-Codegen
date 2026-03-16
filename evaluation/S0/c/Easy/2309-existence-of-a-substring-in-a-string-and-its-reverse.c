// Source: https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, find any substring of length 2 which is also present in the reverse of s.
//
// Return true if such a substring exists, and false otherwise.
//
// Example:
// Input: s = "leetcode"
//
// Output: true
//
// Explanation: Substring "ee" is of length 2 which is also present in reverse(s) == "edocteel".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists only of lowercase English letters.
//

bool isSubstringPresent(char* s) {
    int len = strlen(s);
    for (int i = 0; i < len - 1; i++) {
        for (int j = len - 2; j >= 0; j--) {
            if (s[i] == s[j] && s[i + 1] == s[j + 1]) {
                return true;
            }
        }
    }
    return false;       
}
