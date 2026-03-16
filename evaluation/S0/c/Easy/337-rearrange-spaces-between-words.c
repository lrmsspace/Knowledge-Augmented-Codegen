// Source: https://leetcode.com/problems/rearrange-spaces-between-words/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string text of words that are placed among some number of spaces. Each word consists of one or more lowercase English letters and are separated by at least one space. It's guaranteed that text contains at least one word.
//
// Rearrange the spaces so that there is an equal number of spaces between every pair of adjacent words and that number is maximized. If you cannot redistribute all the spaces equally, place the extra spaces at the end, meaning the returned string should be the same length as text.
//
// Return the string after rearranging the spaces.
//
// Example:
// Input: text = "  this   is  a sentence "
// Output: "this   is   a   sentence"
// Explanation: There are a total of 9 spaces and 4 words. We can evenly divide the 9 spaces between the words: 9 / (4-1) = 3 spaces.
//
// Constraints:
// 1 <= text.length <= 100
// 	text consists of lowercase English letters and ' '.
// 	text contains at least one word.
//

char* reorderSpaces(char* text) {
    int space_count = 0, word_count = 0;
    char* p = text;
    while (*p) {
        if (*p == ' ') {
            space_count++;
            p++;
        } else {
            word_count++;
            while (*p && *p != ' ') p++;
        }
    }

    int spaces_between = word_count > 1 ? space_count / (word_count - 1) : 0;
    int extra_spaces = word_count > 1 ? space_count % (word_count - 1) : space_count;

    char* result = (char*)malloc(strlen(text) + 1);
    char* r = result;
    p = text;

    while (*p) {
        if (*p == ' ') {
            p++;
        } else {
            while (*p && *p != ' ') {
                *r++ = *p++;
            }
            if (--word_count > 0) {
                for (int i = 0; i < spaces_between; i++) {
                    *r++ = ' ';
                }
            }
        }
    }

    for (int i = 0; i < extra_spaces; i++) {
        *r++ = ' ';
    }
    *r = '\0';

    return result;      
}
