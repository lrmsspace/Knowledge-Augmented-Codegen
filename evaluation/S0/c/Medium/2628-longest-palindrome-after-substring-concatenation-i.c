// Source: https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings, s and t.
//
// You can create a new string by selecting a substring from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.
//
// Return the length of the longest palindrome that can be formed this way.
//
// Example:
// Input: s = "a", t = "a"
//
// Output: 2
//
// Explanation:
//
// Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.
//
// Constraints:
// 1 <= s.length, t.length <= 30
// 	s and t consist of lowercase English letters.
//

int longestPalindrome(char* s, char* t) {
    int maxLen = 0;
    int lenS = strlen(s);
    int lenT = strlen(t);

    for (int i = 0; i < lenS; i++) {
        for (int j = 0; j < lenT; j++) {
            if (s[i] == t[j]) {
                int left = i - 1;
                int right = j + 1;
                int currentLen = 2;

                while (left >= 0 && right < lenT && s[left] == t[right]) {
                    currentLen += 2;
                    left--;
                    right++;
                }

                if (currentLen > maxLen) {
                    maxLen = currentLen;
                }
            }
        }
    }

    return maxLen;      
}
