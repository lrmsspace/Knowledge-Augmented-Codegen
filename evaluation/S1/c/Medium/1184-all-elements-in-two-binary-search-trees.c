// Source: https://leetcode.com/problems/all-elements-in-two-binary-search-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given two binary search trees root1 and root2, return a list containing all the integers from both trees sorted in ascending order.
//
// Example:
// Input: root1 = [2,1,4], root2 = [1,0,3]
// Output: [0,1,1,2,3,4]
//
// Constraints:
// The number of nodes in each tree is in the range [0, 5000].
// 	-105 <= Node.val <= 105
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
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
int* getAllElements(struct TreeNode* root1, struct TreeNode* root2, int* returnSize) {
    // Helper function to perform in-order traversal and store values in an array
    void inorderTraversal(struct TreeNode* root, int* arr, int* index) {
        if (root == NULL) {
            return;
        }
        inorderTraversal(root->left, arr, index);
        arr[(*index)++] = root->val;
        inorderTraversal(root->right, arr, index);
    }

    // First, we need to determine the sizes of both trees
    int size1 = 0, size2 = 0;
    void countNodes(struct TreeNode* root, int* size) {
        if (root == NULL) {
            return;
        }
        countNodes(root->left, size);
        (*size)++;
        countNodes(root->right, size);
    }
    countNodes(root1, &size1);
    countNodes(root2, &size2);

    // Allocate arrays to hold the values from both trees
    int* arr1 = (int*)malloc(size1 * sizeof(int));
    int* arr2 = (int*)malloc(size2 * sizeof(int));

    // Perform in-order traversal to fill the arrays
    int index1 = 0, index2 = 0;
    inorderTraversal(root1, arr1, &index1);
    inorderTraversal(root2, arr2, &index2);

    // Merge the two sorted arrays
    int* result = (int*)malloc((size1 + size2) * sizeof(int));
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    while (i < size1) {
        result[k++] = arr1[i++];
    }
    while (j < size2) {
        result[k++] = arr2[j++];
    }

    // Set the return size
    *returnSize = size1 + size2;

    // Free temporary arrays
    free(arr1);
    free(arr2);

    return result;      
}
