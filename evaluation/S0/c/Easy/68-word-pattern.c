// Source: https://leetcode.com/problems/word-pattern/   |   Difficulty: Easy
//
// Problem Description:
// Given a pattern and a string s, find if s follows the same pattern.
//
// Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s. Specifically:
//
//
// 	Each letter in pattern maps to exactly one unique word in s.
// 	Each unique word in s maps to exactly one letter in pattern.
// 	No two letters map to the same word, and no two words map to the same letter.
//
// Example:
// Input: pattern = "abba", s = "dog cat cat dog"
//
// Output: true
//
// Explanation:
//
// The bijection can be established as:
//
//
// 	'a' maps to "dog".
// 	'b' maps to "cat".
//
// Constraints:
// 1 <= pattern.length <= 300
// 	pattern contains only lower-case English letters.
// 	1 <= s.length <= 3000
// 	s contains only lowercase English letters and spaces ' '.
// 	s does not contain any leading or trailing spaces.
// 	All the words in s are separated by a single space.
//

bool wordPattern(char* pattern, char* s) {
    char* words[26] = {0};
    char* p = pattern;
    char* start = s;
    char* end = s;
    int index;

    while (*p) {
        // Find the next word in s
        while (*end && *end != ' ') {
            end++;
        }

        // If we reach the end of s but still have pattern left, return false
        if (start == end) {
            return false;
        }

        // Extract the current word
        int len = end - start;
        char word[len + 1];
        strncpy(word, start, len);
        word[len] = '\0';

        index = *p - 'a';

        // Check if the pattern character already has a mapped word
        if (words[index]) {
            // If it does, check if it matches the current word
            if (strcmp(words[index], word) != 0) {
                return false;
            }
        } else {
            // Check if the current word is already mapped to another pattern character
            for (int i = 0; i < 26; i++) {
                if (words[i] && strcmp(words[i], word) == 0) {
                    return false;
                }
            }
            // Map the pattern character to the current word
            words[index] = strdup(word);
        }

        // Move to the next pattern character and the next word in s
        p++;
        if (*end) {
            end++; // Skip the space
        }
        start = end;
    }

    // If there are still words left in s after processing the pattern, return false
    if (*start) {
        return false;
    }

    return true;        
}
