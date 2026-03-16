// Source: https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given the root of a binary tree, calculate the vertical order traversal of the binary tree.
//
// For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).
//
// The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.
//
// Return the vertical order traversal of the binary tree.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: [[9],[3,15],[20],[7]]
// Explanation:
// Column -1: Only node 9 is in this column.
// Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
// Column 1: Only node 20 is in this column.
// Column 2: Only node 7 is in this column.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	0 <= Node.val <= 1000
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** verticalTraversal(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    // Implementation of vertical order traversal using DFS and sorting

    #define MAX_NODES 1000
    typedef struct {
        int x, y, val;
    } NodeInfo;

    NodeInfo nodes[MAX_NODES];
    int nodeCount = 0;

    void dfs(struct TreeNode* node, int x, int y) {
        if (!node) return;
        nodes[nodeCount++] = (NodeInfo){x, y, node->val};
        dfs(node->left, x - 1, y + 1);
        dfs(node->right, x + 1, y + 1);
    }

    dfs(root, 0, 0);

    // Sort nodes by x, then by y, then by value
    int compare(const void* a, const void* b) {
        NodeInfo* n1 = (NodeInfo*)a;
        NodeInfo* n2 = (NodeInfo*)b;
        if (n1->x != n2->x) return n1->x - n2->x;
        if (n1->y != n2->y) return n1->y - n2->y;
        return n1->val - n2->val;
    }

    qsort(nodes, nodeCount, sizeof(NodeInfo), compare);

    // Group nodes by their x coordinate
    int** result = (int**)malloc(sizeof(int*) * MAX_NODES);
    *returnColumnSizes = (int*)malloc(sizeof(int) * MAX_NODES);
    *returnSize = 0;

    int currentX = nodes[0].x;
    result[0] = (int*)malloc(sizeof(int) * MAX_NODES);
    int colSize = 0;

    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i].x != currentX) {
            (*returnColumnSizes)[*returnSize] = colSize;
            (*returnSize)++;
            currentX = nodes[i].x;
            colSize = 0;
            result[*returnSize] = (int*)malloc(sizeof(int) * MAX_NODES);
        }
        result[*returnSize][colSize++] = nodes[i].val;
    }
    (*returnColumnSizes)[*returnSize] = colSize;
    (*returnSize)++;

    return result;
}
