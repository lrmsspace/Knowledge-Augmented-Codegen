// Source: https://leetcode.com/problems/validate-binary-tree-nodes/   |   Difficulty: Medium
//
// Problem Description:
// You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and rightChild[i], return true if and only if all the given nodes form exactly one valid binary tree.
//
// If node i has no left child then leftChild[i] will equal -1, similarly for the right child.
//
// Note that the nodes have no values and that we only use the node numbers in this problem.
//
// Example:
// Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
// Output: true
//
// Constraints:
// n == leftChild.length == rightChild.length
// 	1 <= n <= 104
// 	-1 <= leftChild[i], rightChild[i] <= n - 1
//

bool validateBinaryTreeNodes(int n, int* leftChild, int leftChildSize, int* rightChild, int rightChildSize) {
    int* parent = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        if (leftChild[i] != -1) {
            if (parent[leftChild[i]] != 0) {
                free(parent);
                return false;
            }
            parent[leftChild[i]] = i + 1;
        }
        if (rightChild[i] != -1) {
            if (parent[rightChild[i]] != 0) {
                free(parent);
                return false;
            }
            parent[rightChild[i]] = i + 1;
        }
    }
    int rootCount = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] == 0) {
            rootCount++;
            if (rootCount > 1) {
                free(parent);
                return false;
            }
        }
    }
    free(parent);
    return rootCount == 1;      
}
