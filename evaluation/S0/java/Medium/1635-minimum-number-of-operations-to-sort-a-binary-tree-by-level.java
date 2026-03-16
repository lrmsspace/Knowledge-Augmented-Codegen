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
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public int minimumOperations(TreeNode root) {
        if (root == null) return 0;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int totalOperations = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            List<Integer> levelValues = new ArrayList<>();

            for (int i = 0; i < size; i++) {
                TreeNode currentNode = queue.poll();
                levelValues.add(currentNode.val);

                if (currentNode.left != null) {
                    queue.offer(currentNode.left);
                }
                if (currentNode.right != null) {
                    queue.offer(currentNode.right);
                }
            }

            totalOperations += calculateMinSwaps(levelValues);
        }

        return totalOperations;         
    }
}
