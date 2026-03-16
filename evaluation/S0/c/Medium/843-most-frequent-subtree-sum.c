// Source: https://leetcode.com/problems/most-frequent-subtree-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.
//
// The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
//
// Example:
// Input: root = [5,2,-3]
// Output: [2,-3,4]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-105 <= Node.val <= 105
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findFrequentTreeSum(struct TreeNode* root, int* returnSize) {
    #define MAX_NODES 10000
    #define HASH_SIZE (MAX_NODES * 2 + 1)

    struct HashEntry {
        int sum;
        int count;
        struct HashEntry* next;
    };

    struct HashEntry* hashTable[HASH_SIZE] = {0};
    int maxCount = 0;
    int* result = (int*)malloc(MAX_NODES * sizeof(int));
    *returnSize = 0;

    int hashFunction(int sum) {
        return (sum + MAX_NODES) % HASH_SIZE;
    }

    struct HashEntry* findOrCreateEntry(int sum) {
        int hashIndex = hashFunction(sum);
        struct HashEntry* entry = hashTable[hashIndex];
        while (entry) {
            if (entry->sum == sum) {
                return entry;
            }
            entry = entry->next;
        }
        entry = (struct HashEntry*)malloc(sizeof(struct HashEntry));
        entry->sum = sum;
        entry->count = 0;
        entry->next = hashTable[hashIndex];
        hashTable[hashIndex] = entry;
        return entry;
    }

    int computeSubtreeSum(struct TreeNode* node) {
        if (!node) return 0;
        int leftSum = computeSubtreeSum(node->left);
        int rightSum = computeSubtreeSum(node->right);
        int totalSum = node->val + leftSum + rightSum;

        struct HashEntry* entry = findOrCreateEntry(totalSum);
        entry->count++;
        if (entry->count > maxCount) {
            maxCount = entry->count;
            *returnSize = 0;
            result[(*returnSize)++] = totalSum;
        } else if (entry->count == maxCount) {
            result[(*returnSize)++] = totalSum;
        }

        return totalSum;
    }

    computeSubtreeSum(root);

    for (int i = 0; i < HASH_SIZE; i++) {
        struct HashEntry* entry = hashTable[i];
        while (entry) {
            struct HashEntry* temp = entry;
            entry = entry->next;
            free(temp);
        }
    }

    return result;      
}
