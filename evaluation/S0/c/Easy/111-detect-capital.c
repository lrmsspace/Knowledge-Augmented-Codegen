// Source: https://leetcode.com/problems/detect-capital/   |   Difficulty: Easy
//
// Problem Description:
// We define the usage of capitals in a word to be right when one of the following cases holds:
//
//
// 	All letters in this word are capitals, like "USA".
// 	All letters in this word are not capitals, like "leetcode".
// 	Only the first letter in this word is capital, like "Google".
//
//
// Given a string word, return true if the usage of capitals in it is right.
//
// Example:
// Input: word = "USA"
// Output: true
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists of lowercase and uppercase English letters.
//

bool detectCapitalUse(char* word) {
    int len = 0;
    while (word[len] != '\0') {
        len++;
    }

    if (len == 1) {
        return true;
    }

    if (word[0] >= 'a' && word[0] <= 'z') {
        // all lowercase
        for (int i = 1; i < len; i++) {
            if (word[i] >= 'A' && word[i] <= 'Z') {
                return false;
            }
        }
        return true;
    } else {
        // first letter is uppercase
        if (word[1] >= 'A' && word[1] <= 'Z') {
            // all uppercase
            for (int i = 2; i < len; i++) {
                if (word[i] >= 'a' && word[i] <= 'z') {
                    return false;
                }
            }
            return true;
        } else {
            // only first letter uppercase
            for (int i = 2; i < len; i++) {
                if (word[i] >= 'A' && word[i] <= 'Z') {
                    return false;
                }
            }
            return true;
        }
    }       
}
