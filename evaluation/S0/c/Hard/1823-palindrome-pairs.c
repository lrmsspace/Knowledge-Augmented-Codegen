// Source: https://leetcode.com/problems/palindrome-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of unique strings words.
//
// A palindrome pair is a pair of integers (i, j) such that:
//
//
//  0 <= i, j < words.length,
//  i != j, and
//  words[i] + words[j] (the concatenation of the two strings) is a palindrome.
//
//
// Return an array of all the palindrome pairs of words.
//
// You must write an algorithm with O(sum of words[i].length) runtime complexity.
//
// Example:
// Input: words = ["abcd","dcba","lls","s","sssll"]
// Output: [[0,1],[1,0],[3,2],[2,4]]
// Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]
//
// Constraints:
// 1 <= words.length <= 5000
//  0 <= words[i].length <= 300
//  words[i] consists of lowercase English letters.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** palindromePairs(char** words, int wordsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (wordsSize < 2) return NULL;

    #define ALPHABET_SIZE 26
    #define MAX_WORDS 5000
    #define MAX_WORD_LEN 300

    typedef struct TrieNode {
        int index;
        struct TrieNode* children[ALPHABET_SIZE];
        int* palinSuffixes;
        int palinSuffixCount;
    } TrieNode;

    TrieNode* createNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        node->index = -1;
        node->palinSuffixes = (int*)malloc(sizeof(int) * MAX_WORDS);
        node->palinSuffixCount = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
        return node;
    }

    int isPalindrome(char* str, int left, int right) {
        while (left < right) {
            if (str[left++] != str[right--]) return 0;
        }
        return 1;
    }

    void insert(TrieNode* root, char* word, int index) {
        int len = strlen(word);
        for (int i = len - 1; i >= 0; i--) {
            if (isPalindrome(word, 0, i)) {
                root->palinSuffixes[root->palinSuffixCount++] = index;
            }
            int charIndex = word[i] - 'a';
            if (!root->children[charIndex]) {
                root->children[charIndex] = createNode();
            }
            root = root->children[charIndex];
        }
        root->index = index;
        root->palinSuffixes[root->palinSuffixCount++] = index;
    }

    TrieNode* search(TrieNode* root, char* word, int* palinSuffixes, int* palinCount) {
        int len = strlen(word);
        for (int i = 0; i < len; i++) {
            if (root->index >= 0 && root->index != -1 && isPalindrome(word, i, len - 1)) {
                palinSuffixes[(*palinCount)++] = root->index;
            }
            int charIndex = word[i] - 'a';
            if (!root->children[charIndex]) {
                return NULL;
            }
            root = root->children[charIndex];
        }
        if (root) {
            for (int i = 0; i < root->palinSuffixCount; i++) {
                palinSuffixes[(*palinCount)++] = root->palinSuffixes[i];
            }
        }
        return root;
    }
    TrieNode* root = createNode();
    for (int i = 0; i < wordsSize; i++) {
        insert(root, words[i], i);
    }
    int** result = (int**)malloc(sizeof(int*) * MAX_WORDS * MAX_WORDS);
    *returnColumnSizes = (int*)malloc(sizeof(int) * MAX_WORDS * MAX_WORDS);
    for (int i = 0; i < wordsSize; i++) {
        int palinSuffixes[MAX_WORDS];
        int palinCount = 0;
        TrieNode* node = search(root, words[i], palinSuffixes, &palinCount);
        if (node && node->index != -1 && node->index != i) {
            result[*returnSize] = (int*)malloc(sizeof(int) * 2);
            result[*returnSize][0] = i;
            result[*returnSize][1] = node->index;
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
        }
        for (int j = 0; j < palinCount; j++) {
            if (palinSuffixes[j] != i) {
                result[*returnSize] = (int*)malloc(sizeof(int) * 2);
                result[*returnSize][0] = i;
                result[*returnSize][1] = palinSuffixes[j];
                (*returnColumnSizes)[*returnSize] = 2;
                (*returnSize)++;
            }
        }
    }
    return result;
}
