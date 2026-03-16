// Source: https://leetcode.com/problems/top-k-frequent-words/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings words and an integer k, return the k most frequent strings.
//
// Return the answer sorted by the frequency from highest to lowest. Sort the words with the same frequency by their lexicographical order.
//
// Example:
// Input: words = ["i","love","leetcode","i","love","coding"], k = 2
// Output: ["i","love"]
// Explanation: "i" and "love" are the two most frequent words.
// Note that "i" comes before "love" due to a lower alphabetical order.
//
// Constraints:
// 1 <= words.length <= 500
// 	1 <= words[i].length <= 10
// 	words[i] consists of lowercase English letters.
// 	k is in the range [1, The number of unique words[i]]
//
//
//  
// Follow-up: Could you solve it in O(n log(k)) time and O(n) extra space?
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** topKFrequent(char** words, int wordsSize, int k, int* returnSize) {
    // Hash map to count frequencies
    typedef struct {
        char* word;
        int freq;
    } WordFreq;

    WordFreq freqMap[500];
    int freqCount = 0;

    for (int i = 0; i < wordsSize; i++) {
        int found = 0;
        for (int j = 0; j < freqCount; j++) {
            if (strcmp(freqMap[j].word, words[i]) == 0) {
                freqMap[j].freq++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freqMap[freqCount].word = words[i];
            freqMap[freqCount].freq = 1;
            freqCount++;
        }
    }

    // Sort by frequency and lexicographical order
    qsort(freqMap, freqCount, sizeof(WordFreq), [](const void* a, const void* b) {
        WordFreq* wfA = (WordFreq*)a;
        WordFreq* wfB = (WordFreq*)b;
        if (wfA->freq != wfB->freq) {
            return wfB->freq - wfA->freq; // Descending frequency
        }
        return strcmp(wfA->word, wfB->word); // Ascending lexicographical order
    });

    // Prepare result
    char** result = (char**)malloc(k * sizeof(char*));
    for (int i = 0; i < k; i++) {
        result[i] = freqMap[i].word;
    }

    *returnSize = k;
    return result;      
}
