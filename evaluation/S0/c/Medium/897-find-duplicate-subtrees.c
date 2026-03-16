// Source: https://leetcode.com/problems/find-duplicate-subtrees/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return all duplicate subtrees.
//
// For each kind of duplicate subtrees, you only need to return the root node of any one of them.
//
// Two trees are duplicate if they have the same structure with the same node values.
//
// Example:
// Input: root = [1,2,3,4,null,2,4,null,null,4]
// Output: [[2,4],[4]]
//
// Constraints:
// The number of the nodes in the tree will be in the range [1, 5000]
// 	-200 <= Node.val <= 200
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
struct TreeNode** findDuplicateSubtrees(struct TreeNode* root, int* returnSize) {
    #define MAXN 5000
    #define MAXS 10000

    typedef struct HashNode {
        char* key;
        struct TreeNode* node;
        struct HashNode* next;
    } HashNode;

    HashNode* hashTable[MAXN] = {0};
    struct TreeNode** result = (struct TreeNode**)malloc(MAXN * sizeof(struct TreeNode*));
    *returnSize = 0;

    char* serialize(struct TreeNode* node, int* size) {
        if (!node) {
            char* nullStr = (char*)malloc(5);
            strcpy(nullStr, "#,");
            *size += 2;
            return nullStr;
        }

        int leftSize = 0, rightSize = 0;
        char* leftStr = serialize(node->left, &leftSize);
        char* rightStr = serialize(node->right, &rightSize);

        int totalSize = leftSize + rightSize + 12; // extra space for value and commas
        char* serial = (char*)malloc(totalSize);
        sprintf(serial, "%d,%s%s", node->val, leftStr, rightStr);
        *size += totalSize;

        free(leftStr);
        free(rightStr);

        return serial;
    }

    void insertHash(char* key, struct TreeNode* node) {
        unsigned long hash = 5381;
        for (char* c = key; *c; c++) {
            hash = ((hash << 5) + hash) + (*c);
        }
        hash %= MAXN;

        HashNode* curr = hashTable[hash];
        while (curr) {
            if (strcmp(curr->key, key) == 0) {
                if (curr->node != NULL) {
                    result[(*returnSize)++] = curr->node;
                    curr->node = NULL; // mark as added
                }
                free(key);
                return;
            }
            curr = curr->next;
        }

        HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
        newNode->key = key;
        newNode->node = node;
        newNode->next = hashTable[hash];
        hashTable[hash] = newNode;
    }

    void traverse(struct TreeNode* node) {
        if (!node) return;

        int size = 0;
        char* serial = serialize(node, &size);
        insertHash(serial, node);

        traverse(node->left);
        traverse(node->right);
    }
    traverse(root);
    // Free hash table
    for (int i = 0; i < MAXN; i++) {
        HashNode* curr = hashTable[i];
        while (curr) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp->key);
            free(temp);
        }
        
    }
    return result;
}
