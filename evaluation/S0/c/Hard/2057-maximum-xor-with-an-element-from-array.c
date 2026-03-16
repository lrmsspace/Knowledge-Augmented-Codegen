// Source: https://leetcode.com/problems/maximum-xor-with-an-element-from-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].
//
// The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.
//
// Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.
//
// Example:
// Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
// Output: [3,3,7]
// Explanation:
// 1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
// 2) 1 XOR 2 = 3.
// 3) 5 XOR 2 = 7.
//
// Constraints:
// 1 <= nums.length, queries.length <= 105
// 	queries[i].length == 2
// 	0 <= nums[j], xi, mi <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximizeXor(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    if (queriesSize == 0) return NULL;

    /* Sort nums */
    int cmpInt(const void *a, const void *b) {
        return (*(int*)a) - (*(int*)b);
    }
    qsort(nums, numsSize, sizeof(int), cmpInt);

    /* Augment queries with original indices */
    typedef struct {
        int x;
        int m;
        int idx;
    } Query;
    Query *qarr = (Query*)malloc(queriesSize * sizeof(Query));
    if (!qarr) return NULL;
    for (int i = 0; i < queriesSize; ++i) {
        qarr[i].x = queries[i][0];
        qarr[i].m = queries[i][1];
        qarr[i].idx = i;
    }
    qsort(qarr, queriesSize, sizeof(Query), cmpIntM);
    
    /* Trie Node Definition */
    typedef struct TrieNode {
        struct TrieNode *children[2];
    } TrieNode;

    TrieNode* createNode() {
        TrieNode *node = (TrieNode*)calloc(1, sizeof(TrieNode));
        return node;
    }

    void insert(TrieNode *root, int num) {
        TrieNode *curr = root;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!curr->children[bit]) {
                curr->children[bit] = createNode();
            }
            curr = curr->children[bit];
        }
    }

    int query(TrieNode *root, int x) {
        TrieNode *curr = root;
        if (!curr->children[0] && !curr->children[1]) return -1; // empty trie
        int maxXor = 0;
        for (int i = 31; i >= 0; --i) {
            int bit = (x >> i) & 1;
            int toggledBit = 1 - bit;
            if (curr->children[toggledBit]) {
                maxXor |= (1 << i);
                curr = curr->children[toggledBit];
            } else {
                curr = curr->children[bit];
            }
        }
        return maxXor;
    }
    TrieNode *trieRoot = createNode();
    int *results = (int*)malloc(queriesSize * sizeof(int));
    int numIdx = 0;
    for (int i = 0; i < queriesSize; ++i) {
        while (numIdx < numsSize && nums[numIdx] <= qarr[i].m) {
            insert(trieRoot, nums[numIdx]);
            numIdx++;
        }
        results[qarr[i].idx] = query(trieRoot, qarr[i].x);
    }
    free(qarr);
    return results; 
}
