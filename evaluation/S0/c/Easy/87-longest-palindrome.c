// Source: https://leetcode.com/problems/longest-palindrome/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.
//
// Letters are case sensitive, for example, "Aa" is not considered a palindrome.
//
// Example:
// Input: s = "abccccdd"
// Output: 7
// Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.
//
// Constraints:
// 1 <= s.length <= 2000
// 	s consists of lowercase and/or uppercase English letters only.
//

int longestPalindrome(char* s) {
    int count[52] = {0};
    int length = 0;
    int hasOdd = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            count[s[i] - 'a']++;
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            count[s[i] - 'A' + 26]++;
        }
    }

    for (int i = 0; i < 52; i++) {
        if (count[i] % 2 == 0) {
            length += count[i];
        } else {
            length += count[i] - 1;
            hasOdd = 1;
        }
    }

    return length + hasOdd;     
}
