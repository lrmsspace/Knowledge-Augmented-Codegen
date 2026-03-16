// Source: https://leetcode.com/problems/k-th-largest-perfect-subtree-size-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree and an integer k.
//
// Return an integer denoting the size of the kth largest perfect binary subtree, or -1 if it doesn't exist.
//
// A perfect binary tree is a tree where all leaves are on the same level, and every parent has two children.
//
// Example:
// Input: root = [5,3,6,5,2,5,7,1,8,null,null,6,8], k = 2
//
// Output: 3
//
// Explanation:
//
//
//
// The roots of the perfect binary subtrees are highlighted in black. Their sizes, in non-increasing order are [3, 3, 1, 1, 1, 1, 1, 1].
// The 2nd largest size is 3.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 2000].
// 	1 <= Node.val <= 2000
// 	1 <= k <= 1024
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, quickselect, randomized)
//   • When to use: Use when you need to efficiently find the k-th smallest or largest element in an unsorted array without fully sorting it, especially when average-case linear time complexity is acceptable and in-place modification is desired.
//   • Idea: QuickSelect is a divide-and-conquer algorithm that partitions an array around a pivot and recursively searches for the k-th element in the relevant partition. It offers an average-case O(N) time complexity and O(1) space.
//   • Invariants: The pivot element is always placed at its correct sorted position within the current sub-array.; All elements to the left of the pivot are less than or equal to it, and all elements to its right are greater than or equal to it.
//   • Tips: Randomly select pivots to ensure average-case O(N) performance and avoid worst-case scenarios.; Adjust the target index k based on whether you're seeking the k-th smallest or k-th largest element.
//   • Pitfalls: Poor pivot selection can lead to a worst-case O(N^2) time complexity, though rare with randomization.; Off-by-one errors are common when mapping k-th largest/smallest to 0-indexed array positions.
// - Binary Search Trees
//  (tree, quickselect)
//   • When to use: Use when maintaining an ordered collection of elements that requires efficient search, insertion, and deletion operations. It is also suitable for finding minimum, maximum, floor, and ceiling values.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Core operations like search, insert, and delete typically run in O(h) time, where h is the tree's height.
//   • Invariants: For any node, all keys in its left subtree are less than its own key.; For any node, all keys in its right subtree are greater than its own key.
//   • Tips: Maintain subtree sizes for order-statistic operations like finding the k-th smallest element.; Consider self-balancing variants (AVL, Red-Black) to guarantee O(log N) worst-case performance.
//   • Pitfalls: Unbalanced trees can degrade to O(N) performance for all operations.; Forgetting to update parent pointers or subtree sizes during modifications.
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
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
int kthLargestPerfectSubtree(struct TreeNode* root, int k) {
    // Helper function to perform DFS and collect sizes of perfect binary subtrees
    void dfs(struct TreeNode* node, int* sizes, int* sizeCount) {
        if (!node) return;

        int leftSize = 0, rightSize = 0;
        dfs(node->left, sizes, sizeCount);
        dfs(node->right, sizes, sizeCount);

        if (node->left && node->right) {
            leftSize = node->left->val;
            rightSize = node->right->val;
            if (leftSize == rightSize) {
                int perfectSize = leftSize + rightSize + 1;
                sizes[(*sizeCount)++] = perfectSize;
                node->val = perfectSize; // Store size in node for parent calculation
                return;
            }
        }
        node->val = 1; // Leaf node or non-perfect subtree
        sizes[(*sizeCount)++] = 1;
    }

    int sizes[2000]; // Array to store sizes of perfect binary subtrees
    int sizeCount = 0;

    dfs(root, sizes, &sizeCount);

    // Quickselect to find the k-th largest element
    int left = 0, right = sizeCount - 1;
    k = sizeCount - k; // Convert to k-th smallest

    while (left <= right) {
        int pivot = sizes[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (sizes[j] <= pivot) {
                i++;
                int temp = sizes[i];
                sizes[i] = sizes[j];
                sizes[j] = temp;
            }
        }
        i++;
        sizes[right] = sizes[i];
        sizes[i] = pivot;

        if (i == k) {
            return sizes[i];
        } else if (i < k) {
            left = i + 1;
        } else {
            right = i - 1;
        }
    }

    return -1; // If k is out of bounds     
}
