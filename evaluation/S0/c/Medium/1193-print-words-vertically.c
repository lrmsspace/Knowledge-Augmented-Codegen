// Source: https://leetcode.com/problems/print-words-vertically/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s. Return all the words vertically in the same order in which they appear in s.
// Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
// Each word would be put on only one column and that in one column there will be only one word.
//
// Example:
// Input: s = "HOW ARE YOU"
// Output: ["HAY","ORO","WEU"]
// Explanation: Each word is printed vertically. 
//  "HAY"
//  "ORO"
//  "WEU"
//
// Constraints:
// 1 <= s.length <= 200
// 	s contains only upper case English letters.
// 	It's guaranteed that there is only one space between 2 words.
//



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** printVertically(char * s, int* returnSize){
    int len = strlen(s);
    int word_count = 1;
    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') {
            word_count++;
        }
    }

    char **words = (char **)malloc(word_count * sizeof(char *));
    for (int i = 0; i < word_count; i++) {
        words[i] = (char *)malloc((len + 1) * sizeof(char));
        memset(words[i], 0, (len + 1) * sizeof(char));
    }

    int max_word_length = 0;
    int current_word_index = 0;
    int current_word_length = 0;

    for (int i = 0; i <= len; i++) {
        if (s[i] == ' ' || s[i] == '\0') {
            words[current_word_index][current_word_length] = '\0';
            if (current_word_length > max_word_length) {
                max_word_length = current_word_length;
            }
            current_word_index++;
            current_word_length = 0;
        } else {
            words[current_word_index][current_word_length++] = s[i];
        }
    }

    char **result = (char **)malloc(max_word_length * sizeof(char *));
    for (int i = 0; i < max_word_length; i++) {
        result[i] = (char *)malloc((word_count + 1) * sizeof(char));
        memset(result[i], ' ', word_count * sizeof(char));
        result[i][word_count] = '\0';
    }

    for (int i = 0; i < word_count; i++) {
        int word_len = strlen(words[i]);
        for (int j = 0; j < word_len; j++) {
            result[j][i] = words[i][j];
        }
    }

    for (int i = 0; i < max_word_length; i++) {
        int end = word_count - 1;
        while (end >= 0 && result[i][end] == ' ') {
            end--;
        }
        result[i][end + 1] = '\0';
    }

    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);

    *returnSize = max_word_length;
    return result;
}
