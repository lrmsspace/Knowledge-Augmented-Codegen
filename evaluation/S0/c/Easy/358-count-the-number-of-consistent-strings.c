// Source: https://leetcode.com/problems/count-the-number-of-consistent-strings/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string allowed consisting of distinct characters and an array of strings words. A string is consistent if all characters in the string appear in the string allowed.
//
// Return the number of consistent strings in the array words.
//
// Example:
// Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
// Output: 2
// Explanation: Strings "aaab" and "baa" are consistent since they only contain characters 'a' and 'b'.
//
// Constraints:
// 1 <= words.length <= 104
// 	1 <= allowed.length <= 26
// 	1 <= words[i].length <= 10
// 	The characters in allowed are distinct.
// 	words[i] and allowed contain only lowercase English letters.
//



int countConsistentStrings(char * allowed, char ** words, int wordsSize){
    int allowed_chars[26] = {0};
    for (int i = 0; allowed[i] != '\0'; i++) {
        allowed_chars[allowed[i] - 'a'] = 1;
    }

    int consistent_count = 0;
    for (int i = 0; i < wordsSize; i++) {
        int is_consistent = 1;
        for (int j = 0; words[i][j] != '\0'; j++) {
            if (!allowed_chars[words[i][j] - 'a']) {
                is_consistent = 0;
                break;
            }
        }
        if (is_consistent) {
            consistent_count++;
        }
    }

    return consistent_count;
}
