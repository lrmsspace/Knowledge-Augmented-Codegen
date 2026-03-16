// Source: https://leetcode.com/problems/check-if-string-is-a-prefix-of-array/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s and an array of strings words, determine whether s is a prefix string of words.
//
// A string s is a prefix string of words if s can be made by concatenating the first k strings in words for some positive k no larger than words.length.
//
// Return true if s is a prefix string of words, or false otherwise.
//
// Example:
// Input: s = "iloveleetcode", words = ["i","love","leetcode","apples"]
// Output: true
// Explanation:
// s can be made by concatenating "i", "love", and "leetcode" together.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 20
// 	1 <= s.length <= 1000
// 	words[i] and s consist of only lowercase English letters.
//

bool isPrefixString(char* s, char** words, int wordsSize) {
    int index = 0;
    for (int i = 0; i < wordsSize; i++) {
        char* word = words[i];
        for (int j = 0; word[j] != '\0'; j++) {
            if (s[index] == '\0' || s[index] != word[j]) {
                return false;
            }
            index++;
        }
        if (s[index] == '\0') {
            return true;
        }
    }
    return s[index] == '\0';        
}
