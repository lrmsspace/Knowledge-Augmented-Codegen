// Source: https://leetcode.com/problems/count-the-number-of-special-characters-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.
//
// Return the number of special letters in word.
//
// Example:
// Input: word = "aaAbcBC"
//
// Output: 3
//
// Explanation:
//
// The special characters are 'a', 'b', and 'c'.
//
// Constraints:
// 1 <= word.length <= 2 * 105
// 	word consists of only lowercase and uppercase English letters.
//

int numberOfSpecialChars(char* word) {
    int lower[26] = {0};
    int upper[26] = {0};
    int specialCount = 0;

    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'z') {
            lower[c - 'a'] = 1;
        } else if (c >= 'A' && c <= 'Z') {
            upper[c - 'A'] = 1;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (lower[i] && upper[i]) {
            specialCount++;
        }
    }

    return specialCount;        
}
