// Source: https://leetcode.com/problems/find-common-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string array words, return an array of all characters that show up in all strings within the words (including duplicates). You may return the answer in any order.
//
// Example:
// Input: words = ["bella","label","roller"]
// Output: ["e","l","l"]
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 100
// 	words[i] consists of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** commonChars(char** words, int wordsSize, int* returnSize) {
    int minFreq[26];
    for (int i = 0; i < 26; i++) {
        minFreq[i] = 101; // Since max length of words[i] is 100
    }

    for (int w = 0; w < wordsSize; w++) {
        int freq[26] = {0};
        for (char* p = words[w]; *p != '\0'; p++) {
            freq[*p - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            if (freq[i] < minFreq[i]) {
                minFreq[i] = freq[i];
            }
        }
    }

    char** result = (char**)malloc(10000 * sizeof(char*)); // Allocate enough space
    int index = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < minFreq[i]; j++) {
            result[index] = (char*)malloc(2 * sizeof(char));
            result[index][0] = 'a' + i;
            result[index][1] = '\0';
            index++;
        }
    }

    *returnSize = index;
    return result;      
}
