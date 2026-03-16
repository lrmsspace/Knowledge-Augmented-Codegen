// Source: https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of strings words and a string chars.
//
// A string is good if it can be formed by characters from chars (each character can only be used once for each word in words).
//
// Return the sum of lengths of all good strings in words.
//
// Example:
// Input: words = ["cat","bt","hat","tree"], chars = "atach"
// Output: 6
// Explanation: The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length, chars.length <= 100
// 	words[i] and chars consist of lowercase English letters.
//

int countCharacters(char** words, int wordsSize, char* chars) {
    int charCount[26] = {0};
    for (int i = 0; chars[i] != '\0'; i++) {
        charCount[chars[i] - 'a']++;
    }

    int totalLength = 0;

    for (int i = 0; i < wordsSize; i++) {
        int wordCount[26] = {0};
        int j;
        for (j = 0; words[i][j] != '\0'; j++) {
            wordCount[words[i][j] - 'a']++;
            if (wordCount[words[i][j] - 'a'] > charCount[words[i][j] - 'a']) {
                break;
            }
        }
        if (words[i][j] == '\0') {
            totalLength += j;
        }
    }

    return totalLength;     
}
