// Source: https://leetcode.com/problems/reverse-words-in-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Given an input string s, reverse the order of the words.
//
// A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.
//
// Return a string of the words in reverse order concatenated by a single space.
//
// Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.
//
// Example:
// Input: s = "the sky is blue"
// Output: "blue is sky the"
//
// Constraints:
// 1 <= s.length <= 104
// 	s contains English letters (upper-case and lower-case), digits, and spaces ' '.
// 	There is at least one word in s.
//
//
//  
// Follow-up: If the string data type is mutable in your language, can you solve it in-place with O(1) extra space?
//

char* reverseWords(char* s) {
    int len = strlen(s);
    char* result = (char*)malloc(len + 1);
    int result_index = 0;
    int i = len - 1;

    while (i >= 0) {
        // Skip trailing spaces
        while (i >= 0 && s[i] == ' ') {
            i--;
        }
        if (i < 0) break;

        // Find the start of the word
        int end = i;
        while (i >= 0 && s[i] != ' ') {
            i--;
        }
        int start = i + 1;

        // Copy the word to the result
        if (result_index > 0) {
            result[result_index++] = ' '; // Add space before the next word
        }
        for (int j = start; j <= end; j++) {
            result[result_index++] = s[j];
        }
    }

    result[result_index] = '\0'; // Null-terminate the string
    return result;      
}
