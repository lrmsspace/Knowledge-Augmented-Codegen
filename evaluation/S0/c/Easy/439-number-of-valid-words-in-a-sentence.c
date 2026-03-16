// Source: https://leetcode.com/problems/number-of-valid-words-in-a-sentence/   |   Difficulty: Easy
//
// Problem Description:
// A sentence consists of lowercase letters ('a' to 'z'), digits ('0' to '9'), hyphens ('-'), punctuation marks ('!', '.', and ','), and spaces (' ') only. Each sentence can be broken down into one or more tokens separated by one or more spaces ' '.
//
// A token is a valid word if all three of the following are true:
//
//
// 	It only contains lowercase letters, hyphens, and/or punctuation (no digits).
// 	There is at most one hyphen '-'. If present, it must be surrounded by lowercase characters ("a-b" is valid, but "-ab" and "ab-" are not valid).
// 	There is at most one punctuation mark. If present, it must be at the end of the token ("ab,", "cd!", and "." are valid, but "a!b" and "c.," are not valid).
//
//
// Examples of valid words include "a-b.", "afad", "ba-c", "a!", and "!".
//
// Given a string sentence, return the number of valid words in sentence.
//
// Example:
// Input: sentence = "cat and  dog"
// Output: 3
// Explanation: The valid words in the sentence are "cat", "and", and "dog".
//
// Constraints:
// 1 <= sentence.length <= 1000
// 	sentence only contains lowercase English letters, digits, ' ', '-', '!', '.', and ','.
// 	There will be at least 1 token.
//

int countValidWords(char* sentence) {
    int count = 0;
    char *token = strtok(sentence, " ");
    
    while (token != NULL) {
        int len = strlen(token);
        int hyphen_count = 0;
        int punctuation_count = 0;
        int is_valid = 1;

        for (int i = 0; i < len; i++) {
            char c = token[i];

            if (isdigit(c)) {
                is_valid = 0;
                break;
            } else if (c == '-') {
                hyphen_count++;
                if (hyphen_count > 1 || i == 0 || i == len - 1 || !islower(token[i - 1]) || !islower(token[i + 1])) {
                    is_valid = 0;
                    break;
                }
            } else if (c == '!' || c == '.' || c == ',') {
                punctuation_count++;
                if (punctuation_count > 1 || i != len - 1) {
                    is_valid = 0;
                    break;
                }
            } else if (!islower(c)) {
                is_valid = 0;
                break;
            }
        }

        if (is_valid) {
            count++;
        }

        token = strtok(NULL, " ");
    }

    return count;       
}
