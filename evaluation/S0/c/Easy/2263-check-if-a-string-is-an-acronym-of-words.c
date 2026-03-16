// Source: https://leetcode.com/problems/check-if-a-string-is-an-acronym-of-words/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of strings words and a string s, determine if s is an acronym of words.
//
// The string s is considered an acronym of words if it can be formed by concatenating the first character of each string in words in order. For example, "ab" can be formed from ["apple", "banana"], but it can't be formed from ["bear", "aardvark"].
//
// Return true if s is an acronym of words, and false otherwise.
//
// Example:
// Input: words = ["alice","bob","charlie"], s = "abc"
// Output: true
// Explanation: The first character in the words "alice", "bob", and "charlie" are 'a', 'b', and 'c', respectively. Hence, s = "abc" is the acronym.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 10
// 	1 <= s.length <= 100
// 	words[i] and s consist of lowercase English letters.
//

bool isAcronym(char** words, int wordsSize, char* s) {
    int i;
    for (i = 0; i < wordsSize; i++) {
        if (s[i] != words[i][0]) {
            return false;
        }
    }
    return s[i] == '\0';        
}
