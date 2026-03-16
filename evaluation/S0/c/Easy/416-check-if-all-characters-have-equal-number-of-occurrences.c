// Source: https://leetcode.com/problems/check-if-all-characters-have-equal-number-of-occurrences/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return true if s is a good string, or false otherwise.
//
// A string s is good if all the characters that appear in s have the same number of occurrences (i.e., the same frequency).
//
// Example:
// Input: s = "abacbc"
// Output: true
// Explanation: The characters that appear in s are 'a', 'b', and 'c'. All characters occur 2 times in s.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters.
//

bool areOccurrencesEqual(char* s) {
    int freq[26] = {0};
    for (int i = 0; s[i] != '\0'; i++) {
        freq[s[i] - 'a']++;
    }

    int expected = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            if (expected == 0) {
                expected = freq[i];
            } else if (freq[i] != expected) {
                return false;
            }
        }
    }
    return true;        
}
