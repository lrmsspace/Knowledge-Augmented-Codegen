// Source: https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree and an integer distance. A pair of two different leaf nodes of a binary tree is said to be good if the length of the shortest path between them is less than or equal to distance.
//
// Return the number of good leaf node pairs in the tree.
//
// Example:
// Input: root = [1,2,3,null,4], distance = 3
// Output: 1
// Explanation: The leaf nodes of the tree are 3 and 4 and the length of the shortest path between them is 3. This is the only good pair.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 210].
// 	1 <= Node.val <= 100
// 	1 <= distance <= 10
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int countPairs(struct TreeNode* root, int distance) {
    int result = 0;

    int* dfs(struct TreeNode* node) {
        if (!node) {
            return NULL;
        }
        if (!node->left && !node->right) {
            int* leafDistances = (int*)calloc(distance + 1, sizeof(int));
            leafDistances[1] = 1;
            return leafDistances;
        }

        int* leftDistances = dfs(node->left);
        int* rightDistances = dfs(node->right);

        if (leftDistances && rightDistances) {
            for (int i = 1; i <= distance; i++) {
                for (int j = 1; j <= distance; j++) {
                    if (i + j <= distance) {
                        result += leftDistances[i] * rightDistances[j];
                    }
                }
            }
        }

        int* currentDistances = (int*)calloc(distance + 1, sizeof(int));
        if (leftDistances) {
            for (int i = 1; i < distance; i++) {
                currentDistances[i + 1] += leftDistances[i];
            }
            free(leftDistances);
        }
        if (rightDistances) {
            for (int i = 1; i < distance; i++) {
                currentDistances[i + 1] += rightDistances[i];
            }
            free(rightDistances);
        }

        return currentDistances;
    }

    dfs(root);
    return result;      
}
