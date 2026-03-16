// Source: https://leetcode.com/problems/construct-k-palindrome-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return true if you can use all the characters in s to construct non-empty k palindrome strings or false otherwise.
//
// Example:
// Input: s = "annabelle", k = 2
// Output: true
// Explanation: You can construct two palindromes using all characters in s.
// Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	1 <= k <= 105
//

bool canConstruct(char* s, int k) {
    int char_count[26] = {0};
    int odd_count = 0;

    // Count the frequency of each character in the string
    for (int i = 0; s[i] != '\0'; i++) {
        char_count[s[i] - 'a']++;
    }

    // Count how many characters have an odd frequency
    for (int i = 0; i < 26; i++) {
        if (char_count[i] % 2 != 0) {
            odd_count++;
        }
    }

    // We need at least 'odd_count' palindromes to accommodate all odd frequency characters
    // If k is less than odd_count, it's impossible to form k palindromes
    return k >= odd_count;      
}
