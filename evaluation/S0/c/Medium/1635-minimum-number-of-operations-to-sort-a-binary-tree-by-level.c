// Source: https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with unique values.
//
// In one operation, you can choose any two nodes at the same level and swap their values.
//
// Return the minimum number of operations needed to make the values at each level sorted in a strictly increasing order.
//
// The level of a node is the number of edges along the path between it and the root node.
//
// Example:
// Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
// Output: 3
// Explanation:
// - Swap 4 and 3. The 2nd level becomes [3,4].
// - Swap 7 and 5. The 3rd level becomes [5,6,8,7].
// - Swap 8 and 7. The 3rd level becomes [5,6,7,8].
// We used 3 operations so return 3.
// It can be proven that 3 is the minimum number of operations needed.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
// 	1 <= Node.val <= 105
// 	All the values of the tree are unique.
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int minimumOperations(struct TreeNode* root) {
    if (!root) return 0;

    #define MAX_NODES 100000
    struct TreeNode* queue[MAX_NODES];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int total_operations = 0;

    while (front < rear) {
        int level_size = rear - front;
        int values[level_size];
        for (int i = 0; i < level_size; i++) {
            struct TreeNode* node = queue[front++];
            values[i] = node->val;
            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }

        // Create a sorted copy of the values
        int sorted_values[level_size];
        for (int i = 0; i < level_size; i++) {
            sorted_values[i] = values[i];
        }
        // Simple bubble sort for demonstration purposes
        for (int i = 0; i < level_size - 1; i++) {
            for (int j = 0; j < level_size - i - 1; j++) {
                if (sorted_values[j] > sorted_values[j + 1]) {
                    int temp = sorted_values[j];
                    sorted_values[j] = sorted_values[j + 1];
                    sorted_values[j + 1] = temp;
                }
            }
        }

        // Count minimum swaps needed to sort the current level
        int visited[level_size];
        for (int i = 0; i < level_size; i++) visited[i] = 0;

        for (int i = 0; i < level_size; i++) {
            if (visited[i] || values[i] == sorted_values[i]) continue;

            int cycle_size = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = 1;
                // Find index of the value in the sorted array
                for (int k = 0; k < level_size; k++) {
                    if (values[j] == sorted_values[k]) {
                        j = k;
                        break;
                    }
                }
                cycle_size++;
            }
            if (cycle_size > 0) {
                total_operations += (cycle_size - 1);
            }
        }
    }

    return total_operations;        
}
