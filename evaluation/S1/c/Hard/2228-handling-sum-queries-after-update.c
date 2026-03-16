// Source: https://leetcode.com/problems/handling-sum-queries-after-update/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed arrays nums1 and nums2 and a 2D array queries of queries. There are three types of queries:
//
//
// 	For a query of type 1, queries[i] = [1, l, r]. Flip the values from 0 to 1 and from 1 to 0 in nums1 from index l to index r. Both l and r are 0-indexed.
// 	For a query of type 2, queries[i] = [2, p, 0]. For every index 0 <= i < n, set nums2[i] = nums2[i] + nums1[i] * p.
// 	For a query of type 3, queries[i] = [3, 0, 0]. Find the sum of the elements in nums2.
//
//
// Return an array containing all the answers to the third type queries.
//
// Example:
// Input: nums1 = [1,0,1], nums2 = [0,0,0], queries = [[1,1,1],[2,1,0],[3,0,0]]
// Output: [3]
// Explanation: After the first query nums1 becomes [1,1,1]. After the second query, nums2 becomes [1,1,1], so the answer to the third query is 3. Thus, [3] is returned.
//
// Constraints:
// 1 <= nums1.length,nums2.length <= 105
// 	nums1.length = nums2.length
// 	1 <= queries.length <= 105
// 	queries[i].length = 3
// 	0 <= l <= r <= nums1.length - 1
// 	0 <= p <= 106
// 	0 <= nums1[i] <= 1
// 	0 <= nums2[i] <= 109
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
//   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
//   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
//   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* handleQuery(int* nums1, int nums1Size, int* nums2, int nums2Size, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;

    // Segment Tree Node
    typedef struct SegmentTreeNode {
        int left, right;
        int countOnes; // Number of ones in the segment
        int lazyFlip; // Lazy propagation flag for flip operation
        struct SegmentTreeNode *leftChild, *rightChild;
    } SegmentTreeNode;

    // Build Segment Tree
    SegmentTreeNode* buildTree(int* arr, int left, int right) {
        SegmentTreeNode* node = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode));
        node->left = left;
        node->right = right;
        node->lazyFlip = 0;
        if (left == right) {
            node->countOnes = arr[left];
            node->leftChild = node->rightChild = NULL;
        } else {
            int mid = (left + right) / 2;
            node->leftChild = buildTree(arr, left, mid);
            node->rightChild = buildTree(arr, mid + 1, right);
            node->countOnes = node->leftChild->countOnes + node->rightChild->countOnes;
        }
        return node;
    }

    // Propagate lazy flip
    void propagate(SegmentTreeNode* node) {
        if (node->lazyFlip) {
            node->countOnes = (node->right - node->left + 1) - node->countOnes; // Flip count
            if (node->left != node->right) { // Not a leaf
                node->leftChild->lazyFlip ^= 1;
                node->rightChild->lazyFlip ^= 1;
            }
            node->lazyFlip = 0;
        }
    }

    // Update range [l, r] to flip values
    void updateRange(SegmentTreeNode* node, int l, int r) {
        propagate(node);
        if (node->right < l || node->left > r) return; // No overlap
        if (node->left >= l && node->right <= r) { // Total overlap
            node->lazyFlip ^= 1;
            propagate(node);
            return;
        }
        // Partial overlap
        updateRange(node->leftChild, l, r);
        updateRange(node->rightChild, l, r);
        node->countOnes = node->leftChild->countOnes + node->rightChild->countOnes;
    }
    // Query count of ones in range [l, r]
    int queryRange(SegmentTreeNode* node, int l, int r) {
        propagate(node);
        if (node->right < l || node->left > r) return 0; // No overlap
        if (node->left >= l && node->right <= r) return node->countOnes; // Total overlap
        // Partial overlap
        return queryRange(node->leftChild, l, r) + queryRange(node->rightChild, l, r);
    }   
    // Free Segment Tree
    void freeTree(SegmentTreeNode* node) {
        if (!node) return;
        freeTree(node->leftChild);
        freeTree(node->rightChild);
        free(node);
    }
    // Build segment tree for nums1
    SegmentTreeNode* root = buildTree(nums1, 0, nums1Size - 1);
    long long* results = (long long*)malloc(queriesSize * sizeof(long long));
    long long sumNums2 = 0;
    for (int i = 0; i < nums2Size; i++) {
        sumNums2 += nums2[i];
    }
    int resIndex = 0;
    for (int i = 0; i < queriesSize; i++) {
        int type = queries[i][0];
        if (type == 1) {
            int l = queries[i][1];
            int r = queries[i][2];
            updateRange(root, l, r);
        } else if (type == 2) {
            int p = queries[i][1];
            int countOnes = queryRange(root, 0, nums1Size - 1);
            sumNums2 += (long long)countOnes * p;
        } else if (type == 3) {
            results[resIndex++] = sumNums2;
        }
    }
    freeTree(root);
    *returnSize = resIndex;
    return results;
}
