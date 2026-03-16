// Source: https://leetcode.com/problems/sum-of-prefix-scores-of-strings/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array words of size n consisting of non-empty strings.
//
// We define the score of a string term as the number of strings words[i] such that term is a prefix of words[i].
//
//
// 	For example, if words = ["a", "ab", "abc", "cab"], then the score of "ab" is 2, since "ab" is a prefix of both "ab" and "abc".
//
//
// Return an array answer of size n where answer[i] is the sum of scores of every non-empty prefix of words[i].
//
// Note that a string is considered as a prefix of itself.
//
// Example:
// Input: words = ["abc","ab","bc","b"]
// Output: [5,4,3,2]
// Explanation: The answer for each string is the following:
// - "abc" has 3 prefixes: "a", "ab", and "abc".
// - There are 2 strings with the prefix "a", 2 strings with the prefix "ab", and 1 string with the prefix "abc".
// The total is answer[0] = 2 + 2 + 1 = 5.
// - "ab" has 2 prefixes: "a" and "ab".
// - There are 2 strings with the prefix "a", and 2 strings with the prefix "ab".
// The total is answer[1] = 2 + 2 = 4.
// - "bc" has 2 prefixes: "b" and "bc".
// - There are 2 strings with the prefix "b", and 1 string with the prefix "bc".
// The total is answer[2] = 2 + 1 = 3.
// - "b" has 1 prefix: "b".
// - There are 2 strings with the prefix "b".
// The total is answer[3] = 2.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 1000
// 	words[i] consists of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumPrefixScores(char** words, int wordsSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = wordsSize;
    if (wordsSize <= 0) return NULL;

    /* Trie node definition */
    typedef struct TrieNode {
        struct TrieNode *children[26];
        int count; /* number of words sharing this prefix */
    } TrieNode;

    /* Create a new trie node */
    TrieNode* createNode() {
        TrieNode *node = (TrieNode*)calloc(1, sizeof(TrieNode));
        return node;
    }

    /* Insert a word into the trie */
    void insert(TrieNode *root, const char *word) {
        TrieNode *curr = root;
        for (const char *p = word; *p; ++p) {
            int index = *p - 'a';
            if (!curr->children[index]) {
                curr->children[index] = createNode();
            }
            curr = curr->children[index];
            curr->count++;
        }
    }

    /* Calculate the sum of prefix scores for a word */
    int calculateScore(TrieNode *root, const char *word) {
        TrieNode *curr = root;
        int score = 0;
        for (const char *p = word; *p; ++p) {
            int index = *p - 'a';
            curr = curr->children[index];
            score += curr->count;
        }
        return score;
    }

    /* Build the trie */
    TrieNode *trieRoot = createNode();
    for (int i = 0; i < wordsSize; ++i) {
        insert(trieRoot, words[i]);
    }

    /* Calculate scores for each word */
    int *result = (int*)malloc(wordsSize * sizeof(int));
    if (!result) {
        /* Free trie */
        // (Freeing code omitted for brevity)
        return NULL;
    }
    for (int i = 0; i < wordsSize; ++i) {
        result[i] = calculateScore(trieRoot, words[i]);
    }

    /* Free trie */
    // (Freeing code omitted for brevity)

    return result;      
}
