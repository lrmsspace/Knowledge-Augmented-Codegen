// Source: https://leetcode.com/problems/longest-string-chain/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of words where each word consists of lowercase English letters.
//
// wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.
//
//
// 	For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
//
//
// A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.
//
// Return the length of the longest possible word chain with words chosen from the given list of words.
//
// Example:
// Input: words = ["a","b","ba","bca","bda","bdca"]
// Output: 4
// Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 16
// 	words[i] only consists of lowercase English letters.
//

int longestStrChain(char** words, int wordsSize) {
    int dp[1000];
    int max_chain = 1;

    // Comparator function for qsort to sort words by length
    int cmp(const void* a, const void* b) {
        return strlen(*(const char**)a) - strlen(*(const char**)b);
    }

    // Function to check if word1 is a predecessor of word2
    int isPredecessor(const char* word1, const char* word2) {
        int len1 = strlen(word1);
        int len2 = strlen(word2);
        if (len2 - len1 != 1) return 0;

        int i = 0, j = 0;
        while (i < len1 && j < len2) {
            if (word1[i] == word2[j]) {
                i++;
            }
            j++;
        }
        return i == len1;
    }

    // Sort words by their lengths
    qsort(words, wordsSize, sizeof(char*), cmp);

    // Initialize dp array
    for (int i = 0; i < wordsSize; i++) {
        dp[i] = 1;
    }

    // Build the dp array
    for (int i = 0; i < wordsSize; i++) {
        for (int j = 0; j < i; j++) {
            if (isPredecessor(words[j], words[i])) {
                dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
            }
        }
        max_chain = max_chain > dp[i] ? max_chain : dp[i];
    }

    return max_chain;       
}
