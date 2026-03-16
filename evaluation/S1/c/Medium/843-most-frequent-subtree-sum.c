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
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
//   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
//   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
//   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
//   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

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
    #define HASH_SIZE 10000

    struct HashNode {
        int sum;
        int count;
        struct HashNode* next;
    };

    struct HashNode* hashTable[HASH_SIZE] = {0};
    int maxCount = 0;
    int uniqueSums = 0;

    int hashFunction(int sum) {
        return (sum % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
    }

    int computeSubtreeSum(struct TreeNode* node) {
        if (!node) return 0;
        int leftSum = computeSubtreeSum(node->left);
        int rightSum = computeSubtreeSum(node->right);
        int totalSum = node->val + leftSum + rightSum;

        int hashIndex = hashFunction(totalSum);
        struct HashNode* curr = hashTable[hashIndex];
        while (curr) {
            if (curr->sum == totalSum) {
                curr->count++;
                if (curr->count > maxCount) {
                    maxCount = curr->count;
                }
                return totalSum;
            }
            curr = curr->next;
        }

        struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
        newNode->sum = totalSum;
        newNode->count = 1;
        newNode->next = hashTable[hashIndex];
        hashTable[hashIndex] = newNode;
        uniqueSums++;
        if (newNode->count > maxCount) {
            maxCount = newNode->count;
        }
        return totalSum;
    }

    computeSubtreeSum(root);

    int* result = (int*)malloc(uniqueSums * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < HASH_SIZE; i++) {
        struct HashNode* curr = hashTable[i];
        while (curr) {
            if (curr->count == maxCount) {
                result[(*returnSize)++] = curr->sum;
            }
            struct HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    return result;      
}
