// Source: https://leetcode.com/problems/count-the-number-of-special-characters-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.
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
// The special characters in word are 'a', 'b', and 'c'.
//
// Constraints:
// 1 <= word.length <= 50
// 	word consists of only lowercase and uppercase English letters.
//

int numberOfSpecialChars(char* word) {
    int lower[26] = {0};
    int upper[26] = {0};
    int count = 0;
    
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            lower[word[i] - 'a'] = 1;
        } else if (word[i] >= 'A' && word[i] <= 'Z') {
            upper[word[i] - 'A'] = 1;
        }
    }
    
    for (int i = 0; i < 26; i++) {
        if (lower[i] && upper[i]) {
            count++;
        }
    }
    
    return count;       
}
