// Source: https://leetcode.com/problems/valid-palindrome-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return true if the s can be palindrome after deleting at most one character from it.
//
// Example:
// Input: s = "aba"
// Output: true
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
//

bool validPalindrome(char* s) {
    int left = 0;
    int right = strlen(s) - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            // Check by skipping either the left or the right character
            int l1 = left + 1, r1 = right;
            int l2 = left, r2 = right - 1;

            while (l1 < r1 && s[l1] == s[r1]) {
                l1++;
                r1--;
            }
            if (l1 >= r1) return true;

            while (l2 < r2 && s[l2] == s[r2]) {
                l2++;
                r2--;
            }
            return l2 >= r2;
        }
        left++;
        right--;
    }
    return true;        
}
