// Source: https://leetcode.com/problems/group-anagrams/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings strs, group the anagrams together. You can return the answer in any order.
//
// Example:
// Input: strs = ["eat","tea","tan","ate","nat","bat"]
//
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
//
// Explanation:
//
//
// 	There is no string in strs that can be rearranged to form "bat".
// 	The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
// 	The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.
//
// Constraints:
// 1 <= strs.length <= 104
// 	0 <= strs[i].length <= 100
// 	strs[i] consists of lowercase English letters.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    #define HASH_SIZE 10007

    typedef struct Node {
        char *str;
        struct Node *next;
    } Node;

    Node *hashTable[HASH_SIZE] = {0};
    char ***result = malloc(strsSize * sizeof(char **));
    *returnColumnSizes = malloc(strsSize * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < strsSize; i++) {
        char *str = strs[i];
        int count[26] = {0};
        for (char *p = str; *p; p++) {
            count[*p - 'a']++;
        }

        unsigned long hash = 5381;
        for (int j = 0; j < 26; j++) {
            hash = ((hash << 5) + hash) + count[j];
        }
        hash %= HASH_SIZE;

        Node *node = hashTable[hash];
        while (node) {
            if (strcmp(node->str, str) == 0) break;
            node = node->next;
        }

        if (!node) {
            node = malloc(sizeof(Node));
            node->str = str;
            node->next = hashTable[hash];
            hashTable[hash] = node;

            result[*returnSize] = malloc(strsSize * sizeof(char *));
            result[*returnSize][0] = str;
            (*returnColumnSizes)[*returnSize] = 1;
            (*returnSize)++;
        } else {
            for (int j = 0; j < *returnSize; j++) {
                if (strcmp(result[j][0], node->str) == 0) {
                    int colSize = (*returnColumnSizes)[j];
                    result[j][colSize] = str;
                    (*returnColumnSizes)[j]++;
                    break;
                }
            }
        }
    }

    return result;      
}
