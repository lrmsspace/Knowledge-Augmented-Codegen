// Source: https://leetcode.com/problems/count-common-words-with-one-occurrence/   |   Difficulty: Easy
//
// Problem Description:
// Given two string arrays words1 and words2, return the number of strings that appear exactly once in each of the two arrays.
//
// Example:
// Input: words1 = ["leetcode","is","amazing","as","is"], words2 = ["amazing","leetcode","is"]
// Output: 2
// Explanation:
// - "leetcode" appears exactly once in each of the two arrays. We count this string.
// - "amazing" appears exactly once in each of the two arrays. We count this string.
// - "is" appears in each of the two arrays, but there are 2 occurrences of it in words1. We do not count this string.
// - "as" appears once in words1, but does not appear in words2. We do not count this string.
// Thus, there are 2 strings that appear exactly once in each of the two arrays.
//
// Constraints:
// 1 <= words1.length, words2.length <= 1000
// 	1 <= words1[i].length, words2[j].length <= 30
// 	words1[i] and words2[j] consists only of lowercase English letters.
//

int countWords(char** words1, int words1Size, char** words2, int words2Size) {
    int count = 0;
    int freq1[1000] = {0};
    int freq2[1000] = {0};
    char* uniqueWords[2000];
    int uniqueCount = 0;

    // Count frequencies in words1
    for (int i = 0; i < words1Size; i++) {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (strcmp(uniqueWords[j], words1[i]) == 0) {
                freq1[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            uniqueWords[uniqueCount] = words1[i];
            freq1[uniqueCount]++;
            uniqueCount++;
        }
    }

    // Count frequencies in words2
    for (int i = 0; i < words2Size; i++) {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (strcmp(uniqueWords[j], words2[i]) == 0) {
                freq2[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            uniqueWords[uniqueCount] = words2[i];
            freq2[uniqueCount]++;
            uniqueCount++;
        }
    }

    // Count common words with exactly one occurrence in both arrays
    for (int i = 0; i < uniqueCount; i++) {
        if (freq1[i] == 1 && freq2[i] == 1) {
            count++;
        }
    }

    return count;       
}
